#pragma once

#include <memory>
#include <string>
#include <jsi/jsi.h>

namespace audioapi {

class BaseAudioContext;
class AudioWorkletGlobalScope;

class AudioWorklet {
 public:
  explicit AudioWorklet(BaseAudioContext *context);

  void addModule(const std::string &script);

  std::shared_ptr<AudioWorkletProcessor>
  createProcessor(const std::string &name, facebook::jsi::Object &&options);

  facebook::jsi::Runtime &getRuntime();

 private:
  BaseAudioContext *context_;
  std::shared_ptr<AudioWorkletGlobalScope> globalScope_;
  std::unique_ptr<facebook::jsi::Runtime> runtime_;
};

} // namespace audioapi
