#include <audioapi/core/worklets/AudioWorkletProcessor.h>
#include <audioapi/HostObjects/MessagePortHostObject.h>

namespace audioapi {

AudioWorkletProcessor::AudioWorkletProcessor(const facebook::jsi::Object &options) {
  auto runtime = options.getRuntime();
  auto processorOptions = options.getProperty(runtime, "processorOptions").asObject(runtime);
  auto portHostObject = processorOptions.getProperty(runtime, "port")
    .asObject(runtime)
    .asHostObject<MessagePortHostObject>(runtime);
  port_ = portHostObject->getPort();
}

} // namespace audioapi
