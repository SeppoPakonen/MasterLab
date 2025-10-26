# Tonebooster Essentials Effect Stub

## Reference
- Inspired by: ToneBooster Essentials
- Vendor: KRISTAL
- Source catalog: ToneBoaster

## Summary
Lightweight macro effects for quick corrective workflows bundled with KRISTAL/ToneBooster environments.

## Implementation Plan
### ToneBooster Essentials
- Category: restoration
- Sidechain: Context dependent; compressor module should expose external sidechain.
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. Bundle of ToneBooster mastering utilities (compressor, EQ, reverb) commonly bundled with KRISTAL. Implement as lightweight macro effect for quick corrective processing.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Preset-driven macro controls (Enhance, Warmth, Space)
  - Uses same base modules as main channel processors for consistency
  - Low CPU path for real-time rehearsal use
  - Per-module bypass to stack with other inserts
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::MacroController, DSP::ParametricEQ, DSP::Compressor, DSP::ReverbLite
- Signal/voice flow: Input → Macro EQ/Comp → Optional ambience → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
