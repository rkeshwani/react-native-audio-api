#pragma once

#include <audioapi/jsi/JsiHostObject.h>
#include <audioapi/core/AudioParam.h>
#include <unordered_map>
#include <string>
#include <memory>

namespace audioapi {
using namespace facebook;

class AudioParamMapHostObject : public JsiHostObject {
 public:
  explicit AudioParamMapHostObject(
      std::unordered_map<std::string, std::shared_ptr<AudioParam>> &&params)
      : params_(std::move(params)) {
    // TODO: Expose map-like methods (get, has, etc.)
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<AudioParam>> params_;
};
} // namespace audioapi
