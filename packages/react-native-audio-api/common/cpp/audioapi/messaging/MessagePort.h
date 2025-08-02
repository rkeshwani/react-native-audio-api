#pragma once

#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <memory>

namespace audioapi {

class MessagePort {
 public:
  MessagePort(std::shared_ptr<react::CallInvoker> callInvoker);

  void postMessage(const facebook::jsi::Value &message);
  void close();

  void setEntangledPort(std::shared_ptr<MessagePort> port);

  facebook::jsi::Function onmessage;

 private:
  std::shared_ptr<MessagePort> entangledPort_;
  std::queue<facebook::jsi::Value> messageQueue_;
  std::mutex queueMutex_;
  std::shared_ptr<react::CallInvoker> callInvoker_;
};

} // namespace audioapi
