#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QSerialPort>
#include "hex.h"
#include "mcu.h"

class Loader : public QObject {
  Q_OBJECT
 public:
  enum MemoryArea { Flas, Rom, XRam };

  explicit Loader(QObject* parent = nullptr);
  ~Loader() { delete _serial; }
  void setPortName(const QString name) { _serial->setPortName(name); }
  void setFile(const QString name) { _fileName = name; }
  void setMcu(const Mcu* mcu) { _mcu = const_cast<Mcu*>(mcu); }
  void setMemoryArea(MemoryArea area) {
    _memoryType = &reinterpret_cast<Mcu::Type*>(_mcu)[area];
  }
  bool connect();
  bool isConnect() const { return _serial->isOpen(); }
  bool dump(QString fileName);
  //  bool erase();
  bool program();
  bool isVerify();
  bool runFirmware();

 signals:
  void textChanged(QString);
  void statusChanged(QString);

 private:
  bool checkAndOpenFile();
  ByteArray transfer(const ByteArray&, int timeout);
  bool serialOpen();
  const ByteArray commandArray(uint32_t addr, uint32_t size);
  QString _fileName;
  QSerialPort* _serial;
  Mcu* _mcu;
  Mcu::Type* _memoryType = nullptr;
  Hex _firmware;
};

#endif  // LOADER_H
