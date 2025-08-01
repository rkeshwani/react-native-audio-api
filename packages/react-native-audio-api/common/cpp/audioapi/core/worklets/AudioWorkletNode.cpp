#include <audioapi/core/worklets/AudioWorkletNode.h>
#include <audioapi/core/worklets/AudioWorkletProcessor.h>
#include <audioapi/core/BaseAudioContext.h>
#include <audioapi/utils/AudioBus.h>

namespace audioapi {

AudioWorkletNode::AudioWorkletNode(
    BaseAudioContext *context,
    const std::string &name,
    const jsi::Object &options)
    : AudioNode(context) {
  auto worklet = context->getAudioWorklet();
  processor_ = worklet->createProcessor(name, jsi::Object(options));
}

void AudioWorkletNode::processNode(
    const std::shared_ptr<AudioBus> &processingBus,
    int framesToProcess) {
  // TODO: Implement processing
}

} // namespace audioapi
