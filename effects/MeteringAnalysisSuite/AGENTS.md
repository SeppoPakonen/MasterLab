# Metering Analysis Suite Effect Stub

## Reference
- Inspired by: Metering & Analysis
- Vendor: Waves
- Source catalog: Dorrough Mono, Dorrough Stereo, PAZ. Frequency Stereo, PAZ: Analyzer Stereo, PAZ: Frequency Mono, PAZ: Meters Mono, PAZ: Meters Stereo, PAZ: Position Stereo, WLM Meter 5.0, WLM Meter 5.1, WLM Meter Mono, WLM Meter Stereo, WLM Plus 5.0., WLM Plus 5.1, WLM Plus Mono, WLM Plus Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves Dorrough Meter
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Real-time metering and analysis for loudness, spectrum, and phase. Accurate emulation of Dorrough analog meters for broadcast loudness monitoring.
- Key features:
  - EBU/ITU loudness standards
  - True peak detection with oversampling
  - Spectral and vector scopes
  - Logging/export of measurement sessions
  - Displays VU + Peak simultaneously
  - Mono, stereo, and surround versions
  - Reference calibration options
  - Peak hold and clip indicators
- Core building blocks:
  - DSP::LoudnessMeter, DSP::TruePeakDetector, DSP::SpectrumAnalyzer, DSP::LoggingBackend, DSP::PeakDetector, DSP::VUIntegrator, DSP::MeterDisplay
- Signal/voice flow: Input → Dual-path meter (VU/Peak) → UI
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves PAZ Analyzer
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Real-time metering and analysis for loudness, spectrum, and phase. Spectrum, stereo, and phase analysis suite for mastering.
- Key features:
  - EBU/ITU loudness standards
  - True peak detection with oversampling
  - Spectral and vector scopes
  - Logging/export of measurement sessions
  - Frequency analyzer with variable averaging
  - Stereo position meter showing energy distribution
  - Phase scope and correlation meter
  - Save/recall snapshots for comparisons
- Core building blocks:
  - DSP::LoudnessMeter, DSP::TruePeakDetector, DSP::SpectrumAnalyzer, DSP::LoggingBackend, DSP::FFTAnalyzer, DSP::Goniometer, DSP::CorrelationMeter
- Signal/voice flow: Input → Analysis modules → UI
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves WLM Loudness Meter
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Real-time metering and analysis for loudness, spectrum, and phase. Broadcast-compliant loudness meter supporting EBU R128/ITU BS.1770.
- Key features:
  - EBU/ITU loudness standards
  - True peak detection with oversampling
  - Spectral and vector scopes
  - Logging/export of measurement sessions
  - Short-term, long-term, and momentary loudness readings
  - True peak detection with adjustable threshold
  - Logging and history export (CSV/automation)
  - Supports 5.1/5.0/2.0 channel configurations
- Core building blocks:
  - DSP::LoudnessMeter, DSP::TruePeakDetector, DSP::SpectrumAnalyzer, DSP::LoggingBackend
- Signal/voice flow: Input → Loudness/TP computation → UI/logging
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
