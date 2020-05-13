#include "loader.h"

#include <bytearray.h>
#include <QDebug>
#include <QFile>
#include <QSerialPort>
#include <QTimer>
#include <iostream>

Loader::Loader(QObject* parent) : QObject(parent), _mcu(nullptr) {
  _serial = new QSerialPort(this);
  _serial->setBaudRate(QSerialPort::Baud9600);
  _serial->setDataBits(QSerialPort::Data8);
  _serial->setParity(QSerialPort::NoParity);
  _serial->setStopBits(QSerialPort::OneStop);
  _serial->setFlowControl(QSerialPort::NoFlowControl);
}

bool Loader::connect() {
  if (!_serial->open(QIODevice::ReadWrite)) {
    emit textChanged(tr("Unable to open port: ") + _serial->errorString());
    return false;
  }

  ByteArray data;
  data.fill(0, 512);
  auto recv = transfer(data, 1000);
  if (recv.indexOf('>') < 0) {
    emit textChanged(tr("No response from MCU"));
    _serial->close();
    return false;
  }
  return true;
}

bool Loader::dump(QString fileName) {
  Q_UNUSED(fileName)
  return false;
}

bool Loader::program() {
  if (!checkAndOpenFile())
    return false;
  ByteArray data;

  data.append('L');
  data.append(_firmware.baseAdr());
  data.append(_firmware.sizeData());
  auto recv = transfer(data, 250);
  if (!recv.contains('L')) {
    emit textChanged(tr("Download command failed!"));
    return false;
  }
  emit textChanged("Downloading...");
  recv = transfer(_firmware.data(), 250);
  if (!recv.contains('K')) {
    emit textChanged("No download confirmation!");
    return false;
  }
  emit textChanged("OK");
  return true;
}

bool Loader::isVerify() {
  ByteArray data;
  ByteArray recv;
  int chankCount = (_firmware.sizeData() + 7) / 8;
  emit textChanged("Memory verifying...");
  for (int chank = 0; chank < chankCount; chank++) {
    data = "Y";
    data.append(_firmware.baseAdr() + chank * 8);
    data.append((int)8);
    recv = transfer(data, 100);
    if (recv.size() < 10) {
      emit textChanged("Verification cmd failed (size)!");
      return false;
    } else if ((recv.at(0) != 'Y') || (recv.at(9) != 'K')) {
      emit textChanged("Verification cmd failed (control)!");
      return false;
    } else if (!recv.contains(_firmware.data().mid(chank * 8, 8))) {
      emit textChanged("Verification cmd failed (verify)!");
      return false;
    }
  }
  emit textChanged("OK");
  return true;
}

bool Loader::runFirmware() {
  ByteArray data;
  data.append('R');
  data.append(_firmware.data().data() + 4, 4);
  auto recv = transfer(data, 250);
  if (!recv.contains('R')) {
    emit textChanged("No runed!");
    return false;
  }
  emit textChanged("Runing!");
  return true;
}

bool Loader::checkAndOpenFile() {
  if (!_firmware.fromFile(_fileName)) {
    emit textChanged(tr("Unable to open firmware file, error on line %1")
                         .arg(_firmware.stringNumber()));
    return false;
  }

  _firmware.setData(_firmware.data(), _memoryType->adr, _memoryType->adr);

  //  if (_firmware.baseAdr() == 0xFFFFFFFF) {
  //    _firmware.setData(_firmware.data(), _memoryType->adr, _memoryType->adr);
  //  } else if ((_firmware.baseAdr() < _memoryType->adr) ||
  //             (_firmware.baseAdr() + _firmware.sizeData() >
  //              _memoryType->adr + _memoryType->size)) {
  //    emit textChanged(tr("Downloadable program goes beyond memory range: "
  //                        "Start 0x%1 \t End 0x%2")
  //                         .arg(_firmware.baseAdr(), 8, 16, QChar('0'))
  //                         .arg(_firmware.baseAdr() + _firmware.sizeData(), 8,
  //                         16,
  //                              QChar('0')));
  //    return false;
  //  } else if ((_firmware.baseAdr() & 0xFFU) != 0) {
  //    emit textChanged(tr("Адрес начала записываемого кода должен быть "
  //                        "кратен 256 байт! 0x%1")
  //                         .arg(_firmware.baseAdr(), 8, 16, QChar('0')));
  //    return false;
  //  }

  qDebug() << "  base =0x" << QString::number(_firmware.baseAdr(), 16)
           << " start =0x" << QString::number(_firmware.startAdr(), 16)
           << "  size =" << QString::number(_firmware.sizeData(), 10);
  return true;
}

ByteArray Loader::transfer(const ByteArray& data, int timeout) {
  ByteArray recv;
  if (!_serial->isOpen())
    return recv;
  _serial->write(data);
  while (!_serial->waitForBytesWritten())
    recv.append(_serial->readAll());
  while (_serial->waitForReadyRead(timeout))
    recv.append(_serial->readAll());
  return recv;
}
