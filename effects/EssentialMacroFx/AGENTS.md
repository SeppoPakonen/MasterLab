# Essential Macro Fx Effect Stub

## Reference
- Inspired by: KSHMR Essentials
- Vendor: Dharma Worldwide
- Source catalog: KSHMR Essentials Kick, Bass, Drums, Synth, Vocals

## Implementation Plan
### KSHMR Essentials
- Category: macro channel
- Sidechain: Internal auto-duck for Kick module, no external sidechain.
- Processing blueprint: Macro-focused multi-effect tailored for different sound categories (kick, bass, drums, synth, vocals) sharing a consistent UI.
- Key features:
  - Module selectors switch curated processors per instrument type
  - Macro knobs map to multi-parameter sweeps (sub, air, pressure)
  - Built-in transient, saturation, and width stages per preset
  - Auto gain to keep macros balanced in live performance
- Core building blocks:
  - DSP::MacroController, DSP::ModuleSwitcher, DSP::TransientDesigner, DSP::Saturator, DSP::StereoSpread, DSP::AutoGain
- Signal/voice flow: Input → Module preset (kick/bass/etc) → Macro-controlled processors → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
