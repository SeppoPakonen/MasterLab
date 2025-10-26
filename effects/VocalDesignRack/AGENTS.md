# Vocal Design Rack Effect Stub

## Reference
- Inspired by: Vocal Design
- Vendor: Cymatics
- Source catalog: Omnivox

## Implementation Plan
### Cymatics Omnivox
- Category: vocal multi-fx
- Sidechain: Internal key detection only; no external sidechain.
- Processing blueprint: AI-driven vocal design rack layering harmonies, formant shifts, and spatial effects behind macro controls.
- Key features:
  - Neural voice style analysis with voice-type presets
  - Four-lane harmonizer with humanize and timing spread
  - Macro-driven FX chain (drive, chorus, delay, reverb) with tempo sync
  - Automatic gain normalization and intelligent de-essing
- Core building blocks:
  - DSP::VoiceFeatureExtractor, DSP::HarmonyGenerator, DSP::StyleTransferNet, DSP::MacroFXRack, DSP::GainNormalizer
- Signal/voice flow: Input → Feature extraction → Harmony/style processors → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
