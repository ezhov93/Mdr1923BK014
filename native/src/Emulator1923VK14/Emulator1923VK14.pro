TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../../firmware/system/drivers/Pin.cpp \
        ../../../firmware/system/drivers/PinMap.cpp \
        ../../../firmware/system/drivers/SerialAbstract.cpp \
        main.cpp

HEADERS += \
  ../../../firmware/system/drivers/Pin.h \
  ../../../firmware/system/drivers/SerialAbstract.h \
  ../../../firmware/system/drivers/StreamInterface.h \
  ../../../firmware/system/libraries/Global.h \
  ../../../firmware/system/libraries/Ring.h \
  ../../../firmware/system/test/TestPin.h \
  1923VK014.h \
  Global.h \
  Periferia/CLKControl.h \
  Periferia/PortControl.h \
  Periferia/Uart.h \
  Periphery/CLKControl.h \
  Periphery/PortControl.h \
  Periphery/Uart.h \
  Ring.h

INCLUDEPATH += \
../../../firmware/system


