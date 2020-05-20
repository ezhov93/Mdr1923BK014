#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QObject>

class Parser : public QObject {
  Q_OBJECT

 public:
  Parser(QString fileName, QObject* parent = nullptr) : QObject(parent) {
    _file = new QFile(fileName);
  }
  ~Parser() {
    finish();
    delete _file;
  }

 public slots:
  void run() {
    if (!_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
      emit textChanged("fail open file");
      finish();
      return;
    }

    while (true) {
      if (_file->atEnd())
        continue;
      QString line = _file->readLine();
      if (!line.isEmpty() && line.at(0) == '@') {
        constexpr auto NewLine = "\\r\\n";
        constexpr auto Begin = "@\"";
        constexpr auto End = "\"\n";
        line.remove(Begin);
        line.remove(End);
        if (line.contains(NewLine)) {
          line.remove(NewLine);
          line += "\n\r";
        }
        emit textChanged(line);
      }
      if (_file->size() == 0) {
        _file->close();
        const auto Cls = "\x1B[2J\x1B[H";
        emit textChanged(Cls);
        _file->open(QIODevice::ReadOnly | QIODevice::Text);
      }
    }
    finish();
  }

 signals:
  void finished();
  void textChanged(QString);

 private:
  void finish() {
    if (_file->isOpen())
      _file->close();
    emit finished();
  }
  QFile* _file;
};

#endif  // PARSER_H
