#pragma once

#include <stdexcept>
#include <string>

namespace audioapi {

class NotSupportedError : public std::runtime_error {
 public:
  explicit NotSupportedError(const std::string &what) : std::runtime_error(what) {}
};

class InvalidStateError : public std::runtime_error {
 public:
  explicit InvalidStateError(const std::string &what) : std::runtime_error(what) {}
};

class TypeError : public std::runtime_error {
 public:
  explicit TypeError(const std::string &what) : std::runtime_error(what) {}
};

} // namespace audioapi
