#ifndef SYSTEM_1923VK014_DRIVERS_PIN_H_
#define SYSTEM_1923VK014_DRIVERS_PIN_H_

#include "libraries/Global.h"

class Pin {
 public:
  enum Function {
    Function0,
    Function1,
    Function2,
    Function3,
    Function4,
    Function5,
    Function6,
    Function7,
    Function8,
    Function9,
    Function10,
    Function11,
    Function12,
    Function13,
    Function14,
    Function15,
  };

  enum Mode {
    Input,
    InputPullup,
    InputPulldown,
    AnalogInput,
    Output,
    OutputPullup,
    OutputPulldown,
    AnalogOutput
  };

  constexpr Pin(const uint portAddr, const uint number)
      : _portAddr(portAddr), _number(number) {}

  ~Pin() = default;

  void init(const Mode, const Function function = Function0) const;
  void set() const;
  void reset() const;
  void write(bool state) const { (state ? set() : reset()); }
  bool read() const;

 private:
  constexpr uint numberPos() const { return (1 << _number); }
  const uint _portAddr;
  const uint _number;
};

extern const Pin PA0;
extern const Pin PA1;
extern const Pin PA2;
extern const Pin PA3;
extern const Pin PA4;
extern const Pin PA5;
extern const Pin PA6;
extern const Pin PA7;
extern const Pin PA8;
extern const Pin PA9;
extern const Pin PA10;
extern const Pin PA11;
extern const Pin PA12;
extern const Pin PA13;
extern const Pin PA14;
extern const Pin PA15;
extern const Pin PA16;
extern const Pin PA17;
extern const Pin PA18;
extern const Pin PA19;
extern const Pin PA20;
extern const Pin PA21;
extern const Pin PA22;
extern const Pin PA23;
extern const Pin PA24;
extern const Pin PA25;
extern const Pin PA26;
extern const Pin PA27;
extern const Pin PA28;
extern const Pin PA29;
extern const Pin PA30;
extern const Pin PA31;
extern const Pin PB0;
extern const Pin PB1;
extern const Pin PB2;
extern const Pin PB3;
extern const Pin PB4;
extern const Pin PB5;
extern const Pin PB6;
extern const Pin PB7;
extern const Pin PB8;
extern const Pin PB9;
extern const Pin PB10;
extern const Pin PB11;
extern const Pin PB12;
extern const Pin PB13;
extern const Pin PB14;
extern const Pin PB15;
extern const Pin PB16;
extern const Pin PB17;
extern const Pin PB18;
extern const Pin PB19;
extern const Pin PB20;
extern const Pin PB21;
extern const Pin PB22;
extern const Pin PB23;
extern const Pin PB24;
extern const Pin PB25;
extern const Pin PB26;
extern const Pin PB27;
extern const Pin PB28;
extern const Pin PB29;
extern const Pin PB30;
extern const Pin PB31;
extern const Pin PC0;
extern const Pin PC1;
extern const Pin PC2;
extern const Pin PC3;
extern const Pin PC4;
extern const Pin PC5;
extern const Pin PC6;
extern const Pin PC7;
extern const Pin PC8;
extern const Pin PC9;
extern const Pin PC10;
extern const Pin PC11;
extern const Pin PC12;
extern const Pin PC13;
extern const Pin PC14;
extern const Pin PC15;
extern const Pin PC16;
extern const Pin PC17;
extern const Pin PC18;
extern const Pin PC19;
extern const Pin PC20;
extern const Pin PC21;
extern const Pin PC22;
extern const Pin PC23;
extern const Pin PC24;
extern const Pin PC25;
extern const Pin PC26;
extern const Pin PC27;
extern const Pin PC28;
extern const Pin PC29;
extern const Pin PC30;
extern const Pin PC31;
extern const Pin PD0;
extern const Pin PD1;
extern const Pin PD2;
extern const Pin PD3;
extern const Pin PD4;
extern const Pin PD5;
extern const Pin PD6;
extern const Pin PD7;
extern const Pin PD8;
extern const Pin PD9;
extern const Pin PD10;
extern const Pin PD11;
extern const Pin PD12;
extern const Pin PD13;
extern const Pin PD14;
extern const Pin PD15;
extern const Pin PD16;
extern const Pin PD17;
extern const Pin PD18;
extern const Pin PD19;
extern const Pin PD20;
extern const Pin PD21;
extern const Pin PD22;
extern const Pin PD23;
extern const Pin PD24;
extern const Pin PD25;
extern const Pin PD26;
extern const Pin PD27;
extern const Pin PD28;
extern const Pin PD29;
extern const Pin PD30;
extern const Pin PD31;
extern const Pin PE0;
extern const Pin PE1;
extern const Pin PE2;
extern const Pin PE3;
extern const Pin PE4;
extern const Pin PE5;
extern const Pin PE6;
extern const Pin PE7;
extern const Pin PE8;
extern const Pin PE9;
extern const Pin PE10;
extern const Pin PE11;
extern const Pin PE12;
extern const Pin PE13;
extern const Pin PE14;
extern const Pin PE15;
extern const Pin PE16;
extern const Pin PE17;
extern const Pin PE18;
extern const Pin PE19;
extern const Pin PE20;
extern const Pin PE21;
extern const Pin PE22;
extern const Pin PE23;
extern const Pin PE24;
extern const Pin PE25;
extern const Pin PE26;
extern const Pin PE27;
extern const Pin PE28;
extern const Pin PE29;
extern const Pin PE30;
extern const Pin PE31;

#endif /* SYSTEM_1923VK014_DRIVERS_PIN_H_ */
