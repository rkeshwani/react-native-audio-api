#include <audioapi/messaging/MessagePort.h>

namespace audioapi {

MessagePort::MessagePort(std::shared_ptr<react::CallInvoker> callInvoker) : callInvoker_(callInvoker) {}

void MessagePort::postMessage(const facebook::jsi::Value &message) {
  if (entangledPort_) {
    entangledPort_->callInvoker_->invokeAsync([this, message]() {
      std::lock_guard<std::mutex> lock(entangledPort_->queueMutex_);
      entangledPort_->messageQueue_.push(facebook::jsi::Value(message));
      if (entangledPort_->onmessage) {
        entangledPort_->onmessage.call(entangledPort_->onmessage.getRuntime(), message);
      }
    });
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
