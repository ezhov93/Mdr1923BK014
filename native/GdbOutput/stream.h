#ifndef BOOT_H
#define BOOT_H

#include <QFile>
#include <QObject>

class Stream : public QObject {
  Q_OBJECT

 public:
  explicit Stream(QString fileName, QObject* parent = nullptr);
  ~Stream() { delete _file; }
  void exec();

 private:
  QFile* _file;
};

#endif  // BOOT_H
