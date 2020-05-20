#include <QCoreApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QTimer>
#include "parser.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

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

  Parser* parser = new Parser(argv[1], &a);
  QObject::connect(parser, &Parser::finished, &a, &QCoreApplication::quit);
  QObject::connect(parser, &Parser::textChanged, print);

  QTimer::singleShot(10, parser, &Parser::run);
  return a.exec();
}
