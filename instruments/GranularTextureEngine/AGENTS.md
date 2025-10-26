# Granular Texture Engine Instrument Stub

## Reference
- Inspired by: Granular pad instruments and sample cloud synthesizers
- Vendor analogues: Spectrasonics Omnisphere (Granular), Audio Damage Quanta, Steinberg Padshop

## Summary
Polyphonic granular instrument capable of evolving soundscapes from sample sources. Supports macro morphing, modulation scenes, and host-synchronised grain motion with visualized node graphs.

## Implementation Plan
### Grain Source & Voice Architecture
- Category: ambient / texture instrument
- Sidechain: N/A (MIDI controlled)
- Processing blueprint: Per-voice granular emitter pulling from sample pool with position/size/pan modulation and diffusion reverb tail.
- Key features:
  - Multi-layer sample slots with per-layer start/end, tuning, and randomisation
  - Voice manager supporting MPE for per-note grain modulation
  - Diffusion reverb and shimmer chain inside voice architecture
  - Macro morph across A/B scenes for performance transitions
- Core building blocks:
  - Synth::VoiceManager
  - Sample::StreamEngine
  - DSP::GranularEngine
  - DSP::SceneMorph
  - DSP::DiffusionEngine
- Voice graph: Note on → Voice allocation → Grain emitter → Modulated filter/amp → Diffusion tail → Output bus
- TODO:
  - Populate PluginSDK::GraphVisualization with per-layer nodes and modulation edges
  - Integrate with UI::XYPAD for macro morphing control

### Performance & Modulation
- Category: modulation / macro control
- Sidechain: Envelope follower from audio-in optional for reactivity
- Processing blueprint: Step sequencer and LFOs drive grain density, pitch, and pan while macros tie to global textures.
- Key features:
  - Motion sequencer driving grain count, spread, and filter sweeps
  - Randomisation dice controlling selected parameters
  - MIDI CC/MPE mapping with per-voice macro infusion
  - Visualization of active modulation lanes for performer feedback
- Core building blocks:
  - DSP::MotionSequencer
  - DSP::ModMatrix
  - DSP::MacroController
  - Automation::MotionDesigner hooks
  - UI::MacroSurface / UI::SceneManager integration
- TODO:
  - Define modulation graph nodes (sequencer, LFOs, macros) for visualization overlay
  - Provide preset schema referencing EFFECTS/INSTRUMENTS blueprint entries
