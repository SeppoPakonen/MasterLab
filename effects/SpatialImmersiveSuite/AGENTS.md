# Spatial Immersive Suite Effect Stub

## Reference
- Inspired by: Spatial & Immersive
- Vendor: Waves
- Source catalog: Abbey Road Studio 3, Nx Virtual Mix Room over Headphones, Space Rider, Brauer Motion, B360 Ambisonics Encoder, DTS Neural Surround UpMix, DTS Neural Surround DownMix, DTS Neural Mono2Stereo, Dorrough Surround

## Implementation Plan
### Waves Abbey Road Studio 3
- Category: monitoring
- Sidechain: N/A
- Processing blueprint: Binaural room emulation modeling Abbey Road Studio Three control room for headphone mixing.
- Key features:
  - Head tracking via supported hardware with personalized HRTF
  - Multiple monitor speaker models and positions
  - Room ambience and speaker drive modeling
  - Virtual mono/stereo/5.1 monitoring modes
- Core building blocks:
  - DSP::BinauralRenderer, DSP::RoomModel, DSP::HeadTracker, DSP::SpeakerArray
- Signal/voice flow: Input → Virtual speaker array → HRTF renderer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Nx Virtual Mix Room
- Category: monitoring
- Sidechain: N/A
- Processing blueprint: General-purpose virtual control room with head tracking and personalized HRTFs.
- Key features:
  - Individual head measurements for personalization
  - Room selection with adjustable ambience
  - External head-tracking hardware integration
  - Fold-down options for surround formats
- Core building blocks:
  - DSP::BinauralRenderer, DSP::HeadModel, DSP::RoomAmbience, DSP::FoldDownMatrix
- Signal/voice flow: Input → Virtual speaker simulation → Binaural rendering → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Space Rider
- Category: spatial fx
- Sidechain: N/A
- Processing blueprint: Spatial effects suite combining delay, reverb, and modulation with orb-style trajectory control.
- Key features:
  - Multi-axis orbital panner modulating delay taps
  - Three effect engines (delay, reverb, tremolo) with sync
  - Dynamic Rider module for auto-ducking of FX tails
  - Macro XY pad controlling orbit speed and size
- Core building blocks:
  - DSP::OrbitalPanner, DSP::DelayEngine, DSP::ReverbEngine, DSP::Tremolo, DSP::DynamicRider, UI::XYPAD
- Signal/voice flow: Input → Orbital modulation → FX engines → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Brauer Motion
- Category: spatial fx
- Sidechain: External sidechain for rhythm trigger.
- Processing blueprint: Auto-panning tool creating 3D circular motion around the listener, derived from Michael Brauer's workflows.
- Key features:
  - Dual panner paths (inside/outside) with trajectory presets
  - Triggerable by BPM, manual tap, or sidechain rhythm
  - Depth and width controls for immersive movement
  - Built-in dynamics to duck dry signal when motion peaks
- Core building blocks:
  - DSP::MotionPanner, DSP::TrajectoryEngine, DSP::SidechainTrigger, DSP::DepthController, DSP::DynamicsDucker
- Signal/voice flow: Input → Motion generator (with sidechain) → Panning matrix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves B360 Ambisonics Encoder
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Encoder converting mono/stereo/surround stems into Ambisonics B-format for 360-degree delivery.
- Key features:
  - Multiple input topologies (mono, stereo, 5.1, 7.1)
  - Height and rotation controls for 3D placement
  - Output level monitoring with normalization
  - Integration hooks for Facebook 360/YouTube VR export
- Core building blocks:
  - DSP::AmbisonicsEncoder, DSP::RotationMatrix, DSP::NormalizationMeter, DSP::MultiChannelRouter
- Signal/voice flow: Input stems → Ambisonics encoder → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves DTS Neural Surround UpMix
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Upmix engine generating 4.0/5.1/7.1 mixes from stereo with dialog localization control.
- Key features:
  - Dialog clarity controls for center extraction
  - Ambient extraction for surrounds with decorrelation
  - Low-frequency management with LFE synthesis
  - Preset management for film/broadcast standards
- Core building blocks:
  - DSP::UpmixEngine, DSP::DialogExtractor, DSP::AmbientSynth, DSP::LFESynth, DSP::PresetManager
- Signal/voice flow: Stereo input → Upmix engine → Surround output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves DTS Neural Surround DownMix
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Downmix tool translating surround mixes to stereo while preserving intent.
- Key features:
  - Preserves dialog localization via center weighting
  - Adjustable surround and LFE contribution
  - ITU-compliant loudness preservation
  - Phase-safe folding with clip prevention
- Core building blocks:
  - DSP::DownmixMatrix, DSP::DialogPreserver, DSP::LFERouter, DSP::ClipGuard
- Signal/voice flow: Surround input → Downmix matrix → Stereo output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves DTS Neural Mono2Stereo
- Category: spatial
- Sidechain: N/A
- Processing blueprint: Mono-to-stereo converter creating width via psychoacoustic cues.
- Key features:
  - Dialog clarity slider for center focus
  - Ambience synthesis with decorrelated delays
  - Anti-phase protection for broadcast compatibility
  - Simple interface for live operations
- Core building blocks:
  - DSP::MonoStereoConverter, DSP::PsychoSpread, DSP::PhaseGuard, DSP::AmbienceGenerator
- Signal/voice flow: Mono input → Psychoacoustic spread → Stereo output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Dorrough Surround
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Surround-capable metering suite based on Dorrough hardware for post-production loudness compliance.
- Key features:
  - Simultaneous VU and peak indication per channel
  - Support for 5.0, 5.1, and 7.1 layouts
  - Reference calibration with trim recall
  - Logging hooks for broadcast documentation
- Core building blocks:
  - DSP::SurroundMeterBridge, DSP::PeakHold, DSP::CalibrationManager, DSP::LoggingBackend
- Signal/voice flow: Input bus → Meter aggregation → UI/logging
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
