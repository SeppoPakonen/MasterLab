# Drum Bus Forge Effect Stub

## Reference
- Inspired by: Dedicated drum-bus processors
- Vendor analogues: Waves SSL E-Channel, XLN Audio RC-20 (Drum), Newfangled Elevate Saturate, JST Bus Glue Drums

## Summary
Purpose-built drum bus sculptor combining transient shaping, dynamics, saturation, parallel compression, and tone shaping, with macro workflows for punch vs glue profiles.

## Implementation Plan
### Transient & Dynamics Block
- Category: dynamics / transient shaping
- Sidechain: Internal kick/snare detection; optional external sidechain for ducking
- Processing blueprint: Dual-band transient designer feeding serial/parallel compressors with auto-release tuned for drums.
- Key features:
  - Attack/sustain split with per-band EQ to emphasise click vs body
  - Punch/glue macros balancing transient skimming with bus compression
  - Parallel compression mixer with blend and phase alignment
  - Sidechain filters to keep cymbals from driving compression
- Core building blocks:
  - DSP::AttackSustainSplitter
  - DSP::TransientDesigner
  - DSP::MultiBandCompressor
  - DSP::SidechainInput
  - DSP::AutoGain
- Signal/voice flow: Input → Attack/sustain split → Targeted dynamics → Parallel mix bus
- TODO:
  - Encode transient/dynamics stages into graph visualization with real-time meters
  - Provide presets tuned for different drum genres (rock, EDM, hip-hop)

### Saturation & Tone Stage
- Category: coloration
- Sidechain: N/A
- Processing blueprint: Multi-mode saturation (tape/tube/fet) with tilt EQ, harmonics emphasis, and stereo wideners.
- Key features:
  - Drive stages preceding/after dynamics with compensation gain
  - Tilt EQ and resonant filters to control mud vs brightness
  - Stereo enhancer/mono low end switch for tight kick handling
  - Dry bleed control to keep transients natural
- Core building blocks:
  - DSP::Saturator
  - DSP::EQTilt
  - DSP::StereoEnhancer
  - DSP::MixStage
  - DSP::MacroController
- Signal/voice flow: Dynamics output → Saturation modes → Tone shaping → Output blend
- TODO:
  - Link macro knobs to saturation + tone parameters through PluginSDK::ParameterSet
  - Emit node/edge metadata for visualization of dual drive paths
