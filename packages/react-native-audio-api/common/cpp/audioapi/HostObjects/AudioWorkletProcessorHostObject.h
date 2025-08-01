#pragma once

#include <audioapi/jsi/JsiHostObject.h>
#include <audioapi/core/worklets/AudioWorkletProcessor.h>
#include <memory>

namespace audioapi {
using namespace facebook;

class AudioWorkletProcessorHostObject : public JsiHostObject {
 public:
  explicit AudioWorkletProcessorHostObject(const std::shared_ptr<AudioWorkletProcessor> &processor)
      : processor_(processor) {}

  std::shared_ptr<AudioWorkletProcessor> getProcessor() {
    return processor_;
  }

 private:
  std::shared_ptr<AudioWorkletProcessor> processor_;
};
} // namespace audioapi
