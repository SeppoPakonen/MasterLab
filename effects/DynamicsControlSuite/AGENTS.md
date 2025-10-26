# Dynamics Control Suite Effect Stub

## Reference
- Inspired by: Dynamics & Control
- Vendor: Waves
- Source catalog: C1 comp Mono, C1 comp Stereo, C1 comp-gate Mono, C1 comp-gate Stereo, C1 comp-sc Mono, C1 comp-sc Stereo, C1 gate Mono, C1 gate Stereo, C4 Mono, C4 Stereo, C6 Mono, C6 Stereo, C6-SideChain Mono, C6-SideChain Stereo, Base Rider Live Mono, Base Rider Live Stereo, Base Rider Mono, Bass Rider Stereo, Vocal Rider Live Mono, Vocal Rider Live Stereo, Vocal Rider Mono, Vocal Rider Stereo, H-Comp Mono, H-Comp Stereo, MaxxVolume Mono, MaxxVolume Stereo, MV2 Mono, MV2 Stereo, TransX Mult Stereo, TransX Multi Mono, TransX Wide Mono, TransX Wide Stereo, MaxxBass Mono, MaxxBass Stereo, Vitamin Mono, Vitamin Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves C1 Dynamics
- Category: dynamics
- Sidechain: External on C1 comp-sc; internal filters on other variants.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. Highly configurable compressor/gate/expander with SC variants widely used for surgical dynamics control.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Multiple modes (comp, gate, expander, comp-gate)
  - Lookahead and electro/optical detector curves
  - Band-select Listen for precise keying
  - Sidechain EQ with frequency-specific control
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::DetectorModes
- Signal/voice flow: Input → Mode-specific detector → Gain computer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves C4 Multiband
- Category: dynamics
- Sidechain: Internal; band solo listen aids tuning.
- Processing blueprint: Multi-band dynamics engine with linear-phase crossover and per-band compression/expansion. Classic four-band multiband compressor with dynamic EQ abilities.
- Key features:
  - Adjustable crossover slopes with latency compensation
  - Per-band solo/mute and gain trim
  - Dynamic EQ bells with external sidechain (C6)
  - Master limiter/post gain staging
  - Adaptive threshold linking to overall level
  - Master controls for range and release character
  - Per-band bypass/solo/mute
  - Auto make-up and density meter
- Core building blocks:
  - DSP::LinearPhaseCrossover, DSP::BandDynamics, DSP::EnvelopeDetector, DSP::GainComputer, DSP::LatencyBuffer, DSP::MixStage
- Signal/voice flow: Input → Crossover → Band dynamics → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves C6 Multiband
- Category: dynamics
- Sidechain: External sidechain assignable to floating bands.
- Processing blueprint: Multi-band dynamics engine with linear-phase crossover and per-band compression/expansion. Expanded C4 adding two floating dynamic EQ bands and external sidechain support.
- Key features:
  - Adjustable crossover slopes with latency compensation
  - Per-band solo/mute and gain trim
  - Dynamic EQ bells with external sidechain (C6)
  - Master limiter/post gain staging
  - Two floating bands that can follow problem frequencies
  - Per-band sidechain assignment
  - Split/Wide band operation
  - Global mix and additional high-mid controls
- Core building blocks:
  - DSP::LinearPhaseCrossover, DSP::BandDynamics, DSP::EnvelopeDetector, DSP::GainComputer, DSP::LatencyBuffer, DSP::DynamicEQBand, DSP::SidechainRouter
