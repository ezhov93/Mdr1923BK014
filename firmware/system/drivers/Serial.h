#ifndef SERIAL_H
#define SERIAL_H

#include "../libraries/IODevice.h"
#include "../libraries/Ring.h"
#include "Pin.h"
#include "Serial.h"

// TODO add irq
struct SerialArgs {
  const Pin& rx;

  const Pin& tx;
  const uint base;
};

class Serial : public IODevice {
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

  Serial(const Pin& rx, const Pin& tx, const uint base)
      : _rx(rx),
        _tx(tx),
        _base(base),
        _irq(),
        _baudRate(9600),
        _dataBits(Data8),
        _parity(NoParity),
        _stopBits(OneStop) {}
  ~Serial() = default;
  void setBaudRate(const int baudrate) { _baudRate = baudrate; }
  int baudrate() const { return _baudRate; }
  void setDataBits(const DataBits dataBits) { _dataBits = dataBits; }
  DataBits dataBits() const { return _dataBits; }
  void setParity(const Parity parity) { _parity = parity; }
  Parity parity() const { return _parity; }
  void setStopBits(const StopBits stopBits) { _stopBits = stopBits; }
  StopBits stopBits() const { return _stopBits; }

  virtual int bytesAvailable() const final { return _ring.available(); }
  virtual int bytesToWrite() const override { return 0; }
  virtual bool close() final;
  virtual int peek() final { return _ring.peek(); }
  virtual int peek(char* data, int size) final {
    _ring.peek(reinterpret_cast<uchar*>(data), size);
    return size;
  }
  virtual bool open() final;
  int read(char* data, int size) final;
  virtual int size() const final { return Size; }
  virtual int availableForWrite() override { return 0; }
  virtual void flush() override;
  virtual int write(const char* data, int size) override;

 private:
  static const int Size = 64;
  const Pin& _rx;
  const Pin& _tx;
  const uint _base;
  const uint _irq;

  Ring<uchar, Size> _ring;
  int _baudRate;
  DataBits _dataBits;
  Parity _parity;
  StopBits _stopBits;
};

#endif  // SERIALABSTRACT_H
