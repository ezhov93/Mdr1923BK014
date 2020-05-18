#ifndef SERIAL_H
#define SERIAL_H

#include <libraries/StreamInterface.h>

#include "Pin.h"
#include "libraries/Global.h"
#include "libraries/Ring.h"

// TODO: pins and methods

class SerialAbstract : public StreamInterface {
 public:
  enum DataBits { Data5 = 0x00, Data6 = 0x20, Data7 = 0x40, Data8 = 0x60 };
  enum Parity {
    NoParity = 0x00,
    EvenParity = 0x06,
    OddParity = 0x02,
    MarkParity = 0x82,
    SpaceParity = 0x86
  };
  enum StopBits { OneStop = 0x00, TwoStop = 0x08 };

  const struct InitArgs {
    const Pin& rx;
    const Pin& tx;
    const uint base;
    const func_ptr handler;
  };

  Serial(const InitArgs& args) {}
  ~Serial() = default;
  void init();
  void init(const int baudrate);
  void setBaudRate(const int baudrate) { _baudRate = baudrate; }
  int baudrate() const { return _baudRate; }
  void setDataBits(const DataBits dataBits) { _dataBits = dataBits; }
  const DataBits dataBits() const { return _dataBits; }
  void setParity(const Parity patity) { _parity = parity; }
  const Parity parity() const { return _parity; }
  void setStopBits(const StopBits stopBits) { _stopBits = stopBits; }
  const StopBits stopBits() const { return _stopBits; }
  virtual int available(void) final { return _ring.available(); }
  virtual int peek(void) final { return _ring.peek(); }
  virtual int read(void) final { return _ring.pop(); }
  virtual void flush() final {}
  virtual int write(unsigned char ch) final;
  virtual int write(const void* buf, int len) final;

 private:
  const Pin& _rx;
  const Pin& _tx;
  const uint _base;
  const uint _irq;
  Ring<uchar, 64> _ring;
  int _baudRate;
  DataBits _dataBits;
  Parity _parity;
  StopBits _stopBits;
};

#endif  // SERIALABSTRACT_H
