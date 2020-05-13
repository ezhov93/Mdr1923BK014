#ifndef BOOT_H
#define BOOT_H

#include <QObject>
#include <QSerialPort>

class Boot : public QObject {
  Q_OBJECT

 public:
  explicit Boot(QObject* parent = nullptr);
  ~Boot() { delete _serial; }
  void setPortName(const QString name) { _serial->setPortName(name); }
  void exec();

 private:
  QSerialPort* _serial;
};

#endif  // BOOT_H
