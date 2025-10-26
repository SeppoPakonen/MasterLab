# Mastering Linear Suite Effect Stub

## Reference
- Inspired by: Mastering & Linear Phase
- Vendor: Waves
- Source catalog: L1 limiter Mono, L1 limiter Stereo, L1+ Ultramasimizer Stereo, L2 Mono, L2 Stereo, L3 MultiManimizer Stereo, L3 MultiMaximizer Mono, L3 UltraMaximizer Mono, L3 UltraMaximizer Stereo, L3-LL Multi Mono, L3-LL Multi Stereo, L3-LL Ultra Man, L3-LL Ultra Stereo, L316 Mono, L316 Stereo, LinEQ Broadband Mono, LinEQ Broadband Stereo, LinEQ Lowband Mono, LinEQ Lowband Stereo, LinMB Mone, LinMB Stereo, IDR Mono, IDR Stereo, Q, Q-Capture Mono, Q-Clone Mono, Q-Clone Stereo, Q1 Mono, Q1 Stereo, Q10 Mono, Q10 Stereo, Q2 Mono, Q2 Stereo, Q3 Mono, Q3 Stereo, Q4 Mono, Q4 Stereo, Q6 Mono, Q6 Stereo, Q8 Mono, Q8 Stereo, REQ 2 Stereo, REQ 2Mono, REQ 4 Stereo, REQ 4Mono, REQ 6 Stereo, REQ 6Mono, RBass Mono, RBass Stereo, RDeEsser Mono, RDeEsser Stereo, Renaissance Aux Mono, Renaissance Aux Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves L1 Limiter
- Category: mastering
- Sidechain: Internal look-ahead only.
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Classic brickwall limiter with look-ahead and dithering, often used on individual tracks.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Separation of threshold and output ceiling
  - Quantize/dither section integrated
  - Release curve presets
  - Modernizable as module inside L-series
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock
- Signal/voice flow: Input → Lookahead detector → Gain stage → Dither → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves L2 Limiter
- Category: mastering
- Sidechain: Internal
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Enhanced L1 with improved dithering (ARC) and IDR noise shaping.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - ARC auto-release reduces pumping
  - IDR dither/noise shaping options
  - Metering for attenuation and output
  - Widely used for mastering pre-ISPs
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock, DSP::ARCRelease
- Signal/voice flow: Input → Lookahead + ARC → Gain stage → IDR → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves L3 Multimaximizer
- Category: mastering
- Sidechain: Internal per-band detectors.
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Five-band look-ahead peak limiter managing frequency-specific limiting.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Priority controls to allocate limiting among bands
  - Linear-phase crossover for minimal artifacts
  - Master release shaping for tonal consistency
  - Can act as mastering EQ by adjusting priorities
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock, DSP::LinearPhaseCrossover, DSP::BandLimiter, DSP::PriorityAllocator
- Signal/voice flow: Input → Linear-phase bands → Per-band limiter → Recombine → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves L3-LL Multimaximizer
- Category: mastering
- Sidechain: Internal per-band detectors.
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Low-latency version of L3 using minimum-phase crossovers for live use.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Latency reduced for tracking
  - Preserves priority system
  - Slight phase coloration due to min-phase crossovers
  - Same GUI/workflow as L3
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock, DSP::MinPhaseCrossover, DSP::BandLimiter, DSP::PriorityAllocator
- Signal/voice flow: Input → Min-phase bands → Band limiter → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves L316 Multimaximizer
- Category: mastering
- Sidechain: Internal per-band detectors.
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. 16-band linear-phase maximizer for detailed spectral limiting.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Target curves for broadcast/film standards
  - Solo each band for focus
  - Built-in paragraphic EQ overlay
  - Linear-phase FIR with lookahead
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock, DSP::LinearPhaseCrossover, DSP::MultiBandLimiter, DSP::EQOverlay
- Signal/voice flow: Input → 16-band limiter network → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Linear Phase EQ
- Category: tone shaping
- Sidechain: N/A
- Processing blueprint: IIR parametric/Shelving EQ banks with analyzer overlay. Linear-phase mastering EQ with minimal phase shift.
- Key features:
  - Multiple filter types per band
  - Static and dynamic gain linking
  - Analyzer overlay/M/S options
  - Per-band saturation (where applicable)
  - Minimum, zero, and split linear-phase modes
  - Band solo/audition
  - Resonant shelves with ZP curves
  - Latency compensation reporting
- Core building blocks:
  - DSP::ParametricEQ, DSP::Biquad, DSP::Analyzer, DSP::LinearPhaseEQ, DSP::LatencyManager
- Signal/voice flow: Input → FIR filter bank → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Linear Phase Multiband
- Category: dynamics
- Sidechain: Internal per-band detectors.
- Processing blueprint: Multi-band dynamics engine with linear-phase crossover and per-band compression/expansion. Linear-phase 5-band compressor suited for mastering and restoration.
- Key features:
  - Adjustable crossover slopes with latency compensation
  - Per-band solo/mute and gain trim
  - Dynamic EQ bells with external sidechain (C6)
  - Master limiter/post gain staging
  - Adaptive thresholds tied to overall loudness
  - Solo/mute per band with crossover smoothing
  - ARC release per band to avoid pumping
  - Modeled after L3 engine without limiting
