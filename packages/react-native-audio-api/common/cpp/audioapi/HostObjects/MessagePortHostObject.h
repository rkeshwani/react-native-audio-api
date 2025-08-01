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
  }

  JSI_HOST_FUNCTION(postMessage) {
    port_->postMessage(args[0]);
    return jsi::Value::undefined();
  }

  JSI_HOST_FUNCTION(close) {
    port_->close();
    return jsi::Value::undefined();
  }

 private:
  std::shared_ptr<MessagePort> port_;
};
} // namespace audioapi
