# Dynamics Level Suite Effect Stub

## Reference
- Inspired by: Dynamics & Level
- Vendor: Steinberg
- Source catalog: Dynamics, VSTDynamics, Comp Mono, Comp Stereo, Compressor, Compressor Mono, Compressor Stereo, CleanComp, VintageCompressor, MultiCompressor, MultibandCompresser, Maximizer, Leveler, Limiter, Puncher, PeakMaster, Gate, Expander, Noise Gate, EnvelopeShaper, MIDI Gate, Channel Mono, Channel Mono/Stereo, Channel Stereo, uv22HR, w22

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg Dynamics
- Category: dynamics
- Sidechain: External key via VST3; internal filters per stage.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. Legacy Cubase/Nuendo dynamics rack combining gate, compressor, and limiter stages in one plugin.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Switchable module order and per-block bypass
  - Shared sidechain filters feeding gate and compressor
  - Limiter stage with soft clip option
  - GUI meters for each stage to aid gain staging
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::SignalRouter, DSP::GateModule, DSP::CompressorModule, DSP::LimiterModule
- Signal/voice flow: Input → Gate → Compressor → Limiter → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Compressor
- Category: dynamics
- Sidechain: External (VST3) plus internal HP filter.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. General-purpose compressor with soft knee, auto release, and mix control.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Switchable peak/RMS detector
  - Auto makeup and dedicated mix knob
  - Envelope display for visual feedback
  - Classic/modern curve switch for knee response
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::MixStage
- Signal/voice flow: Input → Sidechain HPF → Detector → Gain computer → Mix stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Clean Compressor
- Category: dynamics
- Sidechain: External sidechain available; default internal.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. Transparent compressor variant tuned for low distortion and linear phase make-up.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Look-ahead mode for zero overshoot
  - Adaptive release for minimal pumping
  - Optional auto gain compensation
  - Knee/ratio macros for quick mastering setups
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::LookaheadBuffer
- Signal/voice flow: Input → Lookahead split → Detector → Gain computer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg VintageCompressor
- Category: dynamics
- Sidechain: Internal opto detector only.
- Processing blueprint: Feed-forward VCA compressor with RMS/peak detector, soft knee, look-ahead, and parallel blend. Optical leveling amplifier modeled on LA-2A style behaviour with program-dependent timing.
- Key features:
  - Attack/release in ms with adaptive auto mode
  - Mix (parallel compression) and range controls
  - Sidechain EQ section for de-essing/ducking
  - Envelope smoothing to avoid zipper noise
  - Two-mode response (Soft/Hard) replicating LA/1176 flavours
  - Drive knob introducing harmonics
  - Stereo link with dual mono option
  - Gain reduction meter in dB and %
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GainStage, DSP::ParameterSmoother, DSP::OptoDetector, DSP::SaturationStage
- Signal/voice flow: Input → Opto cell → Gain stage → Harmonic drive → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg MultibandCompressor
- Category: dynamics
- Sidechain: Internal per-band detectors; no external bus.
- Processing blueprint: Multi-band dynamics engine with linear-phase crossover and per-band compression/expansion. Four-band compressor with adjustable crossover slopes for mastering duties.
- Key features:
  - Adjustable crossover slopes with latency compensation
  - Per-band solo/mute and gain trim
  - Dynamic EQ bells with external sidechain (C6)
  - Master limiter/post gain staging
  - Crossover frequencies with 6/12/24 dB options
  - Individual band solo/mute and gain trim
  - Link/Hold options for release synchronisation
  - Common limiter after band summing
- Core building blocks:
  - DSP::LinearPhaseCrossover, DSP::BandDynamics, DSP::EnvelopeDetector, DSP::GainComputer, DSP::LatencyBuffer, DSP::LimiterModule