- Core building blocks:
  - DSP::LinearPhaseCrossover, DSP::BandDynamics, DSP::EnvelopeDetector, DSP::GainComputer, DSP::LatencyBuffer, DSP::ARCRelease
- Signal/voice flow: Input → Linear-phase crossover → Band dynamics → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves IDR Dither
- Category: mastering utility
- Sidechain: N/A
- Processing blueprint: Noise-shaped dither with bit-depth conversion. Standalone IDR dither/noise shaping module for mastering chain integration.
- Key features:
  - Triangular, rectangular, UV22HR noise shaping
  - Auto black detection to gate dither
  - Integrates post-limiter
  - Supports surround channel linking
  - Type1/Type2 noise shaping curves
  - Quantize to 8–24 bit
  - Auto black gating
  - Noise shaping to match L-series dithering
- Core building blocks:
  - DSP::DitherGenerator, DSP::NoiseShaper, DSP::BitDepthConverter
- Signal/voice flow: Input → Dither/Noise shape → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Q-Clone/Q-Series
- Category: mastering EQ
- Sidechain: N/A (Q-Capture uses insert send/return).
- Processing blueprint: Linear-phase FIR EQ or hardware capture convolution. Q-Clone hardware EQ capture with accompanying Q1–Q10 paragraphic EQ plug-ins.
- Key features:
  - Zero-phase FIR filtering
  - Impulse capture and interpolation
  - Latency reporting/compensation
  - Hardware curve morphing (Q-Clone)
  - Q-Capture records hardware EQ impulse responses
  - Q-Clone applies captured curve via convolution
  - Q-series offer minimal-phase digital EQ with variable Q
  - Supports M/S and L/R unlink
- Core building blocks:
  - DSP::LinearPhaseEQ, DSP::ImpulseCapture, DSP::LatencyBuffer, DSP::ConvolutionEQ, DSP::ParametricEQ
- Signal/voice flow: Input → Hardware capture or digital EQ processing → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Renaissance EQ
- Category: tone shaping
- Sidechain: N/A
- Processing blueprint: IIR parametric/Shelving EQ banks with analyzer overlay. Warm-sounding paragraphic EQ with analog-style curves.
- Key features:
  - Multiple filter types per band
  - Static and dynamic gain linking
  - Analyzer overlay/M/S options
  - Per-band saturation (where applicable)
  - Selectable filter types per band (Type I/II)
  - Shelf asymmetry modes
  - Built-in analyzer
  - Analog saturation toggle
- Core building blocks:
  - DSP::ParametricEQ, DSP::Biquad, DSP::Analyzer, DSP::AnalogDrive
- Signal/voice flow: Input → Renaissance EQ filters → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Renaissance Bass
- Category: enhancement
- Sidechain: Internal
- Processing blueprint: Psychoacoustic low-frequency enhancement using harmonic resynthesis. R-Bass subharmonic enhancer using psychoacoustic modelling.
- Key features:
  - Generates controllable harmonics one octave above LFE
  - Subharmonic synth with phase aligned mixing
  - Crossover for bus or LFE routing
  - Output meter to avoid over-excursion
  - Generates harmonics based on chosen freq
  - Intensity controls amount of synthesis
  - Range slider sets how deep generation goes
  - Monitor mode to audition synthesized component
- Core building blocks:
  - DSP::EnvelopeFollower, DSP::PitchTracker, DSP::SubSynth, DSP::PhaseAligner, DSP::MixStage
- Signal/voice flow: Input → Sub synthesis → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Renaissance DeEsser
- Category: dynamics
- Sidechain: Internal bandpass; no external key.
- Processing blueprint: Split-band compressor aimed at sibilant range with frequency listen. Smooth split-band de-esser part of Renaissance suite.
- Key features:
  - Wide-band vs split-band modes
  - Frequency sweeping and audition
  - Auto/Manual threshold
  - Parallel mix for natural results
  - Two modes (Audio/Sidechain) for frequency referencing
  - Adaptive threshold for natural response
  - Look-ahead to catch sibilants
  - Output sibilant monitoring
- Core building blocks:
  - DSP::SidechainBandpass, DSP::EnvelopeDetector, DSP::GainComputer, DSP::BlendStage, DSP::BandpassDetector
- Signal/voice flow: Input → Bandpass detection → Gain reduction → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Renaissance Axx
- Category: dynamics
- Sidechain: Internal
- Processing blueprint: Optical-style leveling amplifier with program-dependent release and saturation. Easy compressor with fixed attack/release ideal for guitars and vocals.
- Key features:
  - Two-parameter interface (gain/reduction)
  - Program dependent timing curves
  - Optional harmonic drive
  - GR history meter for set-and-forget workflows
  - Single threshold control with auto makeup
  - Warmth knob adds harmonic saturation
  - Limiter prevents output overs
  - Great for quick tracking compression
- Core building blocks:
  - DSP::OptoDetector, DSP::GainComputer, DSP::HarmonicStage, DSP::OptoCompressor, DSP::SaturationStage
- Signal/voice flow: Input → Opto-style detector → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
