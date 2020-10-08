#include <QCoreApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QTimer>
#include "commandlineparser.h"
#include "task.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);
  QCoreApplication::setApplicationName("Serial MldtMCU loader");
  QCoreApplication::setApplicationVersion("0.1");

  auto print = [](QString str) {
#ifdef Q_OS_WIN32
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
#endif
#ifdef Q_OS_LINUX
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
    static QTextStream qout(stdout);
    qout << str;
    Qt::endl(qout);
  };

  auto parser = &CommandLineParser::instance();
  if (!parser->isVerify())
    return EXIT_FAILURE;
  QObject::connect(parser, &CommandLineParser::textChanged, print);

  Task task(&a);
  QObject::connect(&task, &Task::textChanged, print);
  QObject::connect(&task, &Task::finished, &a, QCoreApplication::quit);

  QTimer::singleShot(10, &task, SLOT(run()));
  return a.exec();
}
