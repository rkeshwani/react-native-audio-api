#pragma once

#include <audioapi/HostObjects/AudioNodeHostObject.h>
#include <audioapi/core/worklets/AudioWorkletNode.h>
#include <memory>

namespace audioapi {
using namespace facebook;

class AudioWorkletNodeHostObject : public AudioNodeHostObject {
 public:
  explicit AudioWorkletNodeHostObject(
      const std::shared_ptr<AudioWorkletNode> &node)
      : AudioNodeHostObject(node) {
    // TODO: Expose port and parameters
    // addGetters(JSI_EXPORT_PROPERTY_GETTER(AudioWorkletNodeHostObject, port));
    // addGetters(JSI_EXPORT_PROPERTY_GETTER(AudioWorkletNodeHostObject, parameters));
  }

  // JSI_PROPERTY_GETTER(port) {
  //   // TODO: return MessagePortHostObject
  //   return jsi::Value::undefined();
  // }

  // JSI_PROPERTY_GETTER(parameters) {
  //   // TODO: return AudioParamMapHostObject
  //   return jsi::Value::undefined();
  // }
};
} // namespace audioapi
