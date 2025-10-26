# Loudness Control Suite Effect Stub

## Reference
- Inspired by: Loudness Suite
- Vendor: APU
- Source catalog: APU Loudness Compressor, APU Loudness Limiter, APU Loudness Analyzer

## Implementation Plan
### APU Loudness Compressor
- Category: dynamics
- Sidechain: Optional external sidechain for weighting and ducking.
- Processing blueprint: Loudness-targeting compressor combining LUFS-weighted detection with look-ahead gain scheduling for transparent mix-bus control.
- Key features:
  - Integrated LUFS/I targets with delta monitoring
  - Short-term vs momentary ballistics with adaptive release
  - Target matching that writes automation or live trims
  - Look-ahead and true-peak limiting stage to prevent overs
- Core building blocks:
  - DSP::LUFSMeter, DSP::WeightingFilterBank, DSP::LookaheadBuffer, DSP::GainComputer, DSP::TruePeakLimiter
- Signal/voice flow: Input → K-weighted loudness analysis → Look-ahead gain computer → True-peak limiter → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### APU Loudness Limiter
- Category: dynamics
- Sidechain: Internal look-ahead only; no external sidechain.
- Processing blueprint: True-peak limiter focused on integrated loudness compliance with auto gain staging.
- Key features:
  - 10-100 ms look-ahead with oversampled ISP detection
  - Target loudness wizard with per-platform presets
  - Unity delta monitoring to audition limiting artifacts
  - Stage-aware release shaping to maintain punch
- Core building blocks:
  - DSP::LookaheadLimiter, DSP::ISPDetector, DSP::AutoGainScheduler, DSP::DeltaMonitor, DSP::MeterBridge
- Signal/voice flow: Input → Look-ahead buffer → ISP detection and gain reduction → Makeup gain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### APU Loudness Analyzer
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Loudness, dynamics, and true-peak measurement suite with offline report export.
- Key features:
  - K-weighted real-time, short-term, and integrated meters
  - True-peak and crest-factor plots with compliance flags
  - Time-based loudness history with markers and region export
  - Report generator for broadcast delivery
- Core building blocks:
  - DSP::LUFSMeter, DSP::TruePeakDetector, DSP::HistoryBuffer, DSP::ReportGenerator, UI::MeterBridge
- Signal/voice flow: Input → Weighting filters → Measurement accumulator → UI/logging
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
