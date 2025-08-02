#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>

namespace facebook {
namespace jsi {

class Runtime;

class JSIException : public std::runtime_error {
 public:
  explicit JSIException(const std::string &what) : std::runtime_error(what) {}
};

class Value {
 public:
  Value() {}
  Value(Runtime &runtime, const Value &value) {}
  static Value undefined() { return Value(); }
  bool isObject() const { return false; }
  // ... other methods
};

class Object {
 public:
  Object() {}
  Object(Runtime &runtime) {}
  Function asFunction(Runtime &runtime) const;
  // ... other methods
};

class Function : public Object {
 public:
  Function() {}
  // ... other methods
};

class Runtime {
 public:
  // ... other methods
};

} // namespace jsi
} // namespace facebook
