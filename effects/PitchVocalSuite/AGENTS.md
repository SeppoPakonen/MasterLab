# Pitch Vocal Suite Effect Stub

## Reference
- Inspired by: Pitch & Vocal Suite
- Vendor: Antares
- Source catalog: AutoTuneVST, AVOX CHOIR, AVOX DUO, AVOX PUNCH, AVOX SYBIL, AVOX THROAT

## Summary
Pitch-oriented processing; low-latency paths and high-quality formant handling are critical. Provide MIDI note integration where applicable.

## Current Status (2026-03-03)
- **Framework:** U++ with custom `PluginEditor` and `PluginHost` for DAW/Standalone integration.
- **Pitch Detection:** Functional FFT-based Autocorrelation engine (Wiener-Khinchin theorem).
- **UI:** Interactive Piano-Roll style `PitchGraphEditor` and real-time `WaveformStrip`.
- **CLI:** Support for `--test` and `--test-audio <path>` for offline analysis.
- **DSP:** Detection pipeline is functional; pitch-shifting correction is currently in development.

## Implementation Plan
### Antares Auto-Tune Pro
- Category: pitch/time
- Sidechain: Pitch detection only; no external audio sidechain.
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Modern pitch-correction engine with automatic and graph modes mirroring Auto-Tune Pro. Supports real-time low-latency operation and fine-grained pitch graph editing.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - Target scale/key with per-note retune speeds
  - Formant and throat modeling macros for natural tone
  - Graph mode for manual pitch/time curves
  - Humanize/vibrato tools to keep sustained notes transparent
- Core building blocks:
  - DSP::PhaseVocoder (NEXT), DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::PitchDetector (DONE), DSP::CorrectionCurve, DSP::FormantModel, DSP::LowLatencyBuffer
- Signal/voice flow: Input → Pitch detector → Correction curve / retune logic → Formant correction → Output
- TODO:
  - Implement Phase Vocoder or SOLA-based pitch shifter
  - Connect manual note editing to the correction curve
  - Implement formant preservation

### Antares AVOX Suite
- Category: multi-effect
- Sidechain: Internal per-module; Sybil offers split-band detection, no external key.
- Processing blueprint: Artist macro chain combining EQ, compression, saturation, and FX under curated controls. Collection of vocal design tools (Choir, Duo, Punch, Sybil, Throat) handling doubling, ensemble, dynamics, and timbre sculpting.
- Key features:
  - Scene-based presets per source
  - Macro knobs controlling multiple parameters
  - Parallel wet/dry architecture
  - Internal routing snapshots
  - Choir creates ensemble stacks with pitch/timing randomization
  - Duo provides adjustable detune/delay doubling
  - Punch adds transient shaping and compression suited for vocals
  - Sybil split-band de-esser with look-ahead; Throat models vocal tract length and resonance
- Core building blocks:
  - DSP::MacroController, DSP::SignalRouter, DSP::ParametricEQ, DSP::DynamicsSuite, DSP::FXRack, DSP::VoiceCloner, DSP::PitchModulator, DSP::TransientShaper, DSP::FormantMorpher
- Signal/voice flow: Input → Module-specific processing (ensemble/dynamics/formant) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
