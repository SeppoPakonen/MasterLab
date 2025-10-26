# Guitar Instrument Suite Effect Stub

## Reference
- Inspired by: Guitar & Instrument
- Vendor: Waves
- Source catalog: GTR Amp 2Cab Mono, GTR Amp Mono, GTR Amp Mono/Stereo, GTR Amp Stereo, GTR Solo Taol Rack Mono/Stereo, GTR Solo Taol Rack Stereo, GTR Stomp 2 Mono, GTR Stomp 2 Mono/Stereo, GTR Stomp 2 Stereo, GTR Stomp 4 Mono, GTR Stomp 4 Mono/Stereo, GTR Stomp 4 Stereo, GTR Stomp 6 Mono, GTR Stomp 6 Mono/Stereo, GTR Stomp 6 Stereo, GTR Tool Rack Mono/Stereo, GTR Tool Rack Stereo, GTR Tuner Mono, J37 Mone, J37 Stereo, Vox Mono, Vox Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves GTR Suite
- Category: instrument processing
- Sidechain: N/A
- Processing blueprint: Integrated guitar/bass rig with amps, cabinets, stomps, and utility modules. Amp, stomp, and cabinet suite co-developed with Paul Reed Smith for guitar/bass processing.
- Key features:
  - Drag-and-drop stomp modules
  - Cabinet/mic blending with IR loader
  - DI split for re-amping
  - Integrated tuner and metering
  - Stomp, Amp, and Tool Rack modules with drag-and-drop routing
  - Amp models with mic/cab selections and DI split
  - Built-in tuner and metronome
  - Can run as standalone amp or plugin modules
- Core building blocks:
  - DSP::StompRack, DSP::AmpHead, DSP::CabIR, DSP::TunerEngine, DSP::UtilityTools
- Signal/voice flow: Input → Stomp rack → Amp → Cab/mic → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves J37 Tape
- Category: saturation
- Sidechain: N/A
- Processing blueprint: Tape recorder emulation with bias, wow/flutter, and saturation stages. Abbey Road J37 tape machine emulation with selectable tape formulas and slapback delay.
- Key features:
  - Selectable tape speed and formulation
  - Wow/flutter LFO with depth
  - Saturation/bias asymmetry controls
  - Delay path for ADT (J37)
  - Tape speed (7.5/15 ips) affecting frequency response
  - Saturation calibrated in VU with bias control
  - Wow/flutter and tape hiss toggles
  - Built-in delay with sync and feedback
- Core building blocks:
  - DSP::TapeSaturation, DSP::WowFlutter, DSP::EQStage, DSP::DelayLine, DSP::BiasControl
- Signal/voice flow: Input → Tape saturation core → Optional delay → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Vox Guitar Suite
- Category: instrument processing
- Sidechain: N/A
- Processing blueprint: Integrated guitar/bass rig with amps, cabinets, stomps, and utility modules. Amp/cabinet models optimized for Vox-style tones (AC30 etc.).
- Key features:
  - Drag-and-drop stomp modules
  - Cabinet/mic blending with IR loader
  - DI split for re-amping
  - Integrated tuner and metering
  - Choose between classic Vox amp voicings
  - Cab/mic combinations with room blend
  - Tone cut and brilliance controls
  - Drive and bias adjustments for chime vs crunch
- Core building blocks:
  - DSP::StompRack, DSP::AmpHead, DSP::CabIR, DSP::TunerEngine, DSP::ToneCut
- Signal/voice flow: Input → Vox amp model → Cabinet/mic → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
