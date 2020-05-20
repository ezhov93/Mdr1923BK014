#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "commandlineparser.h"
#include "loader.h"

class Task : public QObject {
  Q_OBJECT

 public:
  Task(QObject* parent = 0) : QObject(parent) {
    _loader = new Loader;
    connect(_loader, &Loader::textChanged, this, &Task::textChanged);
  }

  ~Task() { delete _loader; }

 public slots:
  void run() {
    auto& parser = CommandLineParser::instance();
    if (!parser.isVerify())
      return;
    _loader->setPortName(parser.portName());
    _loader->setMcu(&Mdr1923VK014);
    _loader->setMemoryArea(Loader::XRam);
    //  loader.setFile("D:/MEGA/Projects/Eclipse/test/Debug/test.bin");
    //  loader.setFile("D:/led_blink/led_blink_debug.hex");
    _loader->setFile(parser.fileName());

    bool ok;
    ok = _loader->connect();
    if (ok)
      ok = _loader->program();
    if (ok && !parser.isFastLoad())
      ok = _loader->isVerify();
    if (ok)
      ok = _loader->runFirmware();

    emit finished();
  }

 signals:
  void finished();
  void textChanged(QString);

 private:
  Loader* _loader;
};

#endif  // TASK_H
