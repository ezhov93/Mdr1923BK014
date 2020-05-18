#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
 public:
  Singleton() = delete;
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton) = delete;

  static T& instance() {
    static T _instance;
    return _instance;
  }
};
