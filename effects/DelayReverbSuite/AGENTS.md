# Delay Reverb Suite Effect Stub

## Reference
- Inspired by: Delay & Reverb
- Vendor: Steinberg
- Source catalog: DoubleDelay, ModDelay, MonoDelay, PingPongDelay, StereoDelay, StereoEcho, Reverb A, Reverb B, Reverb C, NaturalVerb, Roomworks, Roomworks SE, ReVerence, MonoToStereo

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg DoubleDelay
- Category: delay
- Sidechain: Tempo sync per line or milliseconds.
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Dual delay lines with independent time/feedback for creating complex echoes.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Two delay lines routable serial/parallel
  - Per-line feedback and filter
  - Modulation depth for chorus-like tails
  - Cross-feedback for ping-pong textures
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage
- Signal/voice flow: Input → Delay A/B → Feedback matrix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg ModDelay
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Delay with built-in modulation for chorus/slap effects.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Sine/triangle LFO options
  - Stereo width via phase offset
  - Diffusion to smear repeats
  - Tempo sync and note divisions
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::LFO, DSP::StereoWidener
- Signal/voice flow: Input → Delay line with modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg MonoDelay
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Resource-light mono delay for quick slapback tasks.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Feedback with high/low cut
  - Tempo sync and tap tempo
  - LFO for subtle wow
  - Output mix control
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::MixStage
- Signal/voice flow: Input → Delay → Feedback filter → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg PingPongDelay
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Stereo ping-pong delay ideal for rhythmic movement.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Alternate left/right taps with spread control
  - Feedback filters per side
  - Sync to host tempo
  - Width control to collapse to mono if needed
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::StereoDelay
- Signal/voice flow: Input → Ping-pong taps → Feedback → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg StereoDelay
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Dual stereo delay with independent controls for each channel.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Independent time/feedback per channel
  - Offset to create Haas effect
  - Filtering and modulation per side
  - Wet/dry crossmix
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::DualDelay, DSP::ModLFO
- Signal/voice flow: Input → Left/Right delay engines → Crossmix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg StereoEcho
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Vintage inspired echo with diffusion for tape-like ambience.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Pre-delay with wow/flutter option
  - Built-in diffusion to blur repeats
  - Tone control emphasising tape roll-off
  - Saturation before repeats
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::WowFlutter, DSP::Diffusion, DSP::Saturation
- Signal/voice flow: Input → Saturation → Delay/diffusion → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Algorithmic Reverb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Algorithmic reverb (plate/hall/room) with early/late sections and modulation. Legacy “Reverb A/B/C” algorithms covering plates and halls.
- Key features:
  - Early reflection builder with geometric patterns
  - Late tail with diffusion network
  - Damping & modulation to avoid metallic ringing
  - Pre-delay and EQ stages
  - Early reflection patterns selectable
  - Late tail damping and diffusion
  - Pre-delay with tempo sync
  - Dual EQ (pre/post) for tonal control
- Core building blocks:
  - DSP::EarlyReflections, DSP::FeedbackDelayNetwork, DSP::DampingFilter, DSP::ModulatedDelay, DSP::FDNReverb, DSP::EQStage
- Signal/voice flow: Input → Early reflections → Late reverb → EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg NaturalVerb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Algorithmic reverb (plate/hall/room) with early/late sections and modulation. Lightweight reverb with simple controls suited for inserts.
- Key features:
  - Early reflection builder with geometric patterns
  - Late tail with diffusion network
  - Damping & modulation to avoid metallic ringing
  - Pre-delay and EQ stages
  - Room size and color macros
  - Damping for high-frequency control
  - Low CPU footprint for multiple instances
  - Stereo width control
- Core building blocks:
  - DSP::EarlyReflections, DSP::FeedbackDelayNetwork, DSP::DampingFilter, DSP::ModulatedDelay, DSP::FDNReverb, DSP::StereoWidth
- Signal/voice flow: Input → Diffusion network → Damping → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg RoomWorks
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Algorithmic reverb (plate/hall/room) with early/late sections and modulation. More advanced algorithmic reverb with modulation and density controls.
- Key features:
  - Early reflection builder with geometric patterns
  - Late tail with diffusion network
  - Damping & modulation to avoid metallic ringing
  - Pre-delay and EQ stages
  - Adjustable density and diffusion
  - Two-stage EQ (damping + post EQ)
  - Modulation to avoid metallic ringing
  - Supports early/late mix balancing
- Core building blocks:
  - DSP::EarlyReflections, DSP::FeedbackDelayNetwork, DSP::DampingFilter, DSP::ModulatedDelay, DSP::FDNReverb, DSP::EQStage
- Signal/voice flow: Input → Early reflections → Late FDN with modulation → EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg REVerence
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Convolution reverb with IR management, resampling, and latency compensation. Convolution reverb with high-quality impulse library.
- Key features:
  - IR trimming, stretching, and windowing
  - True-stereo and surround convolution
  - Pre-delay and tail EQ
  - Background IR loading and caching
  - True-stereo IR support
  - Stretch and reverse controls
  - Pre-EQ/post-EQ around convolution
  - Background loading and prefetch
- Core building blocks:
  - DSP::ConvolutionEngine, DSP::LatencyBuffer, DSP::IRLibrary, DSP::EQStage
- Signal/voice flow: Input → IR convolution → Tail EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg MonoToStereo
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Utility upmixer converting mono sources to pseudo stereo.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Delay/phase offsets for width
  - Optional reverb injection for ambience
  - Low cut on side signal to keep bass mono
  - Correlation meter
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::MonoSplitter, DSP::PhaseOffset, DSP::StereoWidener
- Signal/voice flow: Input → Mono splitter → Phase/delay decorrelation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
