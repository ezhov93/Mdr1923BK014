#ifndef STREAMINTERFACE_H
#define STREAMINTERFACE_H

class StreamInterface {
 public:
  StreamInterface() = default;
  ~StreamInterface() = default;
  virtual int available() = 0;
  virtual int peek() = 0;
  virtual int read() = 0;
  virtual int availableForWrite() = 0;
  virtual void flush() = 0;
  virtual int write(unsigned char ch) = 0;
  virtual int write(const void *buf, int len) = 0;
  int write(unsigned long n) { return write(static_cast<unsigned char>(n)); }
  int write(long n) { return write(static_cast<unsigned char>(n)); }
  int write(unsigned int n) { return write(static_cast<unsigned char>(n)); }
  int write(int n) { return write(static_cast<unsigned char>(n)); }
};

#endif /* STREAMINTERFACE_H */
