# Restoration Noise Collection Effect Stub

## Reference
- Inspired by: Restoration & Noise
- Vendor: Waves
- Source catalog: W43 Mono, WA43 Stereo, WNS Mono, WNS Stereo, X-Click Mono, X-Click Stereo, X-Crackle Mono, X-Crackle Stereo, X-Hum Mono, X-Hum Stereo, X-Noise Mono, X-Noise Stereo, Z-Noise Mono, Z-Noise Stereo, NS1 Mono, NS1 Stereo, DeBreath Mono

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves W43 Noise Reduction
- Category: restoration
- Sidechain: N/A
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. W43 broadband noise reducer inspired by Dolby Cat43 hardware.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Four bands with sliders for quick reduction
  - Level-dependent gating to avoid pumping
  - Adaptive release for dialog
  - Low latency for post-production
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::MultiBandNoiseReducer, DSP::AdaptiveRelease
- Signal/voice flow: Input → 4-band noise reducer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves WNS Noise Suppressor
- Category: restoration
- Sidechain: N/A
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. WNS provides real-time multi-band noise suppression tailored for dialog.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Six fixed bands with threshold per band
  - Adaptive thresholds with learn function
  - Zero-latency for production sound
  - Automation-friendly sliders
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::MultiBandNoiseReducer
- Signal/voice flow: Input → 6-band suppression → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves X Restoration
- Category: restoration
- Sidechain: N/A
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. X-series (Click, Crackle, Hum, Noise) addressing specific artifacts individually.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Click uses transient detection/interpolation
  - Crackle handles sustained micro transients
  - Hum provides multi-harmonic notch removal
  - Noise offers broadband spectral gating
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::ClickDetector, DSP::HarmonicNotch
- Signal/voice flow: Input → Module-specific restoration → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Z-Noise
- Category: restoration
- Sidechain: N/A
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. Advanced noise reduction with dynamic noise profile updating.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Dynamic noise learning adapts over time
  - Transient preservation mode
  - Smoothing to avoid musical noise
  - Broadband and multi-band views
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::DynamicNoiseProfile, DSP::SmoothingFilter
- Signal/voice flow: Input → Adaptive spectral suppression → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves NS1
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Single-fader noise suppressor using statistical modeling.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - One-knob control adjusting reduction automatically
  - Low latency for live broadcast
  - Intelligibility preservation algorithm
  - Meter displays reduction amount
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::StatisticalNoiseReducer, DSP::MeterBlock
- Signal/voice flow: Input → Statistical noise estimation → Gain reduction → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves DeBreath
- Category: restoration
- Sidechain: Internal dual path for breath vs voice detection.
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. Automatically attenuates vocal breath noises while preserving phrasing.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - Split into target (breath) and voice (rest) with level sliders
  - Histogram to visualise detection confidence
  - Use same detector as C1 for consistent keying
  - Preset library for male/female dialog and singing
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::DualBandDetector, DSP::GainComputer, DSP::MixStage
- Signal/voice flow: Input → Breath/voice classifier → Gain reduction on breath path → Recombine → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
