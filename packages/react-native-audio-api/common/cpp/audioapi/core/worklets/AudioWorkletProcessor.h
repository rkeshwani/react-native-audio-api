#pragma once

#include <audioapi/core/AudioNode.h>
#include <jsi/jsi.h>
#include <vector>
#include <memory>

namespace audioapi {

class AudioBus;

class AudioWorkletProcessor {
 public:
  AudioWorkletProcessor() = default;
  virtual ~AudioWorkletProcessor() = default;

  virtual void process(
      const std::vector<std::shared_ptr<AudioBus>> &inputs,
      const std::vector<std::shared_ptr<AudioBus>> &outputs,
      const facebook::jsi::Object &parameters) = 0;
};

} // namespace audioapi
