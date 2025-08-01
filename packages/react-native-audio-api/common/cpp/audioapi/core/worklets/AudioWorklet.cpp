#include <audioapi/core/worklets/AudioWorklet.h>
#include <audioapi/core/worklets/AudioWorklet.h>
#include <audioapi/core/worklets/AudioWorkletGlobalScope.h>
#include <audioapi/core/BaseAudioContext.h>

namespace audioapi {

AudioWorklet::AudioWorklet(BaseAudioContext *context) : context_(context) {
  globalScope_ = std::make_shared<AudioWorkletGlobalScope>();
}

void AudioWorklet::addModule(const std::string &moduleURL) {
  // TODO: Create a new JSI runtime
  // TODO: Inject registerProcessor into the new runtime
  // TODO: Fetch the module code from moduleURL
  // TODO: Execute the module code in the new runtime
}

std::shared_ptr<AudioWorkletProcessor>
AudioWorklet::createProcessor(const std::string &name, jsi::Object &&options) {
  return globalScope_->createProcessor(name, std::move(options));
}

} // namespace audioapi
