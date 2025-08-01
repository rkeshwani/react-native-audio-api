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

std::shared_ptr<AudioWorkletProcessor> AudioWorkletGlobalScope::createProcessor(
    const std::string &name,
    facebook::jsi::Object &&options) {
  // TODO: Implement processor creation
  return nullptr;
}

} // namespace audioapi
