#pragma once

#include <audioapi/jsi/JsiHostObject.h>
#include <audioapi/messaging/MessagePort.h>
#include <memory>

namespace audioapi {
using namespace facebook;

class MessagePortHostObject : public JsiHostObject {
 public:
  explicit MessagePortHostObject(const std::shared_ptr<MessagePort> &port)
      : port_(port) {
    addFunctions(
        JSI_EXPORT_FUNCTION(MessagePortHostObject, postMessage),
        JSI_EXPORT_FUNCTION(MessagePortHostObject, close));

    addGetters(JSI_EXPORT_PROPERTY_GETTER(MessagePortHostObject, onmessage));
    addSetters(JSI_EXPORT_PROPERTY_SETTER(MessagePortHostObject, onmessage));
  }

  JSI_HOST_FUNCTION(postMessage) {
    port_->postMessage(args[0]);
    return jsi::Value::undefined();
  }

  JSI_HOST_FUNCTION(close) {
    port_->close();
    return jsi::Value::undefined();
  }

  JSI_PROPERTY_GETTER(onmessage) {
    return jsi::Value(runtime, port_->onmessage);
  }

  JSI_PROPERTY_SETTER(onmessage) {
    port_->onmessage = value.asObject(runtime).asFunction(runtime);
  }

 private:
  std::shared_ptr<MessagePort> port_;
};
} // namespace audioapi
