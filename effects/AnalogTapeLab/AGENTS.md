# Analog Tape Lab Effect Stub

## Reference
- Inspired by: Tape deck, cassette, and mastering tape simulation chains
- Vendor analogues: Universal Audio Ampex ATR-102, Softube Tape, Waves Kramer Master Tape

## Summary
Stereo tape coloration rack with selectable machine models, tape formulations, and transport conditions. Targets mix-bus and stem processing where authentic tape compression, head bump, and noise sculpting are required.

## Implementation Plan
### Machine & Transport Modelling
- Category: saturation / mastering color
- Sidechain: N/A (internal envelope followers only)
- Processing blueprint: Dual-stage non-linear transfer (record + repro amps) with oversampled hysteresis model for tape compression, complemented by dynamic bias/flux controls.
- Key features:
  - Switchable machine archetypes (reel-to-reel, cassette, multitrack) with head gap variations
  - Tape speeds (7.5/15/30 ips) affecting EQ tilt and head bump
  - Bias/flux trim feeding hysteresis model for coloration vs fidelity workflows
  - Pre-emphasis/de-emphasis filters with calibration meter
  - Service panel exposing azimuth, crosstalk, and alignment drift
- Core building blocks:
  - DSP::NonlinearStage (record/repro amps)
  - DSP::HysteresisModel
  - DSP::TapeEQCurves
  - DSP::CalibrationMeter
  - DSP::WowFlutterModel
- Signal/voice flow: Input → Record amp saturation → Tape hysteresis loop (with wow/flutter modulation) → Repro EQ/amp → Output
- TODO:
  - Populate PluginSDK::GraphVisualization with machine/tape nodes and modulation edges
  - Implement dynamic oversampling manager for HQ/eco modes

### Tape Degradation & Artifacts
- Category: creative coloration
- Sidechain: None
- Processing blueprint: Parallel degradation engine layering hiss, asperity noise, dropouts, and crinkle events with tempo-sync randomisation.
- Key features:
  - Tape damage macros (crease, dropout, splice) affecting transient response
  - Asperity noise model with spectral tilt and bias-dependent amplitude
  - Dual wow/flutter LFOs plus random bump modulation routed through ModMatrix
  - Auto gain to maintain loudness despite saturation changes
- Core building blocks:
  - DSP::NoiseGenerator
  - DSP::DropoutModel
  - DSP::RandomEventScheduler
  - DSP::AutoGain
  - DSP::ModMatrix
- Signal/voice flow: Input tap → Parallel noise/degradation bus → Summing mixer with auto gain compensation
- TODO:
  - Expose per-band mix controls for parallel degradation path
  - Provide live graph overlay of active artifacts in visualization UI
