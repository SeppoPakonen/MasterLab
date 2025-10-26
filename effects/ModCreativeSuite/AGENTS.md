# Mod Creative Suite Effect Stub

## Reference
- Inspired by: Modulation & Creative FX
- Vendor: Waves
- Source catalog: Enigma Mono/Stereo, Enigma Stereo, MetaFlanger Mono, MetaFlanger Mono/Stereo, MetaFlanger Stereo, MetaFilter Mono, MetaFilter Mono/Stereo, MetaFilter Stereo, MondoMod Mono, MondoMod Mono/Stereo, MondoMod Stereo, Doubler2 Meno/Stereo, Doubler2 Mono, Doubler2 Stereo, Doubler4 Mono, Doubler4 Mono/Stereo, Doubler4 Stereo, OneKnob Bighter Stereo, OneKnob Brighter Mono, OneKnob Driver Mono, OneKnob Driver Stereo, OneKnob Fiter Mono, OneKnob Fiter Stereo, OneKnob Louder Mono, OneKnob Louder Stereo, OneKnob Phatter Mono, OneKnob Phatter Stereo, OneKnob Pressure Mono, OneKnob Pressure Stereo, OneKnob Wetter Meno/Stereo, OneKnob Wetter Mono, OneKnob Wetter Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves Enigma
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Complex modulation effect combining phasing, flanging, and frequency shifting for sweeping textures.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Dual LFOs controlling notch filters and delay
  - Feedback matrix for resonant sweeps
  - Tempo-syncable modulation
  - Blend between phaser/flanger tones
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::ModulationMatrix, DSP::NotchFilterBank
- Signal/voice flow: Input → Modulated filter/delay network → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves MetaFlanger
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Versatile flanger/phaser with multiple modulation sources and vintage models.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Six modulation sources including envelope follower
  - Tape, analog, and digital delay models
  - Phase inversion for jet flanges
  - Tempo sync with note subdivisions
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::FlangerEngine, DSP::ModMatrix
- Signal/voice flow: Input → Modulated short delays → Feedback → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves MetaFilter
- Category: filtering
- Sidechain: Envelope follower from input audio.
- Processing blueprint: Dual multi-mode filters with modulation matrix. Multi-mode filter with sequencer, LFO, and envelope follower for creative sweeps.
- Key features:
  - LP/BP/HP/notch with resonance drive
  - Step sequencer or LFO modulation
  - Envelope follower/key tracking
  - Stereo offset for widening effects
  - LP/BP/HP/notch with drive stages
  - Step sequencer with pattern morphing
  - LFOs and envelope follower assignable via modulation matrix
  - Stereo offset and randomization options
- Core building blocks:
  - DSP::StateVariableFilter, DSP::ModMatrix, DSP::EnvelopeFollower, DSP::LFO
- Signal/voice flow: Input → Dual filters with modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves MondoMod
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). AM/FM/panning modulation tool for tremolo, vibrato, and auto-pan effects.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Modulates amplitude, frequency, and panning simultaneously
  - Phase offset between modulation targets
  - Tempo sync and sample-accurate LFO
  - Stereo width control
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::TremoloEngine, DSP::PitchModulator, DSP::Panner
- Signal/voice flow: Input → Combined AM/FM/Pan modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Doubler
- Category: pitch/modulation
- Sidechain: N/A
- Processing blueprint: Multi-voice pitch shifter/doubler with delay and modulation per voice. Dedicated vocal/instrument doubler with up to four detuned voices.
- Key features:
  - Fixed intervals and detune offsets
  - Per-voice delay/pan for stereo width
  - Formant preserve options
  - Randomization to avoid comb artifacts
  - Independent delay, detune, and pan per voice
  - Formant-correct mode for vocals
  - Unison spread and modulation depth
  - Phase randomization to avoid combing
- Core building blocks:
  - DSP::PitchShifter, DSP::DelayLine, DSP::ModMatrix, DSP::VoiceCloner, DSP::PitchDetune, DSP::DelaySpread
- Signal/voice flow: Input → Voice duplication/detune → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves OneKnob Series
- Category: macro fx
- Sidechain: N/A
- Processing blueprint: Single-knob macro mapping to multiple processors (EQ, compression, saturation). Set of macro effects (Brighter, Driver, Fatter, Pressure, etc.) controlled by a single knob.
- Key features:
  - Curated macro curves per preset
  - Auto gain compensation
  - Lightweight CPU footprint
  - Preset-specific signal flows (serial/parallel)
  - Each preset maps macro knob to multiple parameters
  - Internal chain varies per effect (EQ, compression, saturation)
  - Output trim to manage level
  - Automation friendly for creative sweeps
- Core building blocks:
  - DSP::MacroController, DSP::SignalRouter, DSP::ParametricEQ, DSP::DynamicsSuite, DSP::FXModules
- Signal/voice flow: Input → Macro-defined chain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
