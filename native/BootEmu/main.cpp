#include <QCoreApplication>
#include "boot.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  Boot boot;
  boot.setPortName("COM6");
  boot.exec();

  return a.exec();
}
