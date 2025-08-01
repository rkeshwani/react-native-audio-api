#pragma once

#include <jsi/jsi.h>
#include <string>
#include <unordered_map>
#include <memory>

namespace audioapi {

class AudioWorkletProcessor;

class AudioWorkletGlobalScope {
 public:
  AudioWorkletGlobalScope();

  void registerProcessor(
      const std::string &name,
      facebook::jsi::Function processorCtor);

  std::shared_ptr<AudioWorkletProcessor> createProcessor(
      const std::string &name,
      facebook::jsi::Runtime &runtime,
      facebook::jsi::Object &&options);

 private:
  std::unordered_map<std::string, facebook::jsi::Function> processorConstructors_;
};

} // namespace audioapi
