#include <iostream>
#include <string>
#include <vector>

int hashCode(int i) { return i; }
int hashKey(int i) { return i; }
template <typename Key_type, typename Value_type> Value_type null_element();
template <> int null_element<int, int>() { return -1; }

template <typename Key_type, typename Value_type, size_t N = 10>
class HashTable {
  using HashBucket = std::vector<Value_type>;

public:
  HashTable() {
    for (int i = 0; i < N; ++i)
      m_buckets.emplace_back();
  }

  void put(Key_type key, Value_type value) {
    m_buckets[hashCode(key) % N].push_back(value);
  }

  Value_type get(Key_type key) {
    HashBucket &bucket = m_buckets[hashCode(key) % N];
    for (auto &value : bucket)
      if (primaryKey(value) == key)
        return value;
    return null_element<Key_type, Value_type>();
  }

private:
  std::vector<HashBucket> m_buckets;
};

struct Person {
  std::string name;
  int pkey;
};

int hashCode(const Person &p) {
  if (p.pkey == 3212)
    return 43321;
  return p.pkey;
}
int primaryKey(const Person &p) { return p.pkey; }

template <> Person null_element<int>() { return {"nobody", -1}; }

int main(int, const char **) {
  HashTable<int, Person> tab;
  Person p1{"Peter", 1234};
  Person p2{"Susan", 4321};
  Person p3{"George", 3212};

  tab.put(p1.pkey, p1);
  tab.put(p2.pkey, p2);
  tab.put(p3.pkey, p3);

  std::cout << "get(1) : " << tab.get(1234).name << std::endl;
  std::cout << "get(2) : " << tab.get(4321).name << std::endl;
  std::cout << "get(3) : " << tab.get(3212).name << std::endl;
}
