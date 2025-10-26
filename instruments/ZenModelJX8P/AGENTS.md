# Zen Model JX-8P Expansion Stub

## Purpose
- Mirrors Roland's JX-8P Model Expansion inside ZENOLOGY, exposing PG-800 style macro controls while reusing the shared ZenCoreWorkstation engine.
- Configures dual partials (saw/square) with cross-mod ready routing, motion sequencing for detune/vibrato, and a chorus/delay rack mirroring the hardware's signal flow.

## Engine Mapping
- **Base engine**: inherits from `Instruments::ZenCoreWorkstation`.
- **Partials**: Enables Partials A & B, pre-sets coarse detune and filter offsets, leaves C/D disabled.
- **Motion**: Activates Motion Lane 1 (slow triangle) to emulate analog drift; Motion Lane 2 reserved for vibrato macro.
- **FX Rack**: Defaults IFX slot A to Dimension-style chorus, MFX to stereo delay, TFX to plate reverb.
- **Macros**: Maps Macro 1/2 to filter/brilliance sweeps, Macro 3 to chorus depth, Macro 4 to delay feedback.

## Repository Integration
- Uses existing parameter IDs via `PluginSDK::ParameterSet` for non-destructive presetting.
- Shares `Synth::VoiceManager` voice tracking inherited from the base workstation (no additional state required).
- Leverages `DSP::ZenCoreMFXCatalogue` entries to label IFX/MFX/TFX with JX-8P defaults.

## TODO / Follow-ups
1. Attach PG-800 style UI layer (panel layout, slider grouping) once UI schema is available.
2. Provide sample-based analog noise injection via `Sample::StreamEngine` when MediaPool streaming is implemented.
3. Author factory presets and lifetime key metadata overlapping Roland Cloud naming.
