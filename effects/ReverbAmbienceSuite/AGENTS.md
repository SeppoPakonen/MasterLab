# Reverb Ambience Suite Effect Stub

## Reference
- Inspired by: Reverb & Ambience
- Vendor: Waves
- Source catalog: H-Reverb Hybrid Reverb, Abbey Road Chambers, Magma Springs, Lofi Space, CLA EchoSphere, IR-Live

## Implementation Plan
### Waves H-Reverb Hybrid Reverb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Hybrid FIR/IIR reverb combining finite impulse response and feedback topology with extensive modulation.
- Key features:
  - FIR early reflections with resizable tap pattern
  - Feedback design section with rich modulation and drive
  - Dynamics module for ducking or expanding reverb tail
  - Supports surround configurations up to 7.1
- Core building blocks:
  - DSP::HybridReverb, DSP::FIRTaps, DSP::FeedbackNetwork, DSP::DynamicsModule, DSP::ModulationMatrix
- Signal/voice flow: Input → FIR early reflections → Feedback tail network → Dynamics stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Abbey Road Chambers
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Convolution reverb sampling Abbey Road's historic echo chambers with speaker/mic placement modeling.
- Key features:
  - Chamber, plate, and RS124 drive modeling
  - Speaker and microphone repositioning with delay compensation
  - Pre-delay tape/tube saturation emulation
  - Dry/wet and chamber send matrix for parallel setups
- Core building blocks:
  - DSP::ConvolutionEngine, DSP::SpeakerModel, DSP::MicModel, DSP::TapeSaturation, DSP::RoutingMatrix
- Signal/voice flow: Input → Preamp/tape stage → Convolution engine → Mix matrix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Magma Springs
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Spring reverb collection with seven tank models and flexible tone shaping.
- Key features:
  - Seven spring tanks with resonance and tension controls
  - Drive and low-cut/high-cut tone shaping
  - Modulation to reduce boing artifacts
  - Gate and damping for percussion use
- Core building blocks:
  - DSP::SpringReverb, DSP::NonlinearDrive, DSP::ToneFilters, DSP::DampingControl
- Signal/voice flow: Input → Tone shaping → Spring tank model → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Lofi Space
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Combined vintage reverb and delay with degradation controls for nostalgic textures.
- Key features:
  - Dual-engine reverb and delay with tape age controls
  - Noise, wow/flutter, and saturation dials
  - HP/LP filters with resonance for dub effects
  - Syncable delay with feedback freeze
- Core building blocks:
  - DSP::DelayReverbHybrid, DSP::DegradeModel, DSP::TapeModulation, DSP::FilterBlock
- Signal/voice flow: Input → Preamp/drive → Delay/Reverb network → Degrade stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves CLA EchoSphere
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Signature CLA plate reverb paired with slapback delay sharing simple macro controls.
- Key features:
  - Plate algorithm with pre-echo and tone controls
  - Slap delay with tempo sync or manual timing
  - Three-simple knob workflow (reverb, delay, balance)
  - Optional analog noise and hum for realism
- Core building blocks:
  - DSP::PlateReverb, DSP::SlapDelay, DSP::AnalogNoise, DSP::MacroController
- Signal/voice flow: Input → Plate + Delay engines → Macro blend → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves IR-Live Convolution Reverb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Convolution reverb optimized for live sound with zero latency preset switching.
- Key features:
  - Low CPU convolution engine for live consoles
  - Impulse trimming and time-stretch for venue match
  - Snapshot recall with crossfade to avoid artifacts
  - Parametric EQ on wet signal for quick tuning
- Core building blocks:
  - DSP::ConvolutionEngine, DSP::ImpulseManager, DSP::SnapshotCrossfade, DSP::WetEQ
- Signal/voice flow: Input → Convolution engine → Wet EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
