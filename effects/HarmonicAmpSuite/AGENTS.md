# Harmonic Amp Suite Effect Stub

## Reference
- Inspired by: Harmonic & Amp
- Vendor: Steinberg
- Source catalog: AmpSimulstor, Distortion, Overdrive, DaTube, Metalizer, QuadraFuzz, WahWah, BitCrusher

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg AmpSimulator
- Category: amp & saturation
- Sidechain: N/A
- Processing blueprint: Amp head + cabinet simulation with tone stack and mic modeling. Classic Cubase amp simulator with selectable amp types and cabinet IRs.
- Key features:
  - Multi-stage pre/power amp saturation
  - Tone stack models (Fender/Marshall/etc.)
  - Cab IR loader with mic blend
  - Effects loop send/return
  - Amp models ranging from clean to high gain
  - Cabinet/mic selection with EQ
  - Integrated noise gate and limiter
  - Supports parallel DI blend
- Core building blocks:
  - DSP::PreampStage, DSP::ToneStack, DSP::PowerAmpStage, DSP::CabIR, DSP::MicBlender, DSP::AmpHead, DSP::NoiseGate, DSP::BlendStage
- Signal/voice flow: Input → Amp stage → Cabinet IR/EQ → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Distortion
- Category: amp & saturation
- Sidechain: N/A
- Processing blueprint: Amp head + cabinet simulation with tone stack and mic modeling. General-purpose distortion with multiple clipping curves for synths and guitars.
- Key features:
  - Multi-stage pre/power amp saturation
  - Tone stack models (Fender/Marshall/etc.)
  - Cab IR loader with mic blend
  - Effects loop send/return
  - Overdrive, tube, transistor, hard clip modes
  - Pre/post tone filters
  - Dynamics control for input sensitivity
  - Output limiter to control peaks
- Core building blocks:
  - DSP::PreampStage, DSP::ToneStack, DSP::PowerAmpStage, DSP::CabIR, DSP::MicBlender, DSP::WaveShaper, DSP::ToneFilter, DSP::DynamicsTrim
- Signal/voice flow: Input → Pre filter → Waveshaper → Post EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Overdrive
- Category: saturation
- Sidechain: N/A
- Processing blueprint: Waveshaping distortion with tone filters and oversampling. Simplified stomp-style overdrive with tone and drive controls.
- Key features:
  - Selectable transfer curves (tube, transistor, diode)
  - Pre/post EQ tone sculpting
  - Mix control for parallel drive
  - Oversampling to reduce aliasing
  - Center frequency tone knob
  - Drive interacts with diode clipper model
  - Mix knob for parallel grit
  - Low CPU for insert stacks
- Core building blocks:
  - DSP::Oversampler, DSP::WaveShaper, DSP::EQStage, DSP::MixStage, DSP::DiodeClipper, DSP::ToneControl
- Signal/voice flow: Input → Tone → Diode clipper → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg DaTube
- Category: amp & saturation
- Sidechain: N/A
- Processing blueprint: Amp head + cabinet simulation with tone stack and mic modeling. Tube saturation model great for warming vocals and synths.
- Key features:
  - Multi-stage pre/power amp saturation
  - Tone stack models (Fender/Marshall/etc.)
  - Cab IR loader with mic blend
  - Effects loop send/return
  - Select between triode/pentode responses
  - Bias and drive controls to shape harmonics
  - Built-in 3-band tonestack
  - Soft clipping limiter to prevent overs
- Core building blocks:
  - DSP::PreampStage, DSP::ToneStack, DSP::PowerAmpStage, DSP::CabIR, DSP::MicBlender, DSP::TubeModel, DSP::LimiterStage
- Signal/voice flow: Input → Tube stage → Tone EQ → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Metalizer
- Category: amp & saturation
- Sidechain: N/A
- Processing blueprint: Amp head + cabinet simulation with tone stack and mic modeling. Metallic flanging/distortion effect combining comb filtering and overdrive.
- Key features:
  - Multi-stage pre/power amp saturation
  - Tone stack models (Fender/Marshall/etc.)
  - Cab IR loader with mic blend
  - Effects loop send/return
  - Dual-delay comb lines with feedback
  - Drive stage before comb network
  - Modulation of comb delay for shimmer
  - Blend for subtle metal sheen
- Core building blocks:
  - DSP::PreampStage, DSP::ToneStack, DSP::PowerAmpStage, DSP::CabIR, DSP::MicBlender, DSP::CombFilter, DSP::LFO, DSP::DriveStage
- Signal/voice flow: Input → Drive → Comb filter pair → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg QuadraFuzz
- Category: amp & saturation
- Sidechain: N/A
- Processing blueprint: Amp head + cabinet simulation with tone stack and mic modeling. Four-band distortion with independent drive types per band.
- Key features:
  - Multi-stage pre/power amp saturation
  - Tone stack models (Fender/Marshall/etc.)
  - Cab IR loader with mic blend
  - Effects loop send/return
  - Band-specific drive models (tube/tape/rectifier)
  - Crossover with adjustable slopes
  - Gate per band to tame hiss
  - Stereo and mid/side drive options
- Core building blocks:
  - DSP::PreampStage, DSP::ToneStack, DSP::PowerAmpStage, DSP::CabIR, DSP::MicBlender, DSP::MultiBandSplitter, DSP::BandShaper, DSP::GateModule
- Signal/voice flow: Input → Multiband split → Band shapers → Mixer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg WahWah
- Category: amp & saturation
- Sidechain: Envelope follower modulates cutoff.
- Processing blueprint: Amp head + cabinet simulation with tone stack and mic modeling. Auto/manual wah effect using resonant band-pass filter.
- Key features:
  - Multi-stage pre/power amp saturation
  - Tone stack models (Fender/Marshall/etc.)
  - Cab IR loader with mic blend
  - Effects loop send/return
  - Manual, auto, and MIDI modes
  - Adjustable Q for vowel intensity
  - Drive control to add grit
  - Tempo-synced LFO option
- Core building blocks:
  - DSP::PreampStage, DSP::ToneStack, DSP::PowerAmpStage, DSP::CabIR, DSP::MicBlender, DSP::StateVariableFilter, DSP::EnvelopeFollower, DSP::LFO
- Signal/voice flow: Input → Resonant band-pass → Modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg BitCrusher
- Category: saturation
- Sidechain: N/A
- Processing blueprint: Waveshaping distortion with tone filters and oversampling. Bit-depth and sample-rate reduction effect for lo-fi textures.
- Key features:
  - Selectable transfer curves (tube, transistor, diode)
  - Pre/post EQ tone sculpting
  - Mix control for parallel drive
  - Oversampling to reduce aliasing
  - Bit depth 1–24 bits with dither
  - Sample rate reducer with jitter option
  - Mix control and downsample filter
  - Stereo link/dual mono operation
- Core building blocks:
  - DSP::Oversampler, DSP::WaveShaper, DSP::EQStage, DSP::MixStage, DSP::BitReducer, DSP::SampleRateReducer
- Signal/voice flow: Input → Bit/SR reducer → Anti-alias filter → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
