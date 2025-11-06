# Zen Core Fx Rack Effect Stub

## Reference
- Inspired by: Zenology FX
- Vendor: Roland
- Source catalog: ZENOLOGY FX, ZENOLOGY Pro FX

## Implementation Plan
### Roland ZENOLOGY FX
- Category: multi-fx
- Sidechain: Envelope follower and motion sequencer only; no external audio sidechain.
- Processing blueprint: Zen-Core derived multi-effect rack offering MFX/IFX/TFX slots, step modulation, and scene morphing for external sources.
- Key features:
  - 90+ Zen-Core algorithms (chorus, phaser, pitch, amp) ported from hardware synths
  - Motion Designer with step LFOs, envelope followers, and per-step probability
  - Scene morphing between two effect states with macro automation
  - Per-block oversampling and BBD modeling to minimize aliasing during heavy drive
- Core building blocks:
  - DSP::ZenCoreMFXCatalogue, DSP::MotionSequencer, DSP::SceneMorph, DSP::OversampleStage, DSP::PreEmphasis
- Signal/voice flow: Input → Pre-conditioning (HPF/level match) → MFX slot chain (up to three blocks) → Time FX (TFX) master → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
