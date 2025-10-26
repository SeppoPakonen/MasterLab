# Codec Preview Suite Effect Stub

## Reference
- Inspired by: Mastering codec previewers
- Vendor analogues: iZotope Ozone Codec Preview, Sonnox Fraunhofer Pro-Codec, NUGEN MasterCheck

## Summary
Utility plug-in that previews lossy codec side-effects, loudness compliance, and playback translation in real time. Provides AB compare, dither, and integrated loudness metering to validate masters for streaming platforms.

## Implementation Plan
### Codec Simulation Engine
- Category: analysis / utility
- Sidechain: Optional reference track for AB
- Processing blueprint: Encodes audio through selectable codecs, then decodes for AB comparison while exposing codec artifacts.
- Key features:
  - Fraunhofer AAC, MP3, Ogg Vorbis, Opus emulation with adjustable bitrate
  - Auto loudness matching between original and encoded version
  - Delta output to audition codec artifacts
  - Offline batch export hooks for final verification
- Core building blocks:
  - DSP::CodecPreview
  - DSP::AutoGain
  - DSP::DeltaMonitor
  - DSP::PresetManager
  - DSP::Analyzer (for aliasing/residual analysis)
- Signal/voice flow: Input → Codec encode/decode lanes (A/B) → Loudness matching → Output / Delta bus
- TODO:
  - Populate GraphVisualization with original vs encoded nodes and delta branch
  - Integrate with FileIO pipeline for offline export (future)

### Loudness & Compliance Metering
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Real-time loudness, true-peak, and streaming compliance checks with platform presets.
- Key features:
  - LUFS integrated, short-term, momentary meters + true peak detection
  - Streaming service presets (Spotify, Apple Music, YouTube, Broadcast) with tolerance indicators
  - Phase correlation and mono-compatibility readouts
  - Report export (CSV/JSON) for QC logs
- Core building blocks:
  - DSP::LUFSMeter
  - DSP::TruePeakDetector
  - DSP::CorrelationMeter
  - DSP::LoggingBackend
  - UI::MeterBridge integration via PluginSDK graph
- Signal/voice flow: Input taps → Metering suite → UI/log output
- TODO:
  - Expose measurement data through AnalyzerTap for UI meter bridge
  - Add preset management for service profiles
