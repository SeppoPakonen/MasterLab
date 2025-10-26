# Restoration Noise Suite Effect Stub

## Reference
- Inspired by: Restoration & Noise
- Vendor: Steinberg
- Source catalog: DeClicker, DeNoiser, DeEsser, DeEsser Mono, DeEsser Stereo, SoftCipper

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg DeClicker
- Category: restoration
- Sidechain: N/A
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. Offline/real-time declicking using transient detection and interpolation.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Threshold and sensitivity per click size
  - Option to focus on crackle bursts
  - Audition mode to monitor removed material
  - Batch preset friendly for restoration workflows
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::ClickDetector, DSP::Interpolator, DSP::ArtifactMonitor
- Signal/voice flow: Input → Click detection → Interpolation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg DeNoiser
- Category: restoration
- Sidechain: N/A
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. Broadband noise reduction with learnable noise profile.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Learn function to capture noise fingerprint
  - Reduction and sensitivity per band
  - Artifact smoothing slider
  - Gate floor to avoid pumping
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::SmoothingFilter
- Signal/voice flow: Input → Spectral analysis → Noise attenuation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg/Waves DeEsser
- Category: dynamics
- Sidechain: Internal bandpass with listen; C1-sc variant accepts external.
- Processing blueprint: Split-band compressor aimed at sibilant range with frequency listen. Shared de-esser concept used by both Steinberg stock and Waves plug-ins.
- Key features:
  - Wide-band vs split-band modes
  - Frequency sweeping and audition
  - Auto/Manual threshold
  - Parallel mix for natural results
  - Wideband or split-band behaviour
  - Auto threshold calibration
  - Monitor S-only output
  - Use same detector as C1 for consistency
- Core building blocks:
  - DSP::SidechainBandpass, DSP::EnvelopeDetector, DSP::GainComputer, DSP::BlendStage
- Signal/voice flow: Input → Sibilant band detector → Gain reduction → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg SoftClipper
- Category: saturation
- Sidechain: N/A
- Processing blueprint: Waveshaping distortion with tone filters and oversampling. Soft clipping stage to shave peaks before limiting.
- Key features:
  - Selectable transfer curves (tube, transistor, diode)
  - Pre/post EQ tone sculpting
  - Mix control for parallel drive
  - Oversampling to reduce aliasing
  - Adjustable knee softness
  - Symmetric and asymmetric clipping modes
  - Pre-gain/trim for precise drive
  - Visual clip meter
- Core building blocks:
  - DSP::Oversampler, DSP::WaveShaper, DSP::EQStage, DSP::MixStage, DSP::SoftClipper, DSP::GainStage, DSP::MeterBlock
- Signal/voice flow: Input → Gain trim → Soft clipper → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
