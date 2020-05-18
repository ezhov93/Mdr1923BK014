#ifndef TEST_TESTINTERFACE_H
#define TEST_TESTINTERFACE_H

class TestInterface {
 public:
  virtual ~TestInterface() = default;
  virtual void exec() = 0;
  virtual void update() = 0;
};

#endif /* TEST_TESTINTERFACE_H */
