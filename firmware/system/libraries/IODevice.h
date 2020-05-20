#ifndef IODEVICE_H
#define IODEVICE_H

#include "IODeviceObserver.h"

// TODO Event: readuRead and bytesWritten(int bytes);

class IODevice {
  enum { Error = -1 };

 public:
  IODevice() : _open(false) {}
  ~IODevice() = default;
  virtual int bytesAvailable() const = 0;
  virtual int bytesToWrite() const = 0;
  virtual bool close() = 0;
  bool isOpen() const { return _open; }
  virtual int peek() = 0;
  virtual int peek(char* data, int size) = 0;
  virtual bool open() = 0;
  virtual int read(char* data, int size) = 0;
  virtual int read(char& c) { return read(&c, 1); }
  virtual int size() const = 0;
  int skip(int size) {
    char c;
    int len = 0;
    while (size--) {
      if (read(c) < 1)
        return len;
      len++;
    }
    return len;
  }
  virtual int availableForWrite() = 0;
  virtual void flush() = 0;
  virtual int write(const char* data, int size) = 0;
  virtual int write(unsigned char ch) {
    return write(reinterpret_cast<char*>(&ch), 1);
  }
  int write(const char* data) {
    int size = 0;
    while (data[size] != '\0')
      write(data[size++]);
    return size;
  }
  int write(unsigned long n) { return write(static_cast<unsigned char>(n)); }
  int write(long n) { return write(static_cast<unsigned char>(n)); }
  int write(unsigned int n) { return write(static_cast<unsigned char>(n)); }
  int write(int n) { return write(static_cast<unsigned char>(n)); }

  virtual void attach(IODeviceObserver* observer) { _observer = observer; }
  virtual void detach() { _observer = nullptr; }

 protected:
  virtual void notifyReadyRead() {
    if (_observer)
      _observer->readyRead();
  }
  virtual void notyfyBytesWritten(int size) {
    if (_observer)
      _observer->bytesWritten(size);
  }

  bool _open;

 private:
  IODeviceObserver* _observer = nullptr;
};

#endif /* IODEVICE_H */
