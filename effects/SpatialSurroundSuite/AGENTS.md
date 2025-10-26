# Spatial Surround Suite Effect Stub

## Reference
- Inspired by: Spatial & Surround
- Vendor: Waves
- Source catalog: 360 5.0, 360 5.1, Dorrough360 5.0, Dorrough360 5.1, IDR360 5.1, IDR360 6.0, IR360 discrete Mono/5.0, IR360 eff discrete 5.1, IR360 eff discrete 6.0, IR360 eff discrete Stereo/5.0, IR360 eff s eld Stereo/5.0, IR360 sound field 5.0, IR360 sound field 5.1, IR360 sound field Mono/5.0, IR360 sound field Stereo/.0, L360 5.0, L360 5.1, LFE360 Mono, LFE3605.1, M360 Manager 5.0/5.1, M360 Manager 5.1, M360 Manager 6.0, M360 Mixdown 0, M360 Mixdown 5.1, MV360 5.0, MV360 5.1, R360 5.0, R360 5.1, R360 Mono/5.1, R360 Mono/6.0, R360 Stereo/5.1, R360 Stereo/6.0, S360 Imager 5.0, S360 Imager 5.1, S360 Imager Mono/5.0,, S360 Imager Mono/5.1, S360 Imager Stereo/5.0,, S360 Imager Stereo/5.1, S360 Panner Mono/5.0, S360 Panner Mono/S1, S360 Panner Stereo/5.1, S360 Panner Stereo/6.0, SurroundDither, SurroundPan, UM225 Stereo/6.0, UM226 Stereo/5.1, S1 Imager Stereo, S1 MS Matrix Stereo, S1 Shuffler Stereo, PS22 Stereo Maker, PS22 Split Mono/Stereo, PS22 Split Stereo, PS22 Spread Mono/Stereo, PS22 Spread Stereo, PS22 Spread{10) Stereo, PS22 Spread{10} Mono/Stereo, PS22 XSplit Mono, PS22 XSplit Stereo, InPhase LT Live Mono, InPhase LT Live Stereo, InPhase LT Mono, InPhase LT Stereo, InPhase Live Mono, InPhase Live Stereo, InPhase Mono, InPhase Stereo, LoAir 5.0/5.1, LoAir 5.1, LoAir Mono, LoAir Stereo, Doppler Mono/Stereo, Doppler Stereo, Center Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves 360 Surround Suite
- Category: spatial
- Sidechain: N/A; some modules accept control signals.
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Comprehensive surround toolkit covering panning, imaging, sub management, meters, and convolution for 5.0/5.1/6.0 productions.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - S360 Panner with trajectory automation and divergence control
  - M360 Manager/Mixdown for fold-down and monitoring
  - IDR360, L360, MV360 provide surround-aware limiting/dithering
  - IR360 convolution reverb and Dorrough360 metering for surround
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::SurroundPanner, DSP::SurroundLimiter, DSP::ConvolutionEngine
- Signal/voice flow: Input bus → Module-specific surround processing → Output bus
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves S1 Stereo Imager
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Stereo imaging suite including Imager, MS Matrix, and Shuffler for mid/side manipulation.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Adjusts width, rotation, and asymmetry
  - Shuffler adds frequency-dependent widening
  - MS Matrix for quick mid/side conversions
  - Phase meter integrated
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::MSMatrix, DSP::StereoShuffler
- Signal/voice flow: Input → MS processing → Reconstruction → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves PS22 Stereo Imager
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Psychoacoustic stereo widener maintaining mono compatibility.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Split, Spread, and XSplit modes
  - Frequency-dependent widening with steering filters
  - Preserves bass mono via focus control
  - Optional decorrelation for 10dB spread
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::PsychoStereo, DSP::FilterBank, DSP::Decorrelator
- Signal/voice flow: Input → Psychoacoustic spread filters → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves InPhase
- Category: spatial
- Sidechain: Secondary input for reference channel (dual mono or stereo).
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Phase alignment tool with waveform view, correlation, and all-pass filters.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Sample-accurate delay adjust
  - All-pass filter for frequency-dependent alignment
  - Correlation meter and spectrum view
  - Snapshots for comparing settings
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::FineDelay, DSP::AllPassFilter, DSP::Analyzer
- Signal/voice flow: Input A/B → Delay/phase adjust → Sum → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves LoAir
- Category: spatial
- Sidechain: Internal crossover; dedicated LFE output.
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Subharmonic generator and LFE management tool for surround/film.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Generates sub frequencies from stereo input
  - Supports direct LFE feed
  - Phase alignment controls
  - Different modes for cinema/broadcast
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::SubSynth, DSP::Crossover, DSP::PhaseAligner
- Signal/voice flow: Input → Sub synth + split → Output + LFE
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Doppler
- Category: spatial
- Sidechain: Automation curves for path control.
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Simulates Doppler shift and 3D movement for sound design.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Graphical path editor with speed control
  - Pitch shift due to Doppler plus amplitude falloff
  - Air absorption modelling
  - Bounce mode for repeated passes
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::DopplerModel, DSP::TrajectoryEngine, DSP::DistanceAttenuator
- Signal/voice flow: Input → Trajectory-based Doppler model → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Center
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Mid/side-based center extraction and stereo control tool.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Separate center, side, and ambience gain
  - Frequency-dependent crossover to shape extraction
  - Stereo width and rotate controls
  - Useful for remastering stems or remixes
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::MSMatrix, DSP::FrequencySplit, DSP::GainStage
- Signal/voice flow: Input → MS decomposition → Frequency splits → Gain controls → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
