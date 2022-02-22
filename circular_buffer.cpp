#include <memory>
#include <mutex>

template <class T> class CircularBuffer {

public:
  CircularBuffer(size_t capacity)
      : m_capacity(capacity),
        m_buffer(static_cast<T *>(operator new(sizeof(T) * capacity))) {}

  ~CircularBuffer() {
    printf("about to destroy");
    delete m_buffer;
    printf("destroyed buffer");
  }

  template <class... Args> bool emplace_back(Args &&... args) {
    if (full())
      return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    new (&m_buffer[m_write_pos]) T(std::forward<decltype(args)>(args)...);

    m_write_pos = (m_write_pos + 1) % m_capacity;
    m_is_full = m_write_pos == m_read_pos;
    printf("emplaced next %i", m_write_pos);
    return true;
  }

  T pop_front() {
    while (empty()) {
    }
    printf("pop_front() wanting mutex");
    std::lock_guard<std::mutex> lock(m_mutex);
    T res = m_buffer[m_read_pos];
    m_read_pos = (m_read_pos + 1) % m_capacity;
    printf("pop_front() next %i", m_read_pos);
    return res;
  }

  T &front() {
    while (empty()) {
    }
    printf("front() wating for mutex");
    std::lock_guard<std::mutex> lock(m_mutex);
    T &res = m_buffer[m_read_pos];

    return res;
  }

  size_t size() const {
    if (m_write_pos < m_read_pos)
      return m_write_pos + m_capacity - m_read_pos;
    else if (m_write_pos > m_read_pos)
      return m_write_pos - m_read_pos;
    else
      return full() ? m_capacity : 0;
  }

  bool full() const { return m_is_full; }

  bool empty() const { return m_read_pos == m_write_pos && !full(); }

private:
  size_t m_capacity;
  T *m_buffer;
  int m_write_pos{0};
  int m_read_pos{0};
  bool m_is_full{false};
  std::mutex m_mutex;
};

int main() {
  CircularBuffer<int> cb(3);
  cb.emplace_back(1);
  cb.emplace_back(2);
  cb.emplace_back(3);
  cb.emplace_back(4);

  cb.~CircularBuffer();
  printf("destroued\n");
}
