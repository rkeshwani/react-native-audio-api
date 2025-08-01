#pragma once

#include <memory>
#include <string>

namespace audioapi {

class BaseAudioContext;
class AudioWorkletGlobalScope;

class AudioWorklet {
 public:
  explicit AudioWorklet(BaseAudioContext *context);

  void addModule(const std::string &moduleURL);

  std::shared_ptr<AudioWorkletProcessor>
  createProcessor(const std::string &name, jsi::Object &&options);

 private:
  BaseAudioContext *context_;
  std::shared_ptr<AudioWorkletGlobalScope> globalScope_;
};

} // namespace audioapi
