# Granular Texture FX Effect Stub

## Reference
- Inspired by: Creative granular/time-warp processors
- Vendor analogues: Output Portal, Sugar Bytes Aperture, Ableton Grain Delay

## Summary
Real-time granular processing environment for transforming pads, vocals, and percussion into evolving textures. Supports time-stretch, pitch warp, randomisation, and modulation-driven grain motion with visual graph feedback.

## Implementation Plan
### Grain Engine
- Category: creative FX / granular
- Sidechain: Optional modulation sidechain for envelope follower
- Processing blueprint: Multi-grain engine with stochastic grain scheduling, per-grain pitch/position randomisation, and feedback network.
- Key features:
  - Up to 8 simultaneous grain emitters with independent density envelopes
  - Grain freeze, reverse, and spray controls tied to macro knobs
  - Spectral blur and diffusion modules for pad-like results
  - MIDI note tracking to quantise grain pitch to scales
- Core building blocks:
  - DSP::GranularEngine
  - DSP::RandomEventScheduler
  - DSP::ModMatrix
  - DSP::FilterBank
  - DSP::FeedbackNetwork
- Signal/voice flow: Input buffer → Grain scheduler → Grain renderers → Diffusion/feedback → Output mix
- TODO:
  - Encode grain emitters and diffusion nodes into GraphVisualization with active counts
  - Implement tempo-sync random seed handling for repeatable playback

### Macro & Modulation Layer
- Category: modulation
- Sidechain: External signal can modulate grain density (envelope follower)
- Processing blueprint: Macro controllers mapped to multi-parameter sweeps, plus step sequencer and LFOs driving grain parameters.
- Key features:
  - XY performance pad for blend vs chaos macros
  - Step sequencer controlling grain playback position and density
  - Envelope follower from sidechain to duck or excite grains
  - Preset morphing between macro scenes
- Core building blocks:
  - DSP::MacroController
  - DSP::MotionSequencer
  - DSP::SceneMorph
  - DSP::EnvelopeFollower
  - UI::XYPAD integration via PluginSDK
- Signal/voice flow: Modulation sources → ModMatrix → Grain engine parameter inputs
- TODO:
  - Surface modulation graph edges with different colours for audio vs control signals
  - Coordinate with AudioUI for XY pad visual feedback
