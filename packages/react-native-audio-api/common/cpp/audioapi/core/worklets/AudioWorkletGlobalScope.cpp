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

void AudioWorkletGlobalScope::registerProcessor(
    const std::string &name,
    facebook::jsi::Function &processorCtor,
    facebook::jsi::Runtime &runtime) {
  if (name.empty()) {
    throw facebook::jsi::JSIException("Processor name cannot be empty");
  }

  if (processorConstructors_.count(name)) {
    throw facebook::jsi::JSIException("Processor with name " + name + " already registered");
  }

  if (!processorCtor.isFunction()) {
    throw facebook::jsi::JSIException("processorCtor must be a function");
  }

  auto prototype = processorCtor.getProperty(runtime, "prototype");
  if (!prototype.isObject()) {
    throw facebook::jsi::JSIException("processorCtor must have a prototype property that is an object");
  }

  processorConstructors_[name] = std::move(processorCtor);
}

std::shared_ptr<AudioWorkletProcessor> AudioWorkletGlobalScope::createProcessor(
    const std::string &name,
    facebook::jsi::Runtime &runtime,
    facebook::jsi::Object &&options) {
  if (!processorConstructors_.count(name)) {
    throw facebook::jsi::JSIException("Processor with name " + name + " not found");
  }

  auto &ctor = processorConstructors_.at(name);
  auto processorHostObject = ctor.callAsConstructor(std::move(options))
    .asObject(runtime)
    .asHostObject<AudioWorkletProcessorHostObject>(runtime);

  return processorHostObject->getProcessor();
}

} // namespace audioapi
