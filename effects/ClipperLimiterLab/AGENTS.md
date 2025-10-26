# Clipper Limiter Lab Effect Stub

## Reference
- Inspired by: Modern clipper/limiter combinations for electronic and pop mastering
- Vendor analogues: StandardCLIP, DMG Limitless, FabFilter Pro-L, Kazrog KClip

## Summary
Hybrid soft/hard clipper feeding intelligent look-ahead limiter with multiband transient preservation. Designed to sit after mix-bus compressors to achieve competitive loudness without sacrificing transients.

## Implementation Plan
### Multistage Clipping
- Category: mastering / loudness
- Sidechain: Optional external reference for delta monitoring
- Processing blueprint: Two-stage clipping (soft pre-clipping + programmable hard clip) with per-band weighting and oversampled ISP detection.
- Key features:
  - Variable knee curves with bias toward even/odd harmonic emphasis
  - Pre-emphasis / de-emphasis EQ to balance clipped spectra
  - Mid/side and dual-mono operation for stereo mastering
  - Delta listen and clip audition to fine-tune distortion character
- Core building blocks:
  - DSP::LookaheadBuffer
  - DSP::PeakDetector
  - DSP::ClipperStage
  - DSP::MidSideMatrix
  - DSP::DeltaMonitor
- Signal/voice flow: Input → Soft clip stage → Hard clip stage → ISP detector → Output
- TODO:
  - Expose per-band drive controls through PluginSDK parameters
  - Populate GraphVisualization nodes for clip stages and detection taps

### Intelligent Limiter
- Category: mastering
- Sidechain: External reference for loudness match (optional)
- Processing blueprint: Look-ahead brickwall limiter with dynamic attack/release shaping and transient emphasis path.
- Key features:
  - Adaptive release curves keyed to programme content
  - Transient recovery path with blend control
  - Loudness target helper with LUFS meters
  - Dither/noise shaping stage for output formatting
- Core building blocks:
  - DSP::GainComputer
  - DSP::AutoRelease
  - DSP::TransientPreserver
  - DSP::LUFSMeter
  - DSP::DitherEngine
- Signal/voice flow: Clipped input → Lookahead analysis → Gain computer → Transient blend → Output formatter
- TODO:
  - Integrate limiter state into visualization layer for real-time envelope preview
  - Share loudness metrics with UI meters via AnalyzerTap
