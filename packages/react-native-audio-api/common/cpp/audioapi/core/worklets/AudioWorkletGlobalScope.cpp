#include <audioapi/core/worklets/AudioWorkletGlobalScope.h>
#include <audioapi/core/worklets/AudioWorkletGlobalScope.h>
#include <audioapi/core/worklets/AudioWorkletProcessor.h>

namespace audioapi {

AudioWorkletGlobalScope::AudioWorkletGlobalScope() = default;

void AudioWorkletGlobalScope::registerProcessor(
    const std::string &name,
    facebook::jsi::Function processorCtor) {
  if (name.empty()) {
    // TODO: Throw NotSupportedError
    return;
  }

  if (processorConstructors_.count(name)) {
    // TODO: Throw NotSupportedError
    return;
  }

  // TODO: Validate processorCtor

  processorConstructors_[name] = std::move(processorCtor);
}

#include <audioapi/HostObjects/AudioWorkletProcessorHostObject.h>

std::shared_ptr<AudioWorkletProcessor> AudioWorkletGlobalScope::createProcessor(
    const std::string &name,
    facebook::jsi::Runtime &runtime,
    facebook::jsi::Object &&options) {
  if (!processorConstructors_.count(name)) {
    // TODO: Throw InvalidStateError
    return nullptr;
  }

  auto &ctor = processorConstructors_.at(name);
  auto processorHostObject = ctor.callAsConstructor(std::move(options))
    .asObject(runtime)
    .asHostObject<AudioWorkletProcessorHostObject>(runtime);

  return processorHostObject->getProcessor();
}

} // namespace audioapi
