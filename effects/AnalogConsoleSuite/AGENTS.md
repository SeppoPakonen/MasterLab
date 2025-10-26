# Analog Console Suite Effect Stub

## Reference
- Inspired by: Analog Channel & Console
- Vendor: Waves
- Source catalog: API-2500 Man, API-2500 Stereo, API-550A Mono, API-550A Stereo, API-550B Mono, API-550B Stereo, API-560 Mono, API-560 Stereo, AudioTrack Mono, AudioTrack Stereo, SSLChannel Mono, SSLChannel Stereo, SSLComp Mono, SSLComp Stereo, SSLEQ Mono, SSLEQ Stereo, SSLEQChannel Mono, SSLEQChannel Stereo, NLS Buss Mono, NLS Buss Stereo, NLS Channel Mono, NLS Channel Stereo, TG12345 Mono, TG12345 Stereo, REDD17 Mono, REDD17 Stereo, REDD37-51 Mono, REDD37-51 Stereo, The Kings Microphones Mono, The Kings Microphones Stereo, VEQ3 Mono, VEQ3 Stereo, VEQ4 Mono, VEQ4 Stereo, GEQ Classic Mono, GEQ Classic Stereo, GEQ Modern Mono, GEQ Modern Stereo, Scheps 73 Mono, RS56 Mono, RS56 Stereo, Aphex Vintage Exciter Mono, Aphex Vintage Exciter Stereo, Kramer HLS Mono, Kramer HLS Stereo, Kramer PIE Mono, Kramer PIE Stereo, Kramer Tape Mono, Kramer Tape Stereo, kramer BA Mono, PuigChild 660 Mono, PuigChild 670 Stereo, PuigTec EQP1A Mono, PuigTec EQP1A Stereo, PuigTec MEQ5 Mono, PuigTec MEQ5 Stereo, H-EQ Mono, H-EQ Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves API Collection
- Category: channel coloration
- Sidechain: API-2500 exposes external sidechain with Thrust HP filters.
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Models of API 2500 compressor and 550/560 equalizers providing API console tone.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - 2500 includes Old/New compression tones with Thrust detector
  - 550A/B provide proportional-Q EQ curves
  - 560 graphic EQ with constant level compensation
  - Supports analog noise on/off and link modes
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::APICompressor, DSP::ProportionalQEQ, DSP::AnalogSaturation
- Signal/voice flow: Input → API-style preamp → Compressor/EQ module → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves AudioTrack Channel Strip
- Category: channel strip
- Sidechain: External key for dynamics section.
- Processing blueprint: Integrated EQ + dynamics + routing with modular sections. All-in-one channel strip combining gate, EQ, and compressor from Waves Renaissance era.
- Key features:
  - Gain staging and polarity options
  - Dynamics order switching (Gate→Comp or Comp→Gate)
  - Saturation/drive stages per module
  - Per-section bypass & preset system
  - Three-band fully parametric EQ plus HP/LP
  - Gate/expander with sidechain filter
  - Compressor with soft knee and mix control
  - Latency-free design for tracking
- Core building blocks:
  - DSP::SignalRouter, DSP::ParametricEQ, DSP::Compressor, DSP::Gate, DSP::NonlinearStage, DSP::GateModule, DSP::CompressorModule
- Signal/voice flow: Input → Gate → EQ → Compressor → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves SSL Suite
- Category: channel strip
- Sidechain: External sidechain with HP filter (channel & bus comp).
- Processing blueprint: Integrated EQ + dynamics + routing with modular sections. Official SSL 4000 E/G emulations covering channel strip and G-bus compressor.
- Key features:
  - Gain staging and polarity options
  - Dynamics order switching (Gate→Comp or Comp→Gate)
  - Saturation/drive stages per module
  - Per-section bypass & preset system
  - Channel strip includes E/G EQ curves selectable
  - Dynamics section with expander/gate and over-EZ modes
  - Analog circuit modelling with noise and drive
  - G-bus comp with auto fade and mix controls
- Core building blocks:
  - DSP::SignalRouter, DSP::ParametricEQ, DSP::Compressor, DSP::Gate, DSP::NonlinearStage, DSP::SSLEChannel, DSP::SSLGBusCompressor, DSP::AnalogDrive
- Signal/voice flow: Input → SSL preamp/EQ/dynamics → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves NLS Non-Linear Summing
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Console summing emulation with three consoles (Spike, Mike, Nevo) and master bus.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Per-channel drive and trim with noise modelling
  - Group/linking for console-style stereo behaviour
  - Master bus plugin aggregates channel drive
  - Optional VCA style output fader
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::ConsoleChannelModel, DSP::NonlinearSummingBus
- Signal/voice flow: Individual channels → Nonlinear bus → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves TG12345 Channel Strip
- Category: channel coloration
- Sidechain: Compressor exposes external key.
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. EMI TG12345 desk channel with EQ, dynamics, and spreader.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Presence EQ bands with TG curves
  - Compressor/limiter derived from console channel
  - Parallel mix and THD drive
  - Spread control widening midrange
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::TGEqualizer, DSP::TGCompressor, DSP::SaturationStage
- Signal/voice flow: Input → TG EQ → Compressor/Limiter → Spread/Drive → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves REDD Consoles
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Models of Abbey Road REDD.17 and REDD.37/51 consoles with drive and EQ.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Redsat drive modelling tube stages
  - Classic tone curves with pop/rock switches
  - Mic/Line input modeling with auto gain
  - Spread control for stereo width
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::REDDPreamp, DSP::ToneEQ, DSP::SaturationStage
- Signal/voice flow: Input → REDD preamp/EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves The King's Microphones
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Three EMI king’s microphone impulse-based tone shapers.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - IR captures of 1920s microphones
  - Distance and level controls
  - HP filter to mitigate rumble
  - Great for radio/lo-fi coloration
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::ImpulseConvolver, DSP::GainStage
- Signal/voice flow: Input → Impulse convolution → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves VEQ EQs
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. VEQ3/VEQ4 vintage EQs based on Neve 1066/1081 curves.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Fixed-frequency stepped boost/cut
  - High/low shelf with proportional behaviour
  - Analog noise toggle
  - Phase-coherent with preamp drive
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::VintageEQ, DSP::AnalogDrive
- Signal/voice flow: Input → Vintage EQ filters → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves GEQ Graphic Equalizer
- Category: tone shaping
- Sidechain: N/A
- Processing blueprint: IIR parametric/Shelving EQ banks with analyzer overlay. Modern and Classic graphic EQs with phase-linear filters.
- Key features:
  - Multiple filter types per band
  - Static and dynamic gain linking
  - Analyzer overlay/M/S options
  - Per-band saturation (where applicable)
  - Classic version emulates proportional-Q behaviour
  - Modern version offers constant-Q with bell/shelving slopes
  - Per-band solo and multiple curve editing
  - Inverse link for quick corrective EQ
