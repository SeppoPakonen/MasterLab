# Pitch Vocal Collection Effect Stub

## Reference
- Inspired by: Pitch & Vocal
- Vendor: Waves
- Source catalog: Morphoder Mono, Morphoder Mono/Stereo, Morphoder Stereo, UltraPitch 3 Voices Mono, UltraPitch 6 Veices Mono, UltraPitch 6 Voices Mono/Stereo, UltraPitch Shift Mono, UltraPitch Shift Mono/Stereo, UtraPitch 3 Voices Mono/Stereo, WavesTune Lite Mono, WavesTune Lite Stereo, WavesTune Mono, WavesTune Stereo, SoundShifter Graphic Mono, SoundShifter Graphic Stereo, SoundShifter Parametc Mono, SoundShifter Parametic Stereo, SoundShifter Pitch Mono, SoundShifter Pitch Stereo, Reel ADT Mono, Reel ADT Mono/Stereo, Reel ADT Stereo, Reel ADT2V Mono/Stereo, Reel ADT2V Stereo

## Summary
Modelled after commercial Waves plug-ins. Maintain parity in routing, channel counts, and control ranges so presets translate. Emphasize shared components (analog drive, macro controllers) to minimise duplicate code.

## Implementation Plan
### Waves Morphoder
- Category: pitch/time
- Sidechain: External modulator input; internal or external carrier.
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Vocoder with internal carrier synth and MIDI control.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - 10-band vocoder with morphing oscillator
  - Built-in synth with multiple waveforms and unvoiced detector
  - Formant shift and carrier filter bandwidth control
  - Sidechain compression to keep speech intelligible
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::VocoderBank, DSP::CarrierSynth, DSP::EnvelopeFollower
- Signal/voice flow: Modulator + Carrier → Band analysis → Carrier filter bank → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves UltraPitch
- Category: channel coloration
- Sidechain: N/A
- Processing blueprint: Console/processor emulation combining static EQ curves, saturation, and optional dynamics. Multi-voice pitch shifter supporting 3, 6, and shifting modes.
- Key features:
  - Multiple modeled units/transformers
  - Drive/noise toggles with calibration
  - Phase aligned parallel path for blend
  - Module bypass for EQ/dynamics segments
  - Formant correct and choir modes
  - Detune per voice and pan spread
  - Delay per voice for ADT effects
  - MIDI control for live harmonies
- Core building blocks:
  - DSP::NonlinearStage, DSP::StaticEQ, DSP::DynamicModule, DSP::NoiseModel, DSP::Oversampler, DSP::PitchShifter, DSP::DelayLine, DSP::FormantPreserver
- Signal/voice flow: Input → Multi-voice pitch engine → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves WavesTune
- Category: pitch/time
- Sidechain: MIDI control for target notes.
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. High-precision pitch correction with graphical editing similar to Auto-Tune.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - Note detection with timeline view and pencil editing
  - Formant correction, vibrato, and drift controls
  - ReWire-style ReWire-like note send to host
  - Real-time and offline modes
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::PitchDetector, DSP::GraphEditor, DSP::CorrectionEngine
- Signal/voice flow: Input → Pitch analysis → User-edited correction curve → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves SoundShifter
- Category: pitch/time
- Sidechain: N/A
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Versatile pitch/time shifting toolkit (Graphic, Parametric, Pitch modes).
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - Phase vocoder with transient preservation
  - Graphic timeline for time warping
  - Formant control for natural results
  - Sync with host tempo automation
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::TransientProtector, DSP::TimeWarpEngine
- Signal/voice flow: Input → FFT analysis → Warp/pitch process → Resynthesis → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Reel ADT
- Category: pitch/time
- Sidechain: N/A
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Authentic Abbey Road artificial double tracking with dual tape machines.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - Dual virtual tape decks with wow/flutter
  - Manual/Auto speed controls mimic reel-to-reel
  - Phase and pan per deck for stereo width
  - Drive stage emulating tape saturation
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::TapeADT, DSP::WowFlutter, DSP::PhaseAligner
- Signal/voice flow: Input → Dual tape delay paths → Saturation → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
