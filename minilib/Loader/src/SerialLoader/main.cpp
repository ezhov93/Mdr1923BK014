#include <QCommandLineParser>
#include <QCoreApplication>
#include "QDebug"
#include "iostream"
#include "loader.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);
  QCoreApplication::setApplicationName("Serial Loader");
  QCoreApplication::setApplicationVersion("0.1");

  QCommandLineParser parser;
  parser.setApplicationDescription("Test helper");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("com", "COM port name");
  parser.addPositionalArgument("file", "Load file (.hex .bin)");
  parser.addOption(QCommandLineOption("f", "Fast load whithout verify"));
  parser.parse(QCoreApplication::arguments());
  const QStringList args = parser.positionalArguments();
  const QString serialName = args.isEmpty() ? QString() : args.at(0);
  QString fileName = args.isEmpty() ? QString() : args.at(1);
  bool fast = false;
  if (parser.isSet("f"))
    fast = true;

  Loader loader;
  QObject::connect(&loader, &Loader::textChanged, [](QString str) {
    std::cout << str.toStdString() << std::endl;
  });

  loader.setPortName(serialName);
  loader.setMcu(&Mdr1923VK014);
  loader.setMemoryArea(Loader::XRam);
  //  loader.setFile("D:/MEGA/Projects/Eclipse/test/Debug/test.bin");
  //  loader.setFile("D:/led_blink/led_blink_debug.hex");
  loader.setFile(fileName);

  bool ok;
  ok = loader.connect();
  if (ok)
    ok = loader.program();
  if (ok && !fast)
    ok = loader.isVerify();
  if (ok)
    ok = loader.runFirmware();

  return 1;
}
