# Guitar Instrument Platforms Effect Stub

## Reference
- Inspired by: Guitar & Instrument Platforms
- Vendor: Waves
- Source catalog: PRS Archon, PRS Dallas, PRS Blue Sierra/V9, Lil Tube, GTR3 Amps, GTR3 Stomps, GTR3 ToolRack, GTR3 Tuner

## Implementation Plan
### Waves PRS SuperModels
- Category: amp sim
- Sidechain: N/A
- Processing blueprint: Suite of PRS amp models with cabinet IRs and stomp-style tone shaping.
- Key features:
  - Component-level modeling of preamp, power amp, and sag
  - Cabinet module with selectable IRs and mic positions
  - Bright/boost switches tied to macro automation
  - Built-in output limiter for level control
- Core building blocks:
  - DSP::AmpModel, DSP::CabIRLoader, DSP::SagSimulator, DSP::MacroController, DSP::OutputLimiter
- Signal/voice flow: Input → Amp model → Cab IR/mic mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Lil Tube
- Category: saturation
- Sidechain: N/A
- Processing blueprint: One-knob analog tube saturation for quick harmonics on tracks or buses.
- Key features:
  - Continuous drive control blending triode characteristics
  - Bias and noise toggles for subtle realism
  - Auto gain for level-compensated audition
  - Mix control for parallel saturation
- Core building blocks:
  - DSP::TubeSaturator, DSP::BiasController, DSP::NoiseGenerator, DSP::AutoGain, DSP::MixStage
- Signal/voice flow: Input → Tube saturation → Mix blend → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves GTR3 Amps
- Category: amp sim
- Sidechain: N/A
- Processing blueprint: Collection of amp models covering clean, crunch, and high-gain styles with cabinet/mic selection.
- Key features:
  - 30+ amp models with tone stack customization
  - Cabinet selection with dual-mic blending
  - Phase and delay compensation between mics
  - Snapshots for live recall
- Core building blocks:
  - DSP::AmpModel, DSP::CabMixer, DSP::MicPlacement, DSP::SnapshotStore
- Signal/voice flow: Input → Amp model → Cab/mic mixer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves GTR3 Stomps
- Category: stompbox
- Sidechain: N/A
- Processing blueprint: Suite of stompbox effects (drive, modulation, dynamics) for guitar or synth signals.
- Key features:
  - 30 stomp modules with drag-and-drop ordering
  - Tempo sync for modulation/delay units
  - Expression pedal mapping for automation
  - Integration with ToolRack for preset recall
- Core building blocks:
  - DSP::StompHost, DSP::ModuleRouter, DSP::ModulationEngine, DSP::ExpressionMapper
- Signal/voice flow: Input → Stomp chain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves GTR3 ToolRack
- Category: host
- Sidechain: Supports sidechain into selected modules.
- Processing blueprint: Host environment bundling GTR3 components with split routing, tuner, and automation macros.
- Key features:
  - Split routing for dual chain (A/B) processing
  - Global tuner and metering overlay
  - Macro controls for patch morphing
  - MIDI learn for live rigs
- Core building blocks:
  - DSP::RackHost, DSP::SplitRouter, DSP::MacroController, DSP::TunerModule
- Signal/voice flow: Input → Split/mix chains → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves GTR3 Tuner
- Category: utility
- Sidechain: N/A
- Processing blueprint: Chromatic tuner with high-resolution strobe display for stage and studio.
- Key features:
  - Fast pitch detection with +/-0.1 cent resolution
  - Reference calibration and temperament options
  - Mute and bypass integration for racks
  - Readable strobe display for dark stages
- Core building blocks:
  - DSP::PitchDetector, DSP::CalibrationManager, UI::StrobeDisplay
- Signal/voice flow: Input → Pitch detection → UI
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
