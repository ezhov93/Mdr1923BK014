#ifndef RING_H
#define RING_H

template <typename T = unsigned char, int Size = 64>
class Ring {
 public:
  constexpr Ring() : _head(0), _tail(0) {}
  ~Ring() = default;
  bool isFull() const {
    return ((_tail + 1) == _head) || ((_tail == Size) && (_head == 0));
  }
  bool isEmpty() const { return _head == _tail; }
  void push(const T data) { push(data, 1); }
  void push(const T* data, int size) {
    for (int cnt = 0; cnt < size; ++cnt) {
      _data[_tail] = data[cnt];
      _tail = (++_tail == Size) ? 0 : _tail;
      if (isFull()) return;
    }
  }
  const T pop() {
    T data;
    pop(data, 1);
    return data;
  }
  void pop(T* data, int size) {
    for (int cnt = 0; cnt < size; ++cnt) {
      if (isEmpty()) return;
      data[cnt] = _data[_head];
      _head = (++_head == Size) ? 0 : _head;
    }
  }
  const T peek() {
    T data;
    peek(&data, 1);
    return data;
  }
  void peek(T* data, int size) {
    const int head = _head;
    pop(data, size);
    _head = head;
  }
  void clear() { _head = _tail; }
  int size() const { return Size; }
  int available() const {
    int cnt = _tail - _head;
    if (cnt < 0)
      return (Size - 1) - _head + _tail;
    else
      return cnt;
  }
  const void* data_ptr() const { return reinterpret_cast<void*>(_data); }

 private:
  T _data[Size];
  volatile int _head;
  volatile int _tail;
};

#endif /* RING_H */
