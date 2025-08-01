#pragma once

#include <jsi/jsi.h>
#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <memory>

namespace audioapi {

class MessagePort {
 public:
  MessagePort();

  void postMessage(const facebook::jsi::Value &message);
  void close();

  void setEntangledPort(std::shared_ptr<MessagePort> port);

  // TODO: Add onmessage event handler

 private:
  std::shared_ptr<MessagePort> entangledPort_;
  std::queue<facebook::jsi::Value> messageQueue_;
  std::mutex queueMutex_;
};

} // namespace audioapi
