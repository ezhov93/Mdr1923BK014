#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <QByteArray>

class ByteArray : public QByteArray {
 public:
  ByteArray() : QByteArray() {}
  explicit ByteArray(const QByteArray& other) : QByteArray(other) {}
  ~ByteArray() {}

  inline ByteArray& operator=(const char* str) {
    return static_cast<ByteArray&>(QByteArray::operator=(str));
  }

  inline ByteArray& operator=(QByteArray data) {
    return static_cast<ByteArray&>(QByteArray::operator=(data));
  }

  inline ByteArray& append(const QByteArray& other) {
    return static_cast<ByteArray&>(QByteArray::append(other));
  }
  inline ByteArray& append(const qint64 i) {
    return appendTemplate<const qint64>(i);
  }
  inline ByteArray& append(const quint64 i) {
    return appendTemplate<const quint64>(i);
  }
  inline ByteArray& append(const qint32 i) {
    return appendTemplate<const qint32>(i);
  }
  inline ByteArray& append(const quint32 i) {
    return appendTemplate<const quint32>(i);
  }
  inline ByteArray& append(const qint16 i) {
    return appendTemplate<const qint16>(i);
  }
  inline ByteArray& append(const quint16 i) {
    return appendTemplate<const quint16>(i);
  }
  inline ByteArray& append(const qint8 i) {
    return appendTemplate<const qint8>(i);
  }
  inline ByteArray& append(const quint8 i) {
    return appendTemplate<const quint8>(i);
  }

  ByteArray& append(char i) { return appendTemplate<const quint8>(i); }

  ByteArray& append(const char* ptr, int len) {
    return static_cast<ByteArray&>(QByteArray::append(ptr, len));
  }

  ByteArray& appendChecksum();
  ByteArray& reverse();
  static void test();

 private:
  template <typename T>
  inline ByteArray& appendTemplate(const T t) {
    const char* ptr = reinterpret_cast<const char*>(&t);
    return static_cast<ByteArray&>(QByteArray::append(ptr, sizeof(t)));
  }
};

#endif  // BYTEARRAY_H
