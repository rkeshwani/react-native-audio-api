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
  if (processor_) {
    // The Web Audio API spec says that the inputs to the process method should
    // be a sequence of frozen arrays of Float32Arrays. We can represent this
    // as a vector of AudioBus objects.
    std::vector<std::shared_ptr<AudioBus>> inputs;
    if (numberOfInputs > 0) {
      inputs.push_back(getProcessingInputBus(framesToProcess));
    }

    // The parameters object is a map of parameter names to Float32Arrays.
    // We can represent this as a jsi::Object.
    // TODO: Create the parameters object.
    jsi::Object parameters = jsi::Object(*context_->getRuntime());

    // The outputs object is a sequence of frozen arrays of Float32Arrays.
    // We can represent this as a vector of AudioBus objects.
    std::vector<std::shared_ptr<AudioBus>> outputs;
    if (numberOfOutputs > 0) {
      outputs.push_back(processingBus);
    }

    processor_->process(inputs, outputs, parameters);
  }
}

#ifdef TESTING
void AudioWorkletNode::setProcessor(
    std::shared_ptr<AudioWorkletProcessor> processor) {
  processor_ = processor;
}
#endif

} // namespace audioapi
