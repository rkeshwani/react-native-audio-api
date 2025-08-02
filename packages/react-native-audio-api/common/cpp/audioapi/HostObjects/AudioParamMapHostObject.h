#pragma once

#include <audioapi/jsi/JsiHostObject.h>
#include <audioapi/core/AudioParam.h>
#include <audioapi/HostObjects/AudioParamHostObject.h>
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
    addFunctions(JSI_EXPORT_FUNCTION(AudioParamMapHostObject, get));
  }

  JSI_HOST_FUNCTION(get) {
    auto name = arguments[0].asString(runtime).utf8(runtime);
    if (!params_.count(name)) {
      return jsi::Value::undefined();
    }
    auto param = params_.at(name);
    auto paramHostObject = std::make_shared<AudioParamHostObject>(param);
    return jsi::Object::createFromHostObject(runtime, paramHostObject);
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<AudioParam>> params_;
};
} // namespace audioapi
