#ifndef SYSTEM_LIBRARIES_RING_H_
#define SYSTEM_LIBRARIES_RING_H_

template<typename T = unsigned char, int SIZE>
class Ring {
 public:
  constexpr Ring() {
    _head = 0;
    _tail = 0;
  }

  ~Ring() = default;

  bool isFull() const {
    return ((_tail + 1) == _head) || ((_tail == SIZE) && (_head == 0));
  }

  bool isEmpty() const {
    return _head == _tail;
  }

  void push(const T data) {
    push(data, 1);
  }

  void push(const T &data, int size) {
    for (int cnt = 0; cnt < size; ++cnt) {
      _data[_tail] = data[cnt];
      _tail = (++_tail == SIZE) ? 0 : _tail;
      if (isFull())
        return;
    }
  }

  T pop() {
    T data;
    pop(data, 1);
    return data;
  }

  void pop(const T &data, int size) {
    for (int cnt = 0; cnt < size; ++cnt) {
      if (isEmpty())
        return;
      data[cnt] = _data[_head];
      _head = (++_head == SIZE) ? 0 : _head;
    }
  }

  T peek() {
    T data;
    peak(data, 1);
    return data;
  }

  void peek(T &data, int size) {
    const int head = _head;
    pop(data, size);
    _head = head;
  }

  void clear() {
    _head = _tail;
  }

  int size() const {
    return SIZE;
  }

  int count() const {
    int cnt = _tail - _head;
    if (cnt < 0)
      return (SIZE-1) - _head + _tail;
    else
      return cnt;
  }

  void* data_ptr() const {
    return reinterpret_cast<void*>(_data);
  }

 private:
  unsigned char _data[SIZE];
  volatile int _tail;
  volatile int _head;
};

#endif /* SYSTEM_LIBRARIES_RING_H_ */
