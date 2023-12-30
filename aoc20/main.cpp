#include <cassert>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

class Module;

struct Pulse {
  enum class Value {
    High,
    Low,
  } value;
  const Module &sender;
  std::string receiver;
};

std::deque<Pulse> pulse_queue;

static std::unordered_map<std::string, std::unique_ptr<Module>> modules;

class Module {
public:
  enum class Type {
    Broadcaster,
    FlipFlop,
    Conjunction,
  };
  explicit Module(std::vector<std::string> listeners)
      : m_listeners(listeners) {}

  virtual ~Module() = default;

  virtual void handle(const Pulse &pulse) = 0;

  static std::string typeToString(Type t) {
    switch (t) {
    case Type::FlipFlop:
      return "flip-flop";
    case Type::Broadcaster:
      return "broadcaster";
    case Type::Conjunction:
      return "conjunction";
    }
  }

  void notify_listeners(const Pulse::Value &pulse_value) {
    for (auto listener : m_listeners)
      pulse_queue.push_back({pulse_value, *this, listener});
  }

private:
  std::vector<std::string> m_listeners;
};

class Broadcaster : public Module {
public:
  explicit Broadcaster(std::vector<std::string> listeners)
      : Module(listeners) {}
  void handle(const Pulse &pulse) override { handlepv(pulse.value); }
  void handlepv(const Pulse::Value pulse_value) {
    notify_listeners(pulse_value);
  }
};

class FlipFlop : public Module {
public:
  enum class Position {
    On,
    Off,
  };
  explicit FlipFlop(std::vector<std::string> listeners) : Module(listeners) {}

  void handle(const Pulse &pulse) override {
    if (pulse.value == Pulse::Value::High)
      return;
    switch (m_position) {
    case Position::Off:
      m_position = Position::On;
      notify_listeners(Pulse::Value::High);
      break;
    case Position::On:
      m_position = Position::Off;
      notify_listeners(Pulse::Value::Low);
      break;
    }
  }

private:
  Position m_position{Position::Off};
};

class Conjunction : public Module {
public:
  explicit Conjunction(std::vector<std::string> listeners)
      : Module(listeners) {}

  void handle(const Pulse &pulse) override {
    m_last_pulses.insert({&pulse.sender, pulse.value});
    for (const auto &entry : m_last_pulses) {
      if (entry.second == Pulse::Value::Low) {
        notify_listeners(Pulse::Value::High);
        return;
      }
    }
    notify_listeners(Pulse::Value::Low);
  }

private:
  std::unordered_map<const Module *, Pulse::Value> m_last_pulses;
};

bool parseModuleDecl(const std::string &moduleDecl) {

  Module::Type mt;
  std::string name;
  const size_t eon = moduleDecl.find_first_of(" ");

  switch (moduleDecl[0]) {
  case '%':
    mt = Module::Type::FlipFlop;
    name = moduleDecl.substr(1, eon - 1);
    break;
  case '&':
    mt = Module::Type::Conjunction;
    name = moduleDecl.substr(1, eon - 1);
    break;
  default:
    name = moduleDecl.substr(0, eon);
    mt = Module::Type::Broadcaster;
    if (name != "broadcaster") {
      cout << "Error: no type code and name '" << name
           << "' isn't 'broadcaster'\n";
      return false;
    }
    break;
  }

  size_t pos = eon;
  if (moduleDecl[pos] == ' ')
    pos++;
  assert(moduleDecl[pos++] == '-');
  assert(moduleDecl[pos++] == '>');
  if (moduleDecl[pos] == ' ')
    pos++;
  std::vector<std::string> listeners;
  size_t start_of_name = pos;
  size_t next_comma_pos = moduleDecl.find_first_of(",", start_of_name);
  do {
    while (moduleDecl[start_of_name] == ' ')
      start_of_name++;

    listeners.emplace_back(
        moduleDecl.substr(start_of_name, next_comma_pos - start_of_name));
    start_of_name = next_comma_pos != std::string::npos ? next_comma_pos + 1
                                                        : next_comma_pos;
    while (moduleDecl[start_of_name] == ' ')
      start_of_name++;
    next_comma_pos = moduleDecl.find_first_of(",", start_of_name);
  } while (start_of_name < moduleDecl.length());

  switch (mt) {
  case Module::Type::Conjunction:
    modules.insert({name, make_unique<Conjunction>(listeners)});
    break;
  case Module::Type::FlipFlop:
    modules.insert({name, make_unique<FlipFlop>(listeners)});
    break;
  case Module::Type::Broadcaster:
    modules.insert({name, make_unique<Broadcaster>(listeners)});
    break;
  }
  return true;
}

bool parseFile(const std::string &filename) {
  cout << "Parsing file '" << filename << "'" << endl;

  std::ifstream infile(filename);
  if (!infile.is_open()) {
    cout << "Cannot open file '" << filename << "'\n";
    return false;
  }
  std::string line;
  while (getline(infile, line)) {
    parseModuleDecl(line);
  }
  infile.close();
  return true;
}

bool resolveModules() {
  for (auto &entry : modules) {
    auto name = entry.first;
    auto module
    cout << "An entry: " << entry.first << "\n";
  }
  return false;
}

int main(int argc, const char **argv) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }
  std::string filename{argv[1]};
  parseFile(filename);
  cout << "Succesfully read '" << filename << "'.\n";

  bool resolveStatus = resolveModules();
  if (!resolveStatus) {
    cout << "Error in name resolution\n";
    return -1;
  }

  auto &broadcaster =
      *dynamic_cast<Broadcaster *>(modules.find("broadcaster")->second.get());
  cout << &broadcaster;
  broadcaster.handlepv(Pulse::Value::Low);
  while (!pulse_queue.empty()) {
    Pulse pulse = pulse_queue.front();
    pulse_queue.pop_front();
    auto recipient_it = modules.find(pulse.receiver);
    if (recipient_it == modules.end()) {
      cout << "Warning: recipient '" << pulse.receiver << "' not found!\n";
    } else {
      auto &recipient = *recipient_it->second;
      /*
      cout << "Sending " << (pulse.value == Pulse::Value::Low ? "low" : "high")
           << " to " << pulse.receiver << "\n";
      */
      recipient.handle(pulse);
    }
  }
}
