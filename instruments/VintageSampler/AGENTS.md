# Vintage Sampler Instrument Stub

## Reference
- Inspired by: TAL Sampler
- Vendor: Togu Audio Line
- Source catalog: TAL-Sampler

## Implementation Plan
### TAL-Sampler
- Category: sampler
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Sample engine with vintage DAC models, analog filters, time-stretch, and modulation routing.
- Key features:
  - DAC emulations (AM6070, S1200, MPC60) for coloration
  - Four sample layers with independent loop, start, and tuning controls
  - Mod matrix with 4 sources × 10 destinations plus two LFOs
  - Integrated FX (reverb, delay, chorus, bit-crusher)
- Core building blocks:
  - Sample::StreamEngine, Sample::VintageDAC, Synth::AnalogFilter, Synth::ModMatrix, FX::InsertRack
- Signal/voice flow: Note/trigger → Sample playback with DAC coloration → Analog-modeled filter/amp → FX chain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
