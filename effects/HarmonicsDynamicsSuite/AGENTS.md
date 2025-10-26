# Harmonics Dynamics Suite Effect Stub

## Reference
- Inspired by: Harmonics & Dynamics
- Vendor: Waves
- Source catalog: Vitamin Sonic Enhancer, Torque, Submarine, Kaleidoscopes, eMo D5 Dynamics, eMo Q4 Equalizer, Abbey Road Vinyl, IDR360, L3 Ultramaximizer, L3-LL Ultramaximizer

## Implementation Plan
### Waves Vitamin Sonic Enhancer
- Category: dynamics
- Sidechain: Sidechain for punch/bite detection optional.
- Processing blueprint: Parallel multiband enhancer marrying compression, EQ, and harmonic excitement to add clarity and impact.
- Key features:
  - Five-band parallel compressor/exciter matrix
  - Center vs surround mix controls for stereo widening
  - Punch control derived from transient detection
  - Zero-latency and linear-phase crossover options
- Core building blocks:
  - DSP::MultiBandSplitter, DSP::ParallelExciter, DSP::TransientDetector, DSP::StereoMatrix, DSP::LinearPhaseCrossover
- Signal/voice flow: Input → Multiband split → Parallel compression/excitation → Mixing matrix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Torque
- Category: drum tuning
- Sidechain: N/A
- Processing blueprint: Drum resonance retuning tool shifting perceived pitch without changing timing.
- Key features:
  - Pitch detection tailored for percussive transients
  - Harmonic tracking to preserve natural overtones
  - Focus slider isolating target band
  - Drive and mix controls for sound design
- Core building blocks:
  - DSP::PercussivePitchTracker, DSP::PhaseVocoder, DSP::HarmonicPreserver, DSP::MixStage
- Signal/voice flow: Input → Pitch tracking → Spectral retune → Mix blend → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Submarine
- Category: low-end
- Sidechain: N/A
- Processing blueprint: Subharmonic generator extending bass fundamentals up to two octaves below the source.
- Key features:
  - Dual-band sub synth with independent depth controls
  - Phase-aligned output for mono compatibility
  - Drive and dynamics sections to glue low end
  - Real-time analyzer visualizing generated subs
- Core building blocks:
  - DSP::SubSynth, DSP::PhaseAligner, DSP::DynamicsGlue, DSP::SpectrumAnalyzer
- Signal/voice flow: Input → Band-split detection → Sub generation → Mixing/drive → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Kaleidoscopes
- Category: modulation
- Sidechain: External sidechain for rhythm trigger input.
- Processing blueprint: Dual-engine modulation suite (phaser, flanger, chorus, tremolo) with trigger and sequencer-based modulation options.
- Key features:
  - Two parallel/serial modulation engines with extensive routing
  - Sync-to-beat step sequencer and external sidechain trigger
  - Envelope follower and LFO with shape morphing
  - Analog-modeled saturation per engine
- Core building blocks:
  - DSP::ModEngine, DSP::StepSequencer, DSP::EnvelopeFollower, DSP::LFOGenerator, DSP::SaturationStage
- Signal/voice flow: Input → Engine A/B modulation → Mixer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves eMo D5 Dynamics
- Category: dynamics
- Sidechain: Shared sidechain across gate, de-esser, comp; external input supported.
- Processing blueprint: Unified dynamics suite housing gate, de-esser, 2 compressors, and limiter with shared detection and workflow.
- Key features:
  - Shared detector matrix feeding multiple dynamics modules
  - Drag-and-drop signal order with snapshot recall
  - Feed-forward or feedback compression modes
  - Limiter with look-ahead and release shaping
- Core building blocks:
  - DSP::DetectorMatrix, DSP::GateModule, DSP::DeEsser, DSP::Compressor, DSP::Limiter, DSP::SnapshotStore
- Signal/voice flow: Input → Detector matrix → Module chain (Gate → De-Esser → Comp → Limiter) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves eMo Q4 Equalizer
- Category: eq
- Sidechain: N/A
- Processing blueprint: Four-band paragraphic EQ optimized for live sound with touchscreen workflow.
- Key features:
  - Four sweepable bands with variable Q and filter types
  - Touch-friendly large knobs and real-time analyzer
  - Gain scale control for relative adjustments
  - Latency-free processing for live rigs
- Core building blocks:
  - DSP::ParametricEQ, DSP::Analyzer, UI::TouchEncoder, DSP::GainScaler
- Signal/voice flow: Input → Parametric EQ engine → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Abbey Road Vinyl
- Category: saturation
- Sidechain: N/A
- Processing blueprint: Vinyl mastering chain emulating cutting and playback paths from Abbey Road Studios.
- Key features:
  - Selectable lacquer/master and DMM curves
  - Adjustable wow/flutter, noise, and mechanical rumble
  - Virtual stylus cartridges with tone shifts
  - TG mastering console drive and tone controls
- Core building blocks:
  - DSP::VinylEncoder, DSP::WowFlutter, DSP::NoiseGenerator, DSP::StylusModel, DSP::ConsoleDrive
- Signal/voice flow: Input → Console drive → Vinyl encoder → Noise/W&F overlay → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves IDR360 Bit Re-Quantizer
- Category: dithering
- Sidechain: N/A
- Processing blueprint: Dithering and noise-shaping engine for surround master delivery.
- Key features:
  - Multiple noise-shaping curves for multi-channel buses
  - Auto black to mute dithering during silence
  - 24/20/16-bit targets with crest-factor monitoring
  - Integrates with surround limiter for final stage
- Core building blocks:
  - DSP::DitherEngine, DSP::NoiseShaper, DSP::SilenceDetector, DSP::MeterBridge
- Signal/voice flow: Input → Quantization with noise shaping → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves L3 Ultramaximizer
- Category: mastering
- Sidechain: N/A
- Processing blueprint: Multiband look-ahead limiter with priority-based gain allocation for loudness maximization.
- Key features:
  - Priority slider to allocate headroom per band
  - Adaptive release control to avoid pumping
  - Built-in dithering and noise shaping
  - Per-band meters and attenuation graph
- Core building blocks:
  - DSP::LookaheadLimiter, DSP::PriorityAllocator, DSP::AdaptiveRelease, DSP::DitherEngine, DSP::MeterBridge
- Signal/voice flow: Input → Look-ahead analysis → Multiband gain allocation → Reconstruction → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves L3-LL Ultramaximizer
- Category: mastering
- Sidechain: N/A
- Processing blueprint: Low-latency variant of L3 with minimal look-ahead for live and tracking scenarios.
- Key features:
  - Reduced latency algorithm retaining 5-band control
  - ARC release modes optimized for low pre-delay
  - True-peak output ceiling with ISP catching
  - Latency compensation metadata for host sync
- Core building blocks:
  - DSP::LowLatencyLimiter, DSP::PriorityAllocator, DSP::TruePeakDetector, DSP::ARCController
- Signal/voice flow: Input → Fast look-ahead analysis → Multiband limiting → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
