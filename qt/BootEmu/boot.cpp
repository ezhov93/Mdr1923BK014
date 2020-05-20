#include "boot.h"
#include <QDebug>
#include <QSerialPort>
#include <QThread>

Boot::Boot(QObject* parent) {
  _serial = new QSerialPort(this);
  _serial->setBaudRate(QSerialPort::Baud9600);
  _serial->setDataBits(QSerialPort::Data8);
  _serial->setParity(QSerialPort::NoParity);
  _serial->setStopBits(QSerialPort::OneStop);
  _serial->setFlowControl(QSerialPort::NoFlowControl);
}

void Boot::exec() {
  if (!_serial->open(QSerialPort::ReadWrite))
    return;

  QByteArray data, recv;

  _serial->waitForReadyRead();  // wait start
  while (_serial->waitForReadyRead(3000))
    _serial->readAll();  // skip zeros

  // connect
  data = "\r\n>";
  _serial->write(data);
  _serial->waitForBytesWritten();
  _serial->write(data);
  _serial->waitForBytesWritten();
  _serial->clear();

  // load cmd
  while (_serial->waitForReadyRead(100))
    recv += _serial->readAll();
  qDebug() << recv;
  _serial->write("L");

  // load file
  while (_serial->waitForReadyRead(3000))
    _serial->readAll();
  _serial->write("K");

  // run
  recv = 0;
  while (_serial->waitForReadyRead(1000))
    recv += _serial->readAll();
  qDebug() << recv;
  _serial->write("R");
  qDebug() << "finish";
  //_serial->waitForReadyRead(3000);
  // qDebug() << _serial->readAll();
  //  _serial->write(data);
  //  _serial->waitForReadyRead(3000);
}