- Signal/voice flow: Input → Fixed + floating band dynamics → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Bass Rider
- Category: dynamics
- Sidechain: Optional sidechain (music bus) to avoid over-triggering by kick drums.
- Processing blueprint: Level riding engine measuring short/long term loudness and writing gain moves. Automatic level rider tuned for bass instruments.
- Key features:
  - Dual detector ballistics for responsive yet stable gain moves
  - Target window and sensitivity controls
  - Automation writeback / live trim
  - Priority sidechain for ducking (Vocal/Bass Rider)
  - Target range slider between sustain and dynamics
  - Sensitivity and spill rejection to ignore bleed
  - Manual trim for automation writing
  - Graphic history display
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeFollower, DSP::GainScheduler, DSP::AutomationWriter
- Signal/voice flow: Input → Level detector → Gain automation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Vocal Rider
- Category: dynamics
- Sidechain: External sidechain for music bed ducking.
- Processing blueprint: Level riding engine measuring short/long term loudness and writing gain moves. Real-time vocal level rider keeping vocals present without compression artifacts.
- Key features:
  - Dual detector ballistics for responsive yet stable gain moves
  - Target window and sensitivity controls
  - Automation writeback / live trim
  - Priority sidechain for ducking (Vocal/Bass Rider)
  - Fast/slow targeting for verse vs chorus
  - Spill and Music sensitivity controls
  - Write/read automation to DAW lanes
  - Live mode for near-zero latency
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeFollower, DSP::GainScheduler, DSP::AutomationWriter, DSP::DualTimeDetector
- Signal/voice flow: Input → Dual detector → Gain automation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves H-Comp
- Category: dynamics
- Sidechain: External sidechain with punch (parallel) feature.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. Hybrid compressor blending digital precision and analog modeling with punchy transients.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Analog modeled release curves (1–4)
  - Punch knob for parallel transient retention
  - Sync-to-tempo release values
  - Analog noise and transformer drive
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::HybridCompressor, DSP::ParallelBlend, DSP::AnalogDrive
- Signal/voice flow: Input → Detector (digital/analog) → Gain stage + Punch mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves MaxxVolume
- Category: dynamics
- Sidechain: Internal detectors with separate low/peak thresholds.
- Processing blueprint: Level riding engine measuring short/long term loudness and writing gain moves. Combines low-level compression, gating, and peak limiting for loudness maximization.
- Key features:
  - Dual detector ballistics for responsive yet stable gain moves
  - Target window and sensitivity controls
  - Automation writeback / live trim
  - Priority sidechain for ducking (Vocal/Bass Rider)
  - Low-level compressor to lift quiet details
  - Gate for noise reduction before upward comp
  - Peak limiter to catch transients
  - Mix-friendly output meters
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeFollower, DSP::GainScheduler, DSP::AutomationWriter, DSP::UpwardCompressor, DSP::GateStage, DSP::LimiterModule
- Signal/voice flow: Input → Gate → Upward compressor → Peak limiter → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves MV2
- Category: dynamics
- Sidechain: Internal
- Processing blueprint: Level riding engine measuring short/long term loudness and writing gain moves. Simplified dual fader upward/downward compressor for quick loudness control.
- Key features:
  - Dual detector ballistics for responsive yet stable gain moves
  - Target window and sensitivity controls
  - Automation writeback / live trim
  - Priority sidechain for ducking (Vocal/Bass Rider)
  - High-level fader for peak control, low-level for upward compression
  - Auto release tuned for transparency
  - Great for stems and broadcast
  - Zero attack to catch sudden peaks
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeFollower, DSP::GainScheduler, DSP::AutomationWriter, DSP::DualStageCompressor, DSP::GainBlender
- Signal/voice flow: Input → Upward/Downward gain engines → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves TransX
- Category: dynamics
- Sidechain: Internal with frequency focus (Multi).
- Processing blueprint: Transient designer splitting attack and sustain envelopes with adjustable gain shaping. Transient shaping suite (Multi/Wide) for drums and percussive material.
- Key features:
  - Independent attack/sustain gain & timing
  - Frequency selective focus filter
  - Optional clipper to restrain spikes
  - Mid/Side routing for stereo material
  - Multi-band mode allows frequency-specific attack control
  - Wide mode for overall transient emphasis
  - Envelope window controls for shaping
  - Parallel blend for natural results
- Core building blocks:
  - DSP::TransientSplitter, DSP::EnvelopeDetector, DSP::GainStage, DSP::SidechainEQ, DSP::BandDynamics, DSP::MixStage
- Signal/voice flow: Input → Multi/Wide transient detection → Attack gain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves MaxxBass
- Category: enhancement
- Sidechain: Internal crossover; no external key.
- Processing blueprint: Psychoacoustic low-frequency enhancement using harmonic resynthesis. MaxxBass psychoacoustic sub enhancement generating harmonics audibly translating on small speakers.
- Key features:
  - Generates controllable harmonics one octave above LFE
  - Subharmonic synth with phase aligned mixing
  - Crossover for bus or LFE routing
  - Output meter to avoid over-excursion
  - Tune frequency sets psychoacoustic generator
  - Harmonics slider mixing synthetic bass
  - Original bass attenuator for headroom
  - Monitor mode to audition generated content
- Core building blocks:
  - DSP::EnvelopeFollower, DSP::PitchTracker, DSP::SubSynth, DSP::PhaseAligner, DSP::HarmonicGenerator, DSP::Crossover
- Signal/voice flow: Input → Crossover → Harmonic synth → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Vitamin
- Category: enhancement
- Sidechain: Internal per-band detectors.
- Processing blueprint: High-frequency harmonic generator with blend and noise modeling. Multiband harmonic enhancer and stereo imager.
- Key features:
  - Tunable emphasis frequency
  - Tube/tape style modes
  - Mid/Side mix options
  - Auto gain trim
  - Five bands with independent punch and stereo spread
  - Crossover slopes optimized for zero phase shift
  - Blend controls to reinject dry signal
  - Stage for analog-style saturation
- Core building blocks:
  - DSP::SplitFilter, DSP::HarmonicGenerator, DSP::MixStage, DSP::MultiBandEnhancer, DSP::StereoWidener, DSP::SaturationStage
- Signal/voice flow: Input → Multiband enhancer (harmonics + width) → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
