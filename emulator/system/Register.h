#ifndef MCU_REGISTER_H_
#define MCU_REGISTER_H_

#include <assert.h>
#include <stdint.h>

class RegisterInterface {
 public:
  virtual ~RegisterInterface() = default;

 protected:
  virtual uint32_t get() = 0;
  virtual void set(uint32_t value) = 0;
};

class Register : private RegisterInterface {
 public:
  explicit Register(uint32_t i = 0) : _value(i) {}
  ~Register() = default;

  operator const uint32_t() { return get(); }
  void operator=(uint32_t data) { set(data); }

  Register& operator&=(uint32_t const& rhs) {
    _value &= rhs;
    return *this;
  }
  Register& operator|=(uint32_t const& rhs) {
    _value |= rhs;
    return *this;
  }

 private:
  virtual uint32_t get() final { return _value; }
  virtual void set(uint32_t value) final { _value = value; }
  uint32_t _value;
};

class SCRegisterAbstract {
 public:
  SCRegisterAbstract(Register* parent = nullptr) : _parent(parent) {}
  void setParent(Register* parent) { _parent = parent; }
  Register* parent() const {
    assert(_parent);
    return _parent;
  }

 private:
  Register* _parent;
};

class SRegister : public SCRegisterAbstract, private RegisterInterface {
 public:
  explicit SRegister(Register* parent = nullptr) : SCRegisterAbstract(parent) {}
  operator const uint32_t() { return get(); }
  void operator=(uint32_t data) { set(data); }

 private:
  virtual uint32_t get() final { return *parent(); }
  virtual void set(uint32_t value) final { *parent() |= value; }
};

class CRegister : public SCRegisterAbstract, private RegisterInterface {
 public:
  explicit CRegister(Register* parent = nullptr) : SCRegisterAbstract(parent) {}
  operator const uint32_t() { return get(); }
  void operator=(uint32_t data) { set(data); }

 private:
  virtual uint32_t get() final { return *parent(); }
  virtual void set(uint32_t value) final { *parent() &= ~value; };
};

#endif /* MCU_REGISTER_H_ */
