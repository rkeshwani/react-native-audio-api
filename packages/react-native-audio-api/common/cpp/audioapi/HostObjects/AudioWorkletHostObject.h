#pragma once

#include <audioapi/jsi/JsiHostObject.h>
#include <audioapi/core/worklets/AudioWorklet.h>
#include <memory>

namespace audioapi {
using namespace facebook;

class AudioWorkletHostObject : public JsiHostObject {
 public:
  explicit AudioWorkletHostObject(const std::shared_ptr<AudioWorklet> &worklet)
      : worklet_(worklet) {
    addMethods(JSI_EXPORT_METHOD(AudioWorkletHostObject, addModule));
  }

  JSI_HOST_FUNCTION(addModule) {
    auto moduleURL = arguments[0].asString(runtime).utf8(runtime);
    worklet_->addModule(moduleURL);
    // TODO: This should return a promise
    return jsi::Value::undefined();
  }

 private:
  std::shared_ptr<AudioWorklet> worklet_;
};
} // namespace audioapi
