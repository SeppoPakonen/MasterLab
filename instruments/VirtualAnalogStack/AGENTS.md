# Virtual Analog Stack Instrument Stub

## Reference
- Inspired by: Sylenth1
- Vendor: LennarDigital
- Source catalog: Sylenth1

## Implementation Plan
### LennarDigital Sylenth1
- Category: virtual analog
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Four-oscillator virtual analog synth with extensive unison, dual filters, and modulation routing.
- Key features:
  - Oscillator groups A/B each with eight-voice unison and stereo spread
  - Dual multimode filters with serial/parallel routing and drive
  - Two ADSR envelopes, two LFOs, and modulation matrix with sources/targets
  - Built-in FX (distortion, chorus, EQ, delay, reverb, compressor)
- Core building blocks:
  - Synth::OscillatorVA, Synth::UnisonStack, Synth::FilterCascade, Synth::ModMatrix, Synth::EnvelopeBank, FX::InsertRack
- Signal/voice flow: Note on → VoiceManager → Oscillator banks A/B (unison) → Filters A/B → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
