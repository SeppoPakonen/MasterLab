# Modular Guitar Rig Effect Stub

## Reference
- Inspired by: Guitar Rig
- Vendor: Native Instruments
- Source catalog: Guitar Rig 6 Pro, Guitar Rig 6 Player

## Implementation Plan
### Native Instruments Guitar Rig
- Category: multi-fx
- Sidechain: Envelope followers and sidechain modulators accept external key input.
- Processing blueprint: Modular rack hosting amps, cabinets, effects, and modulators with drag-and-drop routing and macro control macros.
- Key features:
  - Component-level amp modeling with matched cabinet IRs
  - Split/Merge routing for parallel chains and wet/dry blends
  - Macro controls and automation per rack, plus global snapshots
  - Modulation sources (LFO, envelope, step sequencer) routable to any parameter
- Core building blocks:
  - DSP::RackGraph, DSP::AmpModel, DSP::CabConvolver, DSP::FXModule, DSP::ModSource, DSP::MacroController
- Signal/voice flow: Input → Rack graph evaluation (serial/parallel) with modulators → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
