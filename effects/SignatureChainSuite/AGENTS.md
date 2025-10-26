# Signature Chain Suite Effect Stub

## Reference
- Inspired by: Signature Series
- Vendor: Waves
- Source catalog: CLA Base Mono/Stereo, CLA Base Stereo, CLA Drums Mono/Stereo, CLA Drums Stereo, CLA Effects Mono/Stereo, CLA Effects Stereo, CLA Guitars Mono/Stereo, CLA Guitars Stereo, CLA Unplugged Mono/Stereo, CLA Unplugged Stereo, CLA Vocals Mono/Stereo, CLA Vocals Stereo, CLA-2A Mono, CLA-2A Stereo, CLA-3A Mono, CLA-3A Stereo, CLA-76 Mono, CLA-76 Stereo, Ekramer BA Stereo, Ekramer DR Mono, Ekramer DR Stereo, Ekramer FX Mono/Stereo, Ekramer FX Stereo, Ekramer GT Mono/Stereo, Ekramer GT Stereo, Ekramer VC Meno/Stereo, Ekramer VC Stereo, MannyM Delay Mono/Stereo, MannyM Distortion Mono, MannyM Tone Shaper Mono, MannyM Tone Shaper Stereo, MannyM TripleD Stereo, ManryM Delay Stereo, ManryM Distoton Stereo, ManryM EQ Mono, ManryM EQ Stereo, ManryM Reverb Mono, ManryM Reverb Mono/Stereo, ManryM Reverb Stereo, ManryM TripleD Mono, Maserati ACG Mono/Stereo, Maserati ACG Stereo, Maserati B72 Mono, Maserati B72 Mono/Stereo, Maserati B72 Stereo, Maserati DRM Mono, Maserati DRM Stereo, Maserati GRP Mono, Maserati GRP Stereo, Maserati GTi Mono/Stereo, Maserati GTi Stereo, Maserati HMX Mono/Stereo, Maserati HMX Stereo, Maserati VX1 Mono/Stereo, Maserati VX1 Stereo, JJP-Bass Mono, JJP-Bass Mono/Stereo, JJP-Bass Stereo, JJP-Cymb-Perc Mono/Stereo, JJP-Cymb-Perc Stereo, JJP-Drums Mono, JJP-Drums Mono/Stereo, JJP-Drums Stereo, JJP-Guitars Mono/Stereo, JJP-Guitars Stereo, JJP-Strings Keys Mono/Stereo, JJP-Strings Keys Stereo, JJP-Vocals Mono/Stereo, JJP-Vocals Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves CLA Artist Signature
- Category: multi-effect
- Sidechain: Internal macros; no external sidechain.
- Processing blueprint: Artist macro chain combining EQ, compression, saturation, and FX under curated controls. Bundle of Chris Lord-Alge artist presets (Bass, Drums, Effects, Guitars, Unplugged, Vocals) combining EQ, compression, and FX with macro controls.
- Key features:
  - Scene-based presets per source
  - Macro knobs controlling multiple parameters
  - Parallel wet/dry architecture
  - Internal routing snapshots
  - Scene buttons for quick tone changes
  - Macro faders simultaneously drive compression, EQ, and FX sends
  - Dedicated reverbs/delays per profile
  - Modeled analog drive for CLA sheen
- Core building blocks:
  - DSP::MacroController, DSP::SignalRouter, DSP::ParametricEQ, DSP::DynamicsSuite, DSP::FXRack, DSP::CompressorModule
- Signal/voice flow: Input → Macro-driven chain (EQ → Dynamics → FX sends) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves CLA Classic Compressors
- Category: dynamics
- Sidechain: External high-pass sidechain (1176/76) plus analog-style HPF.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. Digitally modeled CLA-76, CLA-2A, and CLA-3A compressors reflecting famous hardware units.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Switchable Blacky/Bluey 1176 models
  - CLA-2A includes HF emphasis for de-essing
  - CLA-3A medium attack opto for guitars/bass
  - Analog noise toggle for realism
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::AnalogModel, DSP::OptoDetector, DSP::FETCompressor
- Signal/voice flow: Input → Model-specific detector/drive → Gain reduction → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Eddie Kramer Signature
- Category: channel coloration
- Sidechain: Internal macros; no external key.
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Signature chains by Eddie Kramer for vocals, drums, guitars with creative FX routing.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Multi-stage chain (EQ→Dynamics→FX) tuned per instrument
  - “Intensity” knob balancing compression vs FX blend
  - Sub-bus routing for ambience/widening
  - Includes stereo and mono variants for tracking
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::MacroController, DSP::SignalRouter, DSP::CompressorModule, DSP::FXRack
- Signal/voice flow: Input → Instrument-specific chain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Manny Marroquin Signature
- Category: multi-effect
- Sidechain: Internal macros; Delay supports ducking sidechain from input.
- Processing blueprint: Artist macro chain combining EQ, compression, saturation, and FX under curated controls. Manny Marroquin series (EQ, Delay, Distortion, Reverb, Tone Shaper, TripleD) featuring analog-inspired color options.
- Key features:
  - Scene-based presets per source
  - Macro knobs controlling multiple parameters
  - Parallel wet/dry architecture
  - Internal routing snapshots
  - Color selector toggles between analog curves
  - Delay includes reverb/vibrato send with ducking
  - Tone Shaper uses multi-band saturation
  - TripleD isolates harshness, boom, sibilance bands
- Core building blocks:
  - DSP::MacroController, DSP::SignalRouter, DSP::ParametricEQ, DSP::DynamicsSuite, DSP::FXRack, DSP::ColorEQ, DSP::DelayRack, DSP::MultiBandDynamics, DSP::SaturationModule
- Signal/voice flow: Input → Module-specific processing (EQ/delay/etc.) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Maserati Signature
- Category: multi-effect
- Sidechain: Internal macros only.
- Processing blueprint: Artist macro chain combining EQ, compression, saturation, and FX under curated controls. Tony Maserati signature presets tailored to vocal, drums, guitars, keys, and more.
- Key features:
  - Scene-based presets per source
  - Macro knobs controlling multiple parameters
  - Parallel wet/dry architecture
  - Internal routing snapshots
  - Quick source selection with context-specific FX
  - Parallel compression paths baked into macros
  - Atmosphere knobs injecting reverb/delay
  - Tone controls with targeted EQ curves
- Core building blocks:
  - DSP::MacroController, DSP::SignalRouter, DSP::ParametricEQ, DSP::DynamicsSuite, DSP::FXRack, DSP::ParallelBus
- Signal/voice flow: Input → Tone/EQ shaping → Dynamics → FX returns → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves JJP Signature
- Category: multi-effect
- Sidechain: Internal macros; no external key.
- Processing blueprint: Artist macro chain combining EQ, compression, saturation, and FX under curated controls. Jack Joseph Puig signature chains for bass, drums, guitars, keys, strings, vocals.
- Key features:
  - Scene-based presets per source
  - Macro knobs controlling multiple parameters
  - Parallel wet/dry architecture
  - Internal routing snapshots
  - Modeled Pultec/EQ curves and Fairchild-style compression
  - Attitude knob driving harmonic enhancers
  - Dedicated FX returns (reverb/delay) per profile
  - Noise/Analog toggles for vibe
- Core building blocks:
  - DSP::MacroController, DSP::SignalRouter, DSP::ParametricEQ, DSP::DynamicsSuite, DSP::FXRack, DSP::AnalogModel
- Signal/voice flow: Input → Analog-modeled chain (EQ → Dynamics → FX) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
