# Hybrid FM Collection Instrument Stub

## Reference
- Inspired by: Modern FM + wavetable hybrids
- Vendor analogues: Kilohearts Phase Plant, Native Instruments FM8, Arturia Pigments (FM section)

## Summary
Modular FM and wavetable synthesis platform with node-based routing, macro morphing, and advanced modulation. Provides library of operator algorithms, wavetable blending, and per-layer FX.

## Implementation Plan
### Operator & Wavetable Layer
- Category: hybrid synthesis
- Sidechain: N/A
- Processing blueprint: Four FM operators plus two wavetable oscillators per layer, routable through modular graph with feedback paths.
- Key features:
  - Operator matrix with algorithm presets and user graph editing
  - Wavetable import, morphing, and formant shift
  - Per-layer filter stacks with serial/parallel options
  - Microtuning, MPE pitch modulation
- Core building blocks:
  - Synth::FMOperator
  - Synth::WavetableOsc
  - Synth::ModMatrix
  - Synth::FilterCascade
  - PluginSDK::GraphVisualization to expose operator graph
- Voice graph: Note → Operator matrix → Wavetable blend → Filter/drive → FX slots → Output
- TODO:
  - Encode operator/wavetable nodes + modulation edges for UI graph view
  - Provide algorithm preset descriptors for quick recall

### Modulation & Macro System
- Category: modulation
- Sidechain: Envelope follower (audio-in) optional
- Processing blueprint: Extensive modulation sources (envelopes, LFOs, random, sequencers) mapped via macro controllers and MPE lanes.
- Key features:
  - 8 assignable envelopes with loop segments
  - Multi-segment LFOs and function generators
  - Random per-voice mod + global sample & hold
  - Macro morph scenes for performance transitions
- Core building blocks:
  - DSP::ModMatrix
  - DSP::MotionSequencer
  - DSP::MacroController
  - UI::MacroSurface / UI::SceneManager
  - Automation::MotionDesigner integration
- TODO:
  - Expose modulation nodes/edges in GraphVisualization to allow interactive editing
  - Coordinate with AudioUI for drag-and-drop modulation assignments
