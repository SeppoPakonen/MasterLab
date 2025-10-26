# Vocal Live Utilities Effect Stub

## Reference
- Inspired by: Vocal & Live Utilities
- Vendor: Waves
- Source catalog: Primary Source Expander, Sibilance, X-FDBK, Playlist Rider, Greg Wells VoiceCentric, Greg Wells PianoCentric

## Implementation Plan
### Waves Primary Source Expander
- Category: dynamics
- Sidechain: External sidechain for keying optional; designed for live mics.
- Processing blueprint: Level-dependent expander designed to reduce bleed on stage microphones while keeping desired source intact.
- Key features:
  - Intelligent hold and release tuned for speech/singing
  - Frequency-sensitive sidechain filters to avoid cymbal bleed
  - Stage-friendly UI with big threshold meter
  - Option to link multiple channels for stereo sources
- Core building blocks:
  - DSP::SidechainDetector, DSP::ExpanderGate, DSP::FrequencyKeyFilter, DSP::HoldReleaseScheduler
- Signal/voice flow: Input (+ optional sidechain) → Frequency-weighted detector → Gain computer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Sibilance
- Category: dynamics
- Sidechain: External sidechain for split-band detection optional.
- Processing blueprint: De-esser using Organic ReSynthesis to isolate sibilants and reduce them transparently.
- Key features:
  - Organic ReSynthesis separates noise-like sibilants from voiced signal
  - Split and wide modes for narrow vs broadband reduction
  - Look-ahead for zero-latency vs precision operation
  - Realtime graph showing detected sibilant energy
- Core building blocks:
  - DSP::OrganicSeparator, DSP::SibilantDetector, DSP::GainShaper, DSP::LookaheadBuffer, DSP::VisualizationEngine
- Signal/voice flow: Input → Organic separation → Sibilant gain shaping → Recombine → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves X-FDBK
- Category: live tuning
- Sidechain: N/A
- Processing blueprint: Feedback suppressor that analyses PA ringing frequencies and applies surgical filters automatically.
- Key features:
  - Fast ring-out analysis across 1/3-oct bands
  - Adaptive notch filter creation with severity controls
  - Live mode for continuous monitoring
  - Snapshot storage for multiple venues
- Core building blocks:
  - DSP::FeedbackAnalyzer, DSP::NotchFilterBank, DSP::SeverityController, DSP::SnapshotStore
- Signal/voice flow: Input → Feedback analysis sweep → Automatic notch placement → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Playlist Rider
- Category: dynamics
- Sidechain: Internal program-dependent sidechain; no external input.
- Processing blueprint: Auto leveler maintaining consistent loudness across playlists or stems for broadcast.
- Key features:
  - Short/long-term loudness windows with target selection
  - Detector learns segment boundaries to avoid pumping
  - Trim control for manual offsets plus auto makeup
  - Limiter to catch overs during transitions
- Core building blocks:
  - DSP::LoudnessTracker, DSP::BoundaryDetector, DSP::AutoGain, DSP::SafetyLimiter
- Signal/voice flow: Input → Loudness windows → Gain scheduling → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Greg Wells VoiceCentric
- Category: vocal channel
- Sidechain: N/A
- Processing blueprint: Signature vocal chain combining EQ tilt, compression, and reverb/delay under a single intensity knob.
- Key features:
  - Single-knob macro controlling compression, parallel delay, and reverb amounts
  - Focus control to shift EQ tilt for male/female voices
  - Auto gain staging to maintain consistent output
  - Preset variations for genre-specific voicings
- Core building blocks:
  - DSP::MacroController, DSP::EQTilt, DSP::VocalCompressor, DSP::ParallelDelay, DSP::PlateReverb, DSP::AutoGain
- Signal/voice flow: Input → Tone tilt → Dynamics → Parallel FX blend → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Greg Wells PianoCentric
- Category: keys channel
- Sidechain: N/A
- Processing blueprint: Signature piano processing chain delivering EQ, compression, and spatial enhancement from one macro control.
- Key features:
  - Microphone perspective selector altering EQ curves
  - Compression with mid/side option for stereo keys
  - Chorus and imaging enhancer for pop productions
  - Drive stage to add harmonic richness
- Core building blocks:
  - DSP::MacroController, DSP::EQProfiles, DSP::MidSideCompressor, DSP::StereoEnhancer, DSP::HarmonicDrive
- Signal/voice flow: Input → Profile selection → Dynamics/image processing → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
