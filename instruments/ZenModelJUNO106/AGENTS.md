# Zen Model JUNO-106 Expansion Stub

## Purpose
- Represents the JUNO-106 Model Expansion inside ZENOLOGY, using the shared ZenCoreWorkstation core while constraining the architecture to the JUNO single-oscillator voice.
- Preconfigures a single partial with PWM-capable motion, classic JUNO HPF/LPF balance, and the iconic chorus stages.

## Engine Mapping
- **Base engine**: derives from `Instruments::ZenCoreWorkstation`.
- **Partials**: Enables only Partial A with supersaw/PWM flavour, disables B–D.
- **Motion**: Sets Motion Lane 1 for slow PWM, Lane 2 for envelope-followed brightness sweeps.
- **Macros**: Macro 1 = cutoff sweep, Macro 2 = envelope depth, Macro 3 = chorus depth, Macro 4 = noise level placeholder.

## Repository Integration
- Relies on inherited `Synth::VoiceManager` for voice lifecycle and velocity scaling.
- Uses `PluginSDK::ParameterSet` IDs to establish the JUNO defaults without touching processing code.
- Coordinates with `DSP::ZenCoreMFXCatalogue` defaults indirectly through effect presets (IFX chorus, TFX reverb planned).

## TODO / Follow-ups
1. Lock IFX slot defaults to JUNO Chorus I/II once cross-package parameter bridging is available.
2. Wire Macro 4 to a noise generator partial when `Sample::StreamEngine` gains lightweight noise support.
3. Author factory macro snapshots that match JUNO-106 panel positions.
