import React from 'react';
import { View, Button } from 'react-native';
import { AudioContext, AudioWorkletNode, OscillatorNode } from 'react-native-audio-api';

const workletScript = `
class MyProcessor extends AudioWorkletProcessor {
  process(inputs, outputs, parameters) {
    const output = outputs[0];
    output.forEach(channel => {
      for (let i = 0; i < channel.length; i++) {
        channel[i] = Math.random() * 2 - 1;
      }
    });
    return true;
  }
}

registerProcessor('my-processor', MyProcessor);
`;

const AudioWorkletExample = () => {
  const [context, setContext] = React.useState<AudioContext | null>(null);

  const handlePress = async () => {
    if (context) {
      await context.close();
      setContext(null);
      return;
    }

    const newContext = new AudioContext();
    setContext(newContext);

    // This is a mock implementation of addModule
    // In a real scenario, this would load a file from a URL
    const addModule = () => {
      return new Promise<void>((resolve) => {
        // @ts-ignore
        newContext.audioWorklet._native.addModule(workletScript);
        resolve();
      });
    };

    await addModule();

    const oscillator = new OscillatorNode(newContext);
    const workletNode = new AudioWorkletNode(newContext, 'my-processor');

    oscillator.connect(workletNode).connect(newContext.destination);
    oscillator.start();
  };

  return (
    <View>
      <Button
        title={context ? 'Stop' : 'Start'}
        onPress={handlePress}
      />
    </View>
  );
};

export default AudioWorkletExample;
