#pragma once

#include <audioapi/core/AudioNode.h>
#include <audioapi/messaging/MessagePort.h>
#include <audioapi/core/AudioParam.h>
#include <jsi/jsi.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace audioapi {

class AudioWorkletProcessor;

class AudioWorkletNode : public AudioNode {
 public:
  explicit AudioWorkletNode(
      BaseAudioContext *context,
      const std::string &name,
      const facebook::jsi::Object &options);

  std::shared_ptr<MessagePort> getPort() const;
  std::unordered_map<std::string, std::shared_ptr<AudioParam>> getParameters() const;

 protected:
  void processNode(
      const std::shared_ptr<AudioBus> &processingBus,
      int framesToProcess) override;

#ifdef TESTING
  void setProcessor(std::shared_ptr<AudioWorkletProcessor> processor);
#endif

 private:
  std::shared_ptr<AudioWorkletProcessor> processor_;
  std::shared_ptr<MessagePort> port_;
  std::unordered_map<std::string, std::shared_ptr<AudioParam>> parameters_;
};

} // namespace audioapi