- Core building blocks:
  - DSP::ParametricEQ, DSP::Biquad, DSP::Analyzer, DSP::GraphicEQ
- Signal/voice flow: Input → Graphic EQ bands → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Scheps 73
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Andrew Scheps’ take on the Neve 1073 channel.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - 3-band EQ with selectable mid frequencies
  - Preamp saturation toggle
  - HP filter plus extra 12kHz shelf
  - Linkable L/R or mid/side operation
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::NeveEQ, DSP::SaturationStage
- Signal/voice flow: Input → Scheps EQ/preamp → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves RS56 EQ
- Category: tone shaping
- Sidechain: N/A
- Processing blueprint: IIR parametric/Shelving EQ banks with analyzer overlay. Abbey Road passive RS56 “The Curve Bender” EQ.
- Key features:
  - Multiple filter types per band
  - Static and dynamic gain linking
  - Analyzer overlay/M/S options
  - Per-band saturation (where applicable)
  - Passive EQ with three bands and continuous curves
  - Interactive boost/cut affecting Q
  - Mid/Side mastering mode
  - Analog modeling for transformer colour
- Core building blocks:
  - DSP::ParametricEQ, DSP::Biquad, DSP::Analyzer, DSP::PassiveEQ, DSP::TransformerStage
- Signal/voice flow: Input → Passive EQ network → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Aphex Vintage Aural Exciter
- Category: enhancement
- Sidechain: Internal frequency detection; no external key.
- Processing blueprint: High-frequency harmonic generator with blend and noise modeling. Licensed emulation of the Aphex Aural Exciter Type C for high-frequency enhancement.
- Key features:
  - Tunable emphasis frequency
  - Tube/tape style modes
  - Mid/Side mix options
  - Auto gain trim
  - Mix and Tune controls for harmonic focus
  - Modeled output transformer saturation
  - “Noise” slider replicates original unit
  - Mix to blend subtle sheen
- Core building blocks:
  - DSP::SplitFilter, DSP::HarmonicGenerator, DSP::MixStage, DSP::ExciterStage, DSP::SaturationStage
- Signal/voice flow: Input → HF split/harmonic generator → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Kramer Suite
- Category: channel coloration
- Sidechain: PIE compressor supports external sidechain.
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Includes Kramer HLS channel EQ, Kramer PIE compressor, and Kramer Tape.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - HLS replicates Helios EQ with noise/gain staging
  - PIE is a vari-mu compressor with mix control
  - Kramer Tape adds tape delay, flux, wow/flutter
  - Modules share analog noise modelling
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::HeliosEQ, DSP::VariMuCompressor, DSP::TapeSaturation
- Signal/voice flow: Input → Selected Kramer module → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves PuigChild Compressors
- Category: channel coloration
- Sidechain: External sidechain supported; also high-pass filter built-in.
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Fairchild 660/670 emulations with dual time constants and sidechain filter.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - 6 time constant presets plus manual mode
  - Mid/Side processing on 670
  - Analog hum and noise modelling
  - Headroom trim for hitting sweet spot
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::VariMuCompressor, DSP::SidechainFilter, DSP::SaturationStage
- Signal/voice flow: Input → Vari-mu detector → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves PuigTec EQs
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. PuigTec EQP-1A and MEQ-5 passive EQ collection.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Simultaneous boost/cut for low shelves (EQP trick)
  - Midrange MEQ with peak/dip sections
  - Analog line amp saturation
  - Linked stereo or dual mono
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::PassiveEQ, DSP::LineAmpSaturation
- Signal/voice flow: Input → Passive EQ network → Amplifier → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves H-EQ
- Category: tone shaping
- Sidechain: N/A
- Processing blueprint: IIR parametric/Shelving EQ banks with analyzer overlay. Hybrid EQ with both analog models and digital precision, including M/S and analyzer.
- Key features:
  - Multiple filter types per band
  - Static and dynamic gain linking
  - Analyzer overlay/M/S options
  - Per-band saturation (where applicable)
  - Select analog curves (US, UK, Digi) per band
  - Built-in spectrum analyzer with FFT freeze
  - M/S and Left/Right processing
  - Saturation and resonant HP/LP filters
- Core building blocks:
  - DSP::ParametricEQ, DSP::Biquad, DSP::Analyzer, DSP::HybridEQ, DSP::SaturationStage
- Signal/voice flow: Input → Hybrid parametric EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
