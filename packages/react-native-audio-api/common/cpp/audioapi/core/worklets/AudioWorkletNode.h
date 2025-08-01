#pragma once

#include <audioapi/core/AudioNode.h>
#include <jsi/jsi.h>
#include <memory>
#include <string>

namespace audioapi {

class AudioWorkletProcessor;

class AudioWorkletNode : public AudioNode {
 public:
  explicit AudioWorkletNode(
      BaseAudioContext *context,
      const std::string &name,
      const facebook::jsi::Object &options);

 protected:
  void processNode(
      const std::shared_ptr<AudioBus> &processingBus,
      int framesToProcess) override;

 private:
  std::shared_ptr<AudioWorkletProcessor> processor_;
};

} // namespace audioapi
