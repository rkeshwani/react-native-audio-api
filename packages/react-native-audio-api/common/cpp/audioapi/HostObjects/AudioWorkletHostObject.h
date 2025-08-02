#pragma once

#include <audioapi/jsi/JsiHostObject.h>
#include <audioapi/core/worklets/AudioWorklet.h>
#include <audioapi/jsi/JsiPromise.h>
#include <memory>

namespace audioapi {
using namespace facebook;

class AudioWorkletHostObject : public JsiHostObject {
 public:
  explicit AudioWorkletHostObject(
      const std::shared_ptr<AudioWorklet> &worklet,
      const std::shared_ptr<PromiseVendor> &promiseVendor)
      : worklet_(worklet), promiseVendor_(promiseVendor) {
    addFunctions(JSI_EXPORT_METHOD(AudioWorkletHostObject, addModule));
  }

  JSI_HOST_FUNCTION(addModule) {
    auto script = arguments[0].asString(runtime).utf8(runtime);

    auto promise = promiseVendor_->createPromise([this, script](std::shared_ptr<Promise> promise) {
      worklet_->addModule(
          script,
          [promise]() { promise->resolve([](jsi::Runtime &runtime) { return jsi::Value::undefined(); }); },
          [promise](const std::string &error) { promise->reject(error); });
    });

    return promise;
  }

 private:
  std::shared_ptr<AudioWorklet> worklet_;
  std::shared_ptr<PromiseVendor> promiseVendor_;
};
} // namespace audioapi
