import { IAudioWorklet } from '../interfaces';

export default class AudioWorklet {
  private readonly _native: IAudioWorklet;

  constructor(native: IAudioWorklet) {
    this._native = native;
  }

  addModule(moduleURL: string): Promise<void> {
    return this._native.addModule(moduleURL);
  }
}
