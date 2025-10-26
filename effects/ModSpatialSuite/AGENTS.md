# Mod Spatial Suite Effect Stub

## Reference
- Inspired by: Modulation & Spatial
- Vendor: Steinberg
- Source catalog: AutoPan, Chorus, Chorus2, StudioChorus, Flanger, Phaser, Symphonic, Vibrato, Tremolo, Rotary, Rotary, StereoEnhancer, StereoExpander, Chopper, ModMachine, Cloner

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg AutoPan
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. Stereo autopanner with tempo sync and offset controls.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Sync to note values or Hz
  - Adjustable pan law to maintain loudness
  - Phase offset for dual-LFO modes
  - Envelope follower for dynamic pan
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::Panner, DSP::LFO, DSP::EnvelopeFollower
- Signal/voice flow: Input → Auto-pan modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Chorus
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Classic 2-voice chorus for widening synths and guitars.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Rate/depth with separate delay time
  - Stereo phase offset
  - Feedback for flanger-like tones
  - Tempo sync option
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::ChorusEngine
- Signal/voice flow: Input → Modulated delay voices → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg StudioChorus
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Enhanced chorus with up to 4 voices and ensemble spread.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Voice count selection (2/4)
  - Voice detune and spread parameters
  - Integrated high cut for sheen control
  - Wet/dry mix with stereo width
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::EnsembleEngine
- Signal/voice flow: Input → Multi-voice delay network → Width control → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Flanger
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Traditional flanger with feedback and polarity options.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Manual delay bias control
  - Positive/negative feedback
  - Tempo sync LFO
  - Stereo phase inversion
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::FlangerStage, DSP::FeedbackStage
- Signal/voice flow: Input → Modulated short delay → Feedback → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Phaser
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). 6/12-stage phaser with feedback and centre frequency controls.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Selectable number of all-pass stages
  - Feedback resonance control
  - Envelope follower for auto-wah style sweeps
  - Tempo sync rate
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::PhaserCascade, DSP::EnvelopeFollower
- Signal/voice flow: Input → All-pass cascade → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Symphonic Ensemble
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Triple chorus/delay ensemble inspired by Roland Dimension D.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Three fixed modulation voices with depth presets
  - Stereo widening without heavy phase issues
  - Subtle automatic gain compensation
  - Great on strings/pads
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::EnsembleEngine, DSP::ModulationMatrix
- Signal/voice flow: Input → Triple ensemble voices → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Vibrato
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Pitch vibrato effect with depth and speed controls.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Waveform selection (sine/triangle)
  - Delay compensation to maintain phase
  - Stereo split vibrato mode
  - Rise time for natural start
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::PitchModulator, DSP::DelayCompensator
- Signal/voice flow: Input → Pitch modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Tremolo
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Amplitude tremolo with stereo phase offset.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Waveform selection including square
  - Smoothing control for choppy vs smooth
  - Pan/tremolo dual mode
  - Tempo sync subdivisions
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::TremoloLFO, DSP::StereoPanner
- Signal/voice flow: Input → Amplitude modulation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Rotary
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Rotary speaker simulator with horn/drum balance.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Independent horn/drum speeds with acceleration
  - Mic distance and angle control
  - Cabinet EQ for tonal shaping
  - Overdrive stage before cabinet
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::LeslieModel, DSP::DynamicsStage, DSP::MicModel
- Signal/voice flow: Input → Overdrive → Horn/drum rotation model → Mic mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Stereo Imaging
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Stereo/surround imaging, vector panning, and phase alignment utilities. StereoEnhancer/Expander pair for width and phase control.
- Key features:
  - Azimuth/elevation panning with distance cues
  - Phase correlation and delay alignment
  - Mid/Side shuffling and stereo width control
  - Surround fold-down / bass management
  - Mid/Side gain and EQ controls
  - Stereo field visual meter
  - Phase invert per channel
  - Safe bass option to keep lows mono
- Core building blocks:
  - DSP::SpatialMatrix, DSP::VectorPanner, DSP::PhaseAnalyzer, DSP::BassManager, DSP::MSMatrix, DSP::StereoWidener, DSP::Visualizer
- Signal/voice flow: Input → MS matrix → Width/tilt adjustments → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Chopper
- Category: modulation
- Sidechain: Pattern-driven; optional MIDI sync.
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Rhythmic audio gate/chopper with tempo-synced patterns.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Step sequencer for gate patterns
  - Swing and smoothing controls
  - Random step probability
  - MIDI trigger mode
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::StepSequencer, DSP::GateStage, DSP::SmoothingFilter
- Signal/voice flow: Input → Step sequencer envelope → Gain stage → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg ModMachine
- Category: delay
- Sidechain: N/A
- Processing blueprint: Tempo-syncable delay line with modulation, feedback, and filtering. Multi-effect combining modulation, delay, and filter blocks in one interface.
- Key features:
  - Host tempo sync with note divisions
  - Multi-tap routing (SuperTap, ModDelay)
  - Per-tap filtering and feedback
  - Ping-pong and spatialization modes
  - Chainable blocks (delay, filter, overdrive)
  - LFO with complex waves and envelope follower
  - Tempo sync and retrigger
  - Preset morphing via macros
- Core building blocks:
  - DSP::DelayLine, DSP::TapScheduler, DSP::FeedbackMatrix, DSP::FilterStage, DSP::ModularBlockHost, DSP::FilterBlock, DSP::DriveStage
- Signal/voice flow: Input → User-defined block chain → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Cloner
- Category: modulation
- Sidechain: N/A
- Processing blueprint: Time/pitch modulation using LFO or envelope followers (chorus, flanger, autopan, etc.). Voice doubler creating multi-voice unison effects.
- Key features:
  - Sync to tempo or free rate
  - Stereo phase offsets and feedback paths
  - Envelope follower for dynamic modulation
  - Blend/mix and width controls
  - Up to four cloned voices
  - Random pitch/timing deviations
  - Formant preserve option for vocals
  - Stereo spread control
- Core building blocks:
  - DSP::DelayLine, DSP::AllpassCascade, DSP::LFO, DSP::StereoWidener, DSP::VoiceCloner, DSP::PitchModulator, DSP::DelaySpread
- Signal/voice flow: Input → Voice duplication → Detune/delay per voice → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
