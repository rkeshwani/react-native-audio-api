#pragma once

#include <audioapi/core/AudioNode.h>
#include <audioapi/messaging/MessagePort.h>
#include <jsi/jsi.h>
#include <vector>
#include <memory>

namespace audioapi {

class AudioBus;

class AudioWorkletProcessor {
 public:
  explicit AudioWorkletProcessor(const facebook::jsi::Object &options);
  virtual ~AudioWorkletProcessor() = default;

  virtual void process(
      const std::vector<std::shared_ptr<AudioBus>> &inputs,
      const std::vector<std::shared_ptr<AudioBus>> &outputs,
      const facebook::jsi::Object &parameters) = 0;

 protected:
  std::shared_ptr<MessagePort> port_;
};

} // namespace audioapi
