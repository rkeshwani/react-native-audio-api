#include <audioapi/messaging/MessagePort.h>

namespace audioapi {

MessagePort::MessagePort() = default;

void MessagePort::postMessage(const facebook::jsi::Value &message) {
  if (entangledPort_) {
    std::lock_guard<std::mutex> lock(entangledPort_->queueMutex_);
    entangledPort_->messageQueue_.push(facebook::jsi::Value(message));
  }
}

void MessagePort::close() {
  // TODO: Implement port closing
}

void MessagePort::setEntangledPort(std::shared_ptr<MessagePort> port) {
  entangledPort_ = port;
}

} // namespace audioapi
