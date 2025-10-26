# Transient Eq Designer Effect Stub

## Reference
- Inspired by: Transient Control
- Vendor: Crave DSP
- Source catalog: Crave Transient EQ

## Implementation Plan
### Crave Transient EQ
- Category: dynamics
- Sidechain: External sidechain for keyed transient detection.
- Processing blueprint: Hybrid transient shaper and equalizer that separates attack vs sustain energy and processes them with independent EQ curves.
- Key features:
  - Dual-path attack/sustain analysis with adjustable window size
  - Per-band gain staging for attack vs sustain curves
  - Mid/side and stereo link controls for imaging-aware processing
  - Realtime spectrum and waveform scope for tuning detection thresholds
- Core building blocks:
  - DSP::AttackSustainSplitter, DSP::DynamicEQBand, DSP::MidSideMatrix, DSP::SpectrumScope, DSP::SidechainDetector
- Signal/voice flow: Input (and optional sidechain) → Attack/sustain decomposition → Band EQ per component → Recombination → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
