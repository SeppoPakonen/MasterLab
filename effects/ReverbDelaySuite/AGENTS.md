# Reverb Delay Suite Effect Stub

## Reference
- Inspired by: Reverb & Delay
- Vendor: Waves
- Source catalog: IR1 Mono, IR1 Mono, IR1 Mono/Stereo, IR1 Mono/Stereo, IR1 efficient Stereo, IR1 efficient Stereo, IR1 full Stereo, IR1 full Stereo, IRLive Mono, IRLive Mono/Stereo, IRLive Stereo, TrueVerb Mono, TrueVerb Mono/Stereo, TrueVerb Stereo, RVerb Mono/Stereo, RVerb Stereo, H-Delay Mono, H-Delay Mono/Stereo, H-Delay Stereo, SuperTap 2-Taps Mono, SuperTap 2-Taps Mono, SuperTap 2-Taps Mono/Stereo, SuperTap 2-Taps Stereo, SuperTap 6-Taps Mono/Stereo, SuperTap 6-Taps Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves IR1 Convolution Reverb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Convolution reverb with IR management, resampling, and latency compensation. High-end convolution reverb with extensive IR parameter editing.
- Key features:
  - IR trimming, stretching, and windowing
  - True-stereo and surround convolution
  - Pre-delay and tail EQ
  - Background IR loading and caching
  - Extensive IR library (halls, plates, cars)
  - Time-stretch and compression for IR length
  - Direct/rewverb balance with early/late editing
  - Built-in parametric EQ pre/post
- Core building blocks:
  - DSP::ConvolutionEngine, DSP::LatencyBuffer, DSP::IRLibrary, DSP::EQStage, DSP::IRPreprocessor
- Signal/voice flow: Input → True-stereo convolution → EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves IR-Live
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Convolution reverb with IR management, resampling, and latency compensation. Low-latency convolution reverb for live use with smaller IR footprint.
- Key features:
  - IR trimming, stretching, and windowing
  - True-stereo and surround convolution
  - Pre-delay and tail EQ
  - Background IR loading and caching
  - Latency friendly convolution kernel
  - Simplified controls for quick setup
  - IR trimming to reduce CPU
  - Ideal for FOH or monitor chains
- Core building blocks:
  - DSP::ConvolutionEngine, DSP::LatencyBuffer, DSP::IRLibrary, DSP::EQStage, DSP::ConvolutionEngineLite, DSP::IRTrim
- Signal/voice flow: Input → Optimized convolution → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves TrueVerb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Algorithmic reverb (plate/hall/room) with early/late sections and modulation. Room simulator combining distance modeling and reverb tail.
- Key features:
  - Early reflection builder with geometric patterns
  - Late tail with diffusion network
  - Damping & modulation to avoid metallic ringing
  - Pre-delay and EQ stages
  - Direct + early reflection modeling based on listener/source distance
  - Combined reverb tail with adjustable RT60
  - “Outdoors” mode for ambient scenes
  - Frequency-dependent damping
- Core building blocks:
  - DSP::EarlyReflections, DSP::FeedbackDelayNetwork, DSP::DampingFilter, DSP::ModulatedDelay, DSP::RoomModel, DSP::FDNReverb, DSP::DistanceSimulator
- Signal/voice flow: Input → Distance/early reflection engine → Reverb tail → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Renaissance Reverb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Algorithmic reverb (plate/hall/room) with early/late sections and modulation. Versatile algorithmic reverb offering multiple classic algorithms.
- Key features:
  - Early reflection builder with geometric patterns
  - Late tail with diffusion network
  - Damping & modulation to avoid metallic ringing
  - Pre-delay and EQ stages
  - 16 reverb algorithms including plate, hall, ambience
  - Dual-band EQ for coloration
  - Early/late balance and modulation
  - Low CPU and zero latency
- Core building blocks:
  - DSP::EarlyReflections, DSP::FeedbackDelayNetwork, DSP::DampingFilter, DSP::ModulatedDelay, DSP::FDNReverb, DSP::EQStage
- Signal/voice flow: Input → Early reflections → Late algorithm → EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves H-Delay
- Category: delay
- Sidechain: N/A (ducking uses input program).
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Hybrid analog/digital delay with modulation and filtering.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Analog modeled ping-pong and LoFi modes
  - Tempo sync including host swing
  - High/low-pass on feedback path
  - Flange/chorus via modulation
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::AnalogModel, DSP::LFO
- Signal/voice flow: Input → Delay core → Feedback filters/modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves SuperTap
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Multi-tap delay with up to six taps, modulation, and spatial positioning.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Graphical tap editor for time/level/pan
  - Tap-specific modulation and EQ
  - Tempo sync and groove control
  - Feedback routing between taps
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::TapDelayEngine, DSP::ModMatrix
- Signal/voice flow: Input → Tap delay matrix → Feedback network → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
