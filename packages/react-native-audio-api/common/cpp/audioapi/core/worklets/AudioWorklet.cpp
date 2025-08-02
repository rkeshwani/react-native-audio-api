#include <audioapi/core/worklets/AudioWorklet.h>
#include <audioapi/core/worklets/AudioWorklet.h>
#include <audioapi/core/worklets/AudioWorkletGlobalScope.h>
#include <audioapi/core/BaseAudioContext.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>
#include <fstream>
#include <streambuf>
#include <thread>

namespace audioapi {

using namespace facebook;

AudioWorklet::AudioWorklet(BaseAudioContext *context) : context_(context) {
  globalScope_ = std::make_shared<AudioWorkletGlobalScope>();
}

void AudioWorklet::addModule(
    const std::string &script,
    std::function<void()> onsuccess,
    std::function<void(const std::string &)> onerror) {
  std::thread([this, script, onsuccess, onerror]() {
    try {
      // 1. Create a new JSI runtime
      runtime_ = facebook::hermes::makeHermesRuntime();

      // 2. Inject registerProcessor into the new runtime
      auto registerProcessor = jsi::Function::createFromHostFunction(
          *runtime_,
          jsi::PropNameID::forAscii(*runtime_, "registerProcessor"),
          2,
          [this](
              jsi::Runtime &runtime,
              const jsi::Value &thisValue,
              const jsi::Value *args,
              size_t count) -> jsi::Value {
            auto name = args[0].asString(runtime).utf8(runtime);
            auto processorCtor = args[1].asObject(runtime).asFunction(runtime);
          globalScope_->registerProcessor(name, processorCtor, runtime);
            return jsi::Value::undefined();
          });
      runtime_->global().setProperty(*runtime_, "registerProcessor", registerProcessor);

      // 3. Execute the module code in the new runtime
      runtime_->evaluateJavaScript(std::make_unique<jsi::StringBuffer>(script), "");

      onsuccess();
    } catch (const std::exception &e) {
      onerror(e.what());
    }
  }).detach();
}

std::shared_ptr<AudioWorkletProcessor>
AudioWorklet::createProcessor(const std::string &name, jsi::Object &&options) {
  return globalScope_->createProcessor(name, *runtime_, std::move(options));
}

jsi::Runtime &AudioWorklet::getRuntime() {
  return *runtime_;
}

} // namespace audioapi
