import { IAudioWorkletNode } from '../interfaces';
import AudioNode from './AudioNode';
import BaseAudioContext from './BaseAudioContext';

export default class AudioWorkletNode extends AudioNode {
  // TODO: Implement port and parameters
  constructor(context: BaseAudioContext, name: string, options?: any) {
    // TODO: Get native node from context
    super(context, {} as IAudioWorkletNode);
  }
}
