#ifndef IODEVICEOBSERVER_H
#define IODEVICEOBSERVER_H

class IODeviceObserver {
 public:
  virtual ~IODeviceObserver() = default;
  virtual void readyRead() = 0;
  virtual void bytesWritten(int size) = 0;
};

#endif  // IODEVICEOBSERVER_H
