# Sequence Fx Engine Effect Stub

## Reference
- Inspired by: Effectrix
- Vendor: Sugar Bytes
- Source catalog: Effectrix

## Implementation Plan
### Sugar Bytes Effectrix
- Category: sequenced fx
- Sidechain: N/A
- Processing blueprint: Step-sequenced multi-effect where each slot triggers different processors per subdivision, ideal for glitching and stutters.
- Key features:
  - 14 effect modules switchable per lane with per-step automation
  - 16-step sequencer with variable loop length and swing
  - Per-effect parameter automation envelopes
  - Scene snapshots for live recall and host automation
- Core building blocks:
  - DSP::StepSequencer, DSP::EffectSlot, DSP::TimeGate, DSP::GranularUnit, DSP::RoutingMatrix, UI::SceneManager
- Signal/voice flow: Input → Step gater → Per-step effect slot processing → Summing mixer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
