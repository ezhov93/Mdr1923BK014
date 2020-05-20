#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QCommandLineParser>
#include <QObject>

class CommandLineParser : public QObject {
  Q_OBJECT
 public:
  static CommandLineParser& instance() {
    static CommandLineParser obj;
    return obj;
  }

  bool isVerify() const { return _verify; }
  QString portName() const { return _serialName; }
  QString fileName() const { return _fileName; }
  bool isFastLoad() const { return _fastLoad; }

 signals:
  void textChanged(QString);

 private:
  CommandLineParser() {
    auto app = QCoreApplication::instance();
    QCommandLineParser _parser;
    _parser.setApplicationDescription(app->applicationName());
    _parser.addHelpOption();
    _parser.addVersionOption();
    _parser.addPositionalArgument("com", "Имя COM порта");
    _parser.addPositionalArgument("файл", "Загружаемый файл (.hex .bin)");
    _parser.addOption(QCommandLineOption("f", "Быстрая загрузка без проверки"));
    _parser.process(*app);
    _parser.parse(app->arguments());
    const QStringList args = _parser.positionalArguments();
    _verify = args.size() == 2;
    if (_verify) {
      _serialName = args.isEmpty() ? QString() : args.at(0);
      _fileName = args.isEmpty() ? QString() : args.at(1);
      _fastLoad = _parser.isSet("f");
    } else {
      emit textChanged("Неверное количество аргументов");
    }
  }
  ~CommandLineParser() = default;
  CommandLineParser(const CommandLineParser&) = delete;
  CommandLineParser& operator=(const CommandLineParser&) = delete;
  bool _verify = false;
  bool _fastLoad;
  QString _serialName;
  QString _fileName;
};

#endif  // COMMANDLINEPARSER_H
