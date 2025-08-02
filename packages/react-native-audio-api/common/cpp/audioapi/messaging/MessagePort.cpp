#include <audioapi/messaging/MessagePort.h>

namespace audioapi {

MessagePort::MessagePort() = default;

void MessagePort::postMessage(const facebook::jsi::Value &message) {
  if (entangledPort_) {
    std::lock_guard<std::mutex> lock(entangledPort_->queueMutex_);
    entangledPort_->messageQueue_.push(facebook::jsi::Value(message));
    if (entangledPort_->onmessage) {
      // TODO: This should be called on the correct thread
      entangledPort_->onmessage.call(entangledPort_->onmessage.getRuntime(), message);
    }
  }
}

void MessagePort::close() {
  if (entangledPort_) {
    entangledPort_->entangledPort_ = nullptr;
    entangledPort_ = nullptr;
  }
}

void MessagePort::setEntangledPort(std::shared_ptr<MessagePort> port) {
  entangledPort_ = port;
}

} // namespace audioapi
