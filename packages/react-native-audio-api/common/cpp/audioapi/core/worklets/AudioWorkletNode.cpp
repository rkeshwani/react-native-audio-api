#include <audioapi/core/worklets/AudioWorkletNode.h>
#include <audioapi/core/worklets/AudioWorkletProcessor.h>
#include <audioapi/core/BaseAudioContext.h>
#include <audioapi/core/worklets/AudioWorklet.h>
#include <audioapi/utils/AudioBus.h>
#include <audioapi/HostObjects/MessagePortHostObject.h>

namespace audioapi {

AudioWorkletNode::AudioWorkletNode(
    BaseAudioContext *context,
    const std::string &name,
    const jsi::Object &options)
    : AudioNode(context) {
  auto worklet = context->getAudioWorklet();

  auto port1 = std::make_shared<MessagePort>();
  auto port2 = std::make_shared<MessagePort>();
  port1->setEntangledPort(port2);
  port2->setEntangledPort(port1);

  port_ = port1;

  auto processorOptions = jsi::Object(worklet->getRuntime());
  processorOptions.setProperty(
      worklet->getRuntime(),
      "port",
      jsi::Object::createFromHostObject(
          worklet->getRuntime(), std::make_shared<MessagePortHostObject>(port2)));

  auto newOptions = jsi::Object(options);
  newOptions.setProperty(worklet->getRuntime(), "processorOptions", std::move(processorOptions));

  processor_ = worklet->createProcessor(name, worklet->getRuntime(), std::move(newOptions));
}

std::shared_ptr<MessagePort> AudioWorkletNode::getPort() const {
  return port_;
}

std::unordered_map<std::string, std::shared_ptr<AudioParam>>
AudioWorkletNode::getParameters() const {
  return parameters_;
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
