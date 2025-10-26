# Layered Rompler Instrument Stub

## Reference
- Inspired by: Nexus Workstation
- Vendor: reFX
- Source catalog: Nexus 4, Nexus 3

## Implementation Plan
### reFX Nexus
- Category: rompler
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Sample-based workstation with 16-layer architecture, arpeggiator, trance gate, and macro controls.
- Key features:
  - Layer stack with per-layer amp/filter envelopes and velocity splits
  - Extensive arpeggiator and pattern sequencer with chord/rhythm lanes
  - Macro controls mapped to layer parameters for quick sound design
  - Onboard FX rack (delay, reverb, phaser, compressor) shared across layers
- Core building blocks:
  - Sample::StreamEngine, Synth::LayerStack, Synth::ModMatrix, Sequencer::TranceGate, Sequencer::ArpSequencer, FX::InsertRack
- Signal/voice flow: Note on → Layer stack (up to 16) → Filter/amp per layer → Shared FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