- Signal/voice flow: Input → Linear-phase crossover → Band dynamics → Band mixer → Limiter → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Maximizer
- Category: mastering
- Sidechain: Internal look-ahead only.
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Simple look-ahead maximizer focused on final loudness lift with ceiling control.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Optimized for post-fader insert usage
  - Release presets for punch vs transparent modes
  - True peak ceiling option
  - Soft clip when pushed past threshold
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock
- Signal/voice flow: Input → Lookahead detector → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Leveler
- Category: dynamics
- Sidechain: Internal RMS detector; no external key.
- Processing blueprint: Optical-style leveling amplifier with program-dependent release and saturation. Automatic leveler styled after classic broadcast leveling amplifiers.
- Key features:
  - Two-parameter interface (gain/reduction)
  - Program dependent timing curves
  - Optional harmonic drive
  - GR history meter for set-and-forget workflows
  - Single gain knob with auto makeup
  - Program-dependent release curves
  - Vintage saturation toggle
  - Gain reduction history meter
- Core building blocks:
  - DSP::OptoDetector, DSP::GainComputer, DSP::HarmonicStage, DSP::RMSDetector, DSP::SaturationStage
- Signal/voice flow: Input → RMS detector → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Limiter
- Category: mastering
- Sidechain: Internal
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Fast brickwall limiter for track buses with simple interface.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Release presets including auto mode
  - Soft clip switch to retain transients
  - Metering for gain reduction and output
  - Ceiling readout to coordinate with UV22HR
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock, DSP::LimiterStage
- Signal/voice flow: Input → Peak detector → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Puncher
- Category: dynamics
- Sidechain: Internal detectors per band.
- Processing blueprint: Transient designer splitting attack and sustain envelopes with adjustable gain shaping. Transient processor that emphasises attacks while controlling sustain.
- Key features:
  - Independent attack/sustain gain & timing
  - Frequency selective focus filter
  - Optional clipper to restrain spikes
  - Mid/Side routing for stereo material
  - Adjustable attack/sustain amount
  - Focus filter to limit processing to certain bands
  - Blend knob for subtlety
  - Clip guard to avoid overs
- Core building blocks:
  - DSP::TransientSplitter, DSP::EnvelopeDetector, DSP::GainStage, DSP::SidechainEQ, DSP::ClipGuard
- Signal/voice flow: Input → Attack/Sustain detection → Gain shaping → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg PeakMaster
- Category: mastering
- Sidechain: Internal
- Processing blueprint: Brickwall limiter with oversampled detection, release shaping, and dithering. Legacy maximizer with emphasis on radio-ready loudness.
- Key features:
  - True-peak detection with oversampling
  - Auto Release Control / release presets
  - Ceiling with K-system references
  - Noise shaping/dither integration
  - Adaptive release tuned for steady-state material
  - Simplified controls for quick mastering
  - Optional soft knee limiter
  - Meter focusing on perceived loudness boost
- Core building blocks:
  - DSP::LookaheadBuffer, DSP::PeakDetector, DSP::GainComputer, DSP::DitherShaper, DSP::MeterBlock, DSP::SlewLimiter
- Signal/voice flow: Input → Detector → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Gate
- Category: dynamics
- Sidechain: External key with HP/LP filters.
- Processing blueprint: Noise gate with hysteresis, look-ahead, and floor control. Standard gate for drums and dialog cleanup.
- Key features:
  - Sidechain HP/LP filter and key listen
  - Adjustable hold and hysteresis
  - Soft/Hard gating curves
  - Option for expander mode
  - Adjustable hold and hysteresis
  - Key listen mode
  - Sidechain filter with resonance
  - Range control for downward expansion
- Core building blocks:
  - DSP::SidechainInput, DSP::KeyFilter, DSP::EnvelopeDetector, DSP::GainComputer, DSP::GateStage
- Signal/voice flow: Input → Sidechain filter → Detector → Gate gain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Expander
- Category: dynamics
- Sidechain: External key available.
- Processing blueprint: Downward expander for noise floor management. Downward expander for subtle noise floor control.
- Key features:
  - Ratio and range controls
  - Program dependent release
  - Integration with gate sections
  - Key listen monitoring
  - Ratio/threshold with soft knee
  - Separate expansion range control
  - Lookahead option for smooth transitions
  - Stereo link toggle
- Core building blocks:
  - DSP::SidechainInput, DSP::EnvelopeDetector, DSP::GainComputer
