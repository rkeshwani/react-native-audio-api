#pragma once

#include <audioapi/HostObjects/AudioNodeHostObject.h>
#include <audioapi/core/worklets/AudioWorkletNode.h>
#include <audioapi/HostObjects/MessagePortHostObject.h>
#include <audioapi/HostObjects/AudioParamMapHostObject.h>
#include <memory>

namespace audioapi {
using namespace facebook;

class AudioWorkletNodeHostObject : public AudioNodeHostObject {
 public:
  explicit AudioWorkletNodeHostObject(
      const std::shared_ptr<AudioWorkletNode> &node)
      : AudioNodeHostObject(node) {
    addGetters(
        JSI_EXPORT_PROPERTY_GETTER(AudioWorkletNodeHostObject, port),
        JSI_EXPORT_PROPERTY_GETTER(AudioWorkletNodeHostObject, parameters));
  }

  JSI_PROPERTY_GETTER(port) {
    auto port = std::static_pointer_cast<AudioWorkletNode>(node_)->getPort();
    auto portHostObject = std::make_shared<MessagePortHostObject>(port);
    return jsi::Object::createFromHostObject(runtime, portHostObject);
  }

  JSI_PROPERTY_GETTER(parameters) {
    auto params = std::static_pointer_cast<AudioWorkletNode>(node_)->getParameters();
    auto paramsHostObject =
        std::make_shared<AudioParamMapHostObject>(std::move(params));
    return jsi::Object::createFromHostObject(runtime, paramsHostObject);
  }
};
} // namespace audioapi
