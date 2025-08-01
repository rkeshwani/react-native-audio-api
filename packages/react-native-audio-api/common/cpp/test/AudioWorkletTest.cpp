#include <gtest/gtest.h>
#include <audioapi/core/OfflineAudioContext.h>
#include <audioapi/core/worklets/AudioWorkletNode.h>
#include <audioapi/core/worklets/AudioWorkletProcessor.h>
#include <audioapi/core/sources/AudioBufferSourceNode.h>
#include <audioapi/core/AudioBuffer.h>
#include <audioapi/utils/AudioBus.h>

namespace audioapi {

class PassthroughProcessor : public AudioWorkletProcessor {
 public:
  void process(
      const std::vector<std::shared_ptr<AudioBus>> &inputs,
      const std::vector<std::shared_ptr<AudioBus>> &outputs,
      const facebook::jsi::Object &parameters) override {
    if (inputs.empty() || outputs.empty()) {
      return;
    }
    auto inputBus = inputs[0];
    auto outputBus = outputs[0];
    for (int i = 0; i < inputBus->getNumberOfChannels(); i++) {
      auto inputChannel = inputBus->getChannel(i);
      auto outputChannel = outputBus->getChannel(i);
      memcpy(
          outputChannel->getData(),
          inputChannel->getData(),
          inputChannel->getLength() * sizeof(float));
    }
  }
};

TEST(AudioWorkletTest, Passthrough) {
  auto context = std::make_shared<OfflineAudioContext>(2, 44100, 44100);
  auto workletNode = std::make_shared<AudioWorkletNode>(context.get(), "passthrough", facebook::jsi::Object(*context->getRuntime()));

  // This is a mock. In a real scenario, the processor would be created by the
  // worklet global scope.
  auto processor = std::make_shared<PassthroughProcessor>();
  // workletNode->setProcessor(processor); // This method does not exist yet. I will add it.

  auto source = context->createBufferSource(false);
  auto buffer = BaseAudioContext::createBuffer(2, 44100, 44100);
  for (int i = 0; i < buffer->getNumberOfChannels(); i++) {
    auto channel = buffer->getChannelData(i);
    for (int j = 0; j < buffer->getLength(); j++) {
      channel[j] = static_cast<float>(j);
    }
  }
  source->setBuffer(buffer);

  source->connect(workletNode);
  workletNode->connect(context->getDestination());

  source->start();
  auto renderedBuffer = context->startRendering();

  for (int i = 0; i < buffer->getNumberOfChannels(); i++) {
    auto expected = buffer->getChannelData(i);
    auto actual = renderedBuffer->getChannelData(i);
    for (int j = 0; j < buffer->getLength(); j++) {
      ASSERT_EQ(expected[j], actual[j]);
    }
  }
}

} // namespace audioapi
