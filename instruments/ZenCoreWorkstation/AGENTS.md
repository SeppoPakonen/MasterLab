# Zen Core Workstation Instrument Stub

## Reference
- Inspired by: Zenology Workstation
- Vendor: Roland
- Source catalog: ZENOLOGY, ZENOLOGY Pro

## Implementation Plan
### Roland ZENOLOGY
- Category: rompler/workstation
- Sidechain: MIDI/MPE support; no audio sidechain.
- Processing blueprint: Zen-Core based instrument delivering PCM, virtual analog, and modelled partials with deep modulation and multi-FX.
- Key features:
  - Four-partial structure with cross-mod, ring, and sync options
  - Scenes for layering/splitting up to four parts with macro morphing
  - Motion Designer step-LFOs plus matrix modulation sources
  - Integrated MFX/IFX/TFX racks mirroring modern Roland hardware
- Core building blocks:
  - Synth::ZenPartial, Synth::VoiceManager, Synth::ModMatrix, Automation::MotionDesigner, Sample::StreamEngine, FX::ZenFXRack
- Signal/voice flow: Note on → VoiceManager assigns partial voices → Partial oscillators (PCM/VA) → Time-variant filter/amp → MFX/TFX racks → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