- Signal/voice flow: Input → Sidechain EQ → Detector → Expansion stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Noise Gate
- Category: restoration
- Sidechain: External key with limited filters.
- Processing blueprint: Noise, click, and breath removal using adaptive FFT/thresholding. Simplified gate optimised for live tracking.
- Key features:
  - Adaptive learning of noise prints
  - Look-ahead click detection
  - Artifact smoothing to avoid chirps
  - Separate wet/dry for auditing
  - One-knob threshold with auto release
  - Sidechain HP filter only for ease
  - Visual gate open indicator
  - Range fixed to full mute for reliability
- Core building blocks:
  - DSP::FFTAnalyzer, DSP::NoiseProfile, DSP::SpectralGate, DSP::ArtifactSuppressor, DSP::SidechainInput, DSP::KeyFilter, DSP::GateStage
- Signal/voice flow: Input → Sidechain HP → Detector → Gate → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Envelope Shaper
- Category: dynamics
- Sidechain: Internal detectors with frequency focus.
- Processing blueprint: Transient designer splitting attack and sustain envelopes with adjustable gain shaping. Dedicated transient designer splitting attack and sustain for drum work.
- Key features:
  - Independent attack/sustain gain & timing
  - Frequency selective focus filter
  - Optional clipper to restrain spikes
  - Mid/Side routing for stereo material
  - Attack and sustain gain with independent timing
  - Focus filter emphasises selected frequency band
  - Limiter to prevent overs
  - Mid/Side option for stereo buses
- Core building blocks:
  - DSP::TransientSplitter, DSP::EnvelopeDetector, DSP::GainStage, DSP::SidechainEQ, DSP::BandpassDetector
- Signal/voice flow: Input → Focus filter → Transient detection → Attack/Sustain gain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg MIDI Gate
- Category: dynamics
- Sidechain: Triggered via MIDI event bus.
- Processing blueprint: Noise gate with hysteresis, look-ahead, and floor control. Gate triggered from MIDI notes for rhythmic chopping.
- Key features:
  - Sidechain HP/LP filter and key listen
  - Adjustable hold and hysteresis
  - Soft/Hard gating curves
  - Option for expander mode
  - Velocity-to-depth mapping
  - Hold and release tied to note length
  - Key range filtering
  - Sync option for host tempo
- Core building blocks:
  - DSP::SidechainInput, DSP::KeyFilter, DSP::EnvelopeDetector, DSP::GainComputer, DSP::MIDIGate, DSP::EnvelopeGenerator, DSP::GainStage
- Signal/voice flow: Audio input + MIDI note → Gate envelope → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Channel Strip
- Category: channel strip
- Sidechain: External key for dynamics blocks.
- Processing blueprint: Integrated EQ + dynamics + routing with modular sections. Aggregated strip (EQ, compressor, gate, saturation) as found in Cubase channel settings.
- Key features:
  - Gain staging and polarity options
  - Dynamics order switching (Gate→Comp or Comp→Gate)
  - Saturation/drive stages per module
  - Per-section bypass & preset system
  - Module order configuration
  - Analyzer overlay shared with StudioEQ
  - Drive and tape saturator modules
  - Presets aligned with MixConsole channel strip
- Core building blocks:
  - DSP::SignalRouter, DSP::ParametricEQ, DSP::Compressor, DSP::Gate, DSP::NonlinearStage, DSP::CompressorModule, DSP::GateModule, DSP::SaturationStage
- Signal/voice flow: Input → HPF → Gate → Compressor → EQ → Saturation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg UV22HR
- Category: mastering utility
- Sidechain: N/A
- Processing blueprint: Noise-shaped dither with bit-depth conversion. High-resolution dithering algorithm for 24→16 bit conversion.
- Key features:
  - Triangular, rectangular, UV22HR noise shaping
  - Auto black detection to gate dither
  - Integrates post-limiter
  - Supports surround channel linking
  - UV22HR noise-shaping curves with 44.1/48 kHz tuning
  - Auto black to mute dither on digital silence
  - Supports surround channel linking
  - Works post-limiter for highest fidelity
- Core building blocks:
  - DSP::DitherGenerator, DSP::NoiseShaper, DSP::BitDepthConverter
- Signal/voice flow: Input → UV22HR noise shaping → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
