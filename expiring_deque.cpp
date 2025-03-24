#include <cassert>
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

using std::cout;
using std::endl;

static inline uint64_t red_get_timer_cycles(void) {
  return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

using NowFn = uint64_t (*)();

template <typename T, NowFn = red_get_timer_cycles> class expiring_deque {
private:
  struct wrapper {
    uint64_t m_last_accessed{red_get_timer_cycles()};
    T m_t;
    wrapper(T t) : m_t(t) {}
  };

public:
  class iterator {
  public:
    T operator*() { return (*m_it).m_t; };
    iterator &operator++() {
      ++m_it;
      return *this;
    };
    bool operator!=(const iterator &other) { return m_it != other.m_it; }

    typename std::deque<wrapper>::iterator m_it;
  };

  template <typename... Args>
  expiring_deque(Args &&...args) : m_deque(std::forward(args)...) {}

  auto push_back(T t) { return m_deque.push_back(wrapper(t)); }

  iterator begin() { return {m_deque.begin()}; }
  iterator end() { return {m_deque.end()}; }

  void purge() {
    cout << "purge" << endl;
    auto now = red_get_timer_cycles();
  }

private:
  std::deque<wrapper> m_deque;
};

/**
 * @brief Data structure that represents an red_bucket_stream_t stream
 *
 * An opaque 8 byte struct
 */
typedef struct {
  void *hndl;
} __attribute__((__packed__, __aligned__(8))) red_bucket_stream_t;

template <typename HANDLE, typename FROM>
static inline HANDLE to_chndl(FROM from) {
  return HANDLE{reinterpret_cast<void *>(from)};
}

template <typename TO, typename HANDLE> static inline TO from_chndl(HANDLE h) {
  return reinterpret_cast<TO>(h.hndl);
}

struct rfs_bucket_stream_t {
  /*
   * Used to keep track of unused red_s3_bucket_t that have been
   * read up from the server.
   */
  size_t cur_index;
  std::vector<std::string> s3_bucket_vec;

  /*
   * To implement LRU and remove the ones those expired the limit based on
   * last_accessed
   */
  uint64_t bs_last_accessed{0};

  /* Service thread owning the stream */
  //    client_sthread_t             *bs_sthread {NULL};

  /* MTQ */
  //    mtq_entry_t  bs_qe;
  //    MTQHEAD_TYPEDEF(rfs_bucket_stream_t, bs_qe) bucket_stream_q_t;
  rfs_bucket_stream_t() = default;
  rfs_bucket_stream_t(std::string s) { s3_bucket_vec.push_back(s); }
};

template <typename Key, typename T> class expiring_map {
public:
  struct element {
    T *t;
    bool is_deleted{false};
  };
  using SetType = std::unordered_map<T *, element>;
  using iterator = typename SetType::iterator;

  template <typename... Args> std::pair<Key, bool> emplace(Args &&...args) {
    auto newt = new T(args...);
    auto eres = m_map.emplace(std::make_pair(newt, element({newt})));
    assert(eres.second);
    expiration_queue.push_back(&(eres.first->second));
    return {to_chndl<Key>(newt), true};
  }

  auto find(const Key &key) {
    expiration_queue.purge();
    return m_map.find(from_chndl<T *>(key));
  }
  iterator begin() { return m_map.begin(); }
  iterator end() { return m_map.end(); }

  bool remove(const Key &key) {
    auto it = find(key);
    if (it == m_map.end() || it->second.is_deleted)
      return false;
    it->second.is_deleted = true;
    return true;
  }

  bool purge_expired() { expiration_queue.purge(); }

  ~expiring_map() {
    for (auto kv : m_map) {
      delete kv.second.t;
    }
  }

private:
  SetType m_map;
  expiring_deque<element *> expiration_queue;
};

int main() {
  expiring_deque<int> d;
  d.push_back(13);
  d.push_back(14);
  d.push_back(15);
  for (auto elem : d)
    cout << elem << ", ";
  cout << std::endl;

  expiring_map<red_bucket_stream_t, rfs_bucket_stream_t> map;
  auto handle1 = map.emplace("apa").first;
  auto handle2 = map.emplace("bapa").first;
  auto handle3 = map.emplace("CP:a").first;

  for (auto kv : map) {
    cout << kv.first;
    if (kv.second.is_deleted)
      cout << "<deleted>\n";
    else
      cout << " : " << kv.second.t->s3_bucket_vec[0] << endl;
  }

  map.remove(handle2);

  for (auto kv : map) {
    cout << kv.first;
    if (kv.second.is_deleted)
      cout << "<deleted>\n";
    else
      cout << " : " << kv.second.t->s3_bucket_vec[0] << endl;
  }

  /*
    {
    auto r = map.find(handle);
    if (r != map.end()) {
      cout << "found\n";
      cout << *r << endl;
      cout << (*r)->s3_bucket_vec[0] << endl;
    }
  }
  */
}
