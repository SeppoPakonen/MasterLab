# Filter Design Suite Effect Stub

## Reference
- Inspired by: Filter & Sound Design
- Vendor: Steinberg
- Source catalog: EQ 1, FilterVST, NuendoEQ2, StepFiter, StudioEQ, Tonic, Tranceformer, DualFiter, Externalizer, Grungelizer, ToolsOne, RingModulator

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg EQ & Filters
- Category: tone shaping
- Sidechain: N/A
- Processing blueprint: IIR parametric/Shelving EQ banks with analyzer overlay. Collection of EQ/Filter processors (EQ1, StudioEQ, StepFilter, Tonic, Tranceformer) sharing core filter architecture.
- Key features:
  - Multiple filter types per band
  - Static and dynamic gain linking
  - Analyzer overlay/M/S options
  - Per-band saturation (where applicable)
  - Parametric bands with analyzer overlay (StudioEQ)
  - StepFilter sequenced filter gating
  - Tonic provides dual multimode filters with LFO
  - Tranceformer adds spectral morphing options
- Core building blocks:
  - DSP::ParametricEQ, DSP::Biquad, DSP::Analyzer, DSP::StateVariableFilter, DSP::StepSequencer, DSP::SpectralMorph
- Signal/voice flow: Input → Selected EQ/Filter module → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg DualFilter
- Category: filtering
- Sidechain: Envelope follower and LFO modulation.
- Processing blueprint: Dual multi-mode filters with modulation matrix. Dual multimode filters routable in serial or parallel.
- Key features:
  - LP/BP/HP/notch with resonance drive
  - Step sequencer or LFO modulation
  - Envelope follower/key tracking
  - Stereo offset for widening effects
  - Morphable routing (series/parallel)
  - Independent resonance and drive per filter
  - Mod matrix for LFO/envelope control
  - Tempo-synced step sequencer
- Core building blocks:
  - DSP::StateVariableFilter, DSP::ModMatrix, DSP::EnvelopeFollower, DSP::LFO, DSP::DualFilter
- Signal/voice flow: Input → Filter A/B with modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Externalizer
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Early binaural/spatializer effect simulating speaker placement around the listener.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Head-related transfer function (HRTF) models
  - Room size and reflective surfaces
  - Distance and elevation controls
  - Optional LFE feed
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::HRTFConvolver, DSP::RoomModel, DSP::DelayLine
- Signal/voice flow: Input → HRTF convolution → Room response → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Grungelizer
- Category: saturation
- Sidechain: N/A
- Processing blueprint: Waveshaping distortion with tone filters and oversampling. Vinyl/tape degradation simulator adding noise, hum, and wow.
- Key features:
  - Selectable transfer curves (tube, transistor, diode)
  - Pre/post EQ tone sculpting
  - Mix control for parallel drive
  - Oversampling to reduce aliasing
  - Adjustable crackle, noise, and hum layers
  - Age control affecting EQ and wow
  - Tempo sync for wow rate
  - Wet/dry blend for subtle ageing
- Core building blocks:
  - DSP::Oversampler, DSP::WaveShaper, DSP::EQStage, DSP::MixStage, DSP::NoiseGenerator, DSP::WowFlutter
- Signal/voice flow: Input → Noise/hum injection + wow → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg ToolsOne
- Category: utility
- Sidechain: N/A
- Processing blueprint: Routing, test, and diagnostic tools for session management. Legacy multi-effect bundle (filter, delay, modulation) packaged in a simple interface.
- Key features:
  - Routing matrices and gain trims
  - Signal generators (pink, sine, SMPTE)
  - Latency compensation helpers
  - Format conversions (6→2, mono→stereo)
  - Macro controls for filter sweeps and delays
  - Assignable modulation LFO
  - Preset management with morphing
  - CPU-light for legacy projects
- Core building blocks:
  - DSP::SignalRouter, DSP::Generator, DSP::MatrixMixer, DSP::MacroController, DSP::FilterStage, DSP::DelayStage
- Signal/voice flow: Input → Macro-controlled FX chain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Ring Modulator
- Category: modulation
- Sidechain: Carrier oscillator inside plugin.
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Ring modulation effect for metallic textures.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Carrier frequency with tempo sync
  - Quadrature mode for stereo movement
  - Envelope-driven carrier amplitude
  - Mix stage for subtlety
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::RingModulator, DSP::Oscillator, DSP::EnvelopeFollower
- Signal/voice flow: Input × Carrier oscillator → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
