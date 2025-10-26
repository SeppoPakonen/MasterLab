# Analysis Utility Suite Effect Stub

## Reference
- Inspired by: Analysis & Utility
- Vendor: Steinberg
- Source catalog: MultiScope, SMPTEGenerator, TestGenerater, Tuner

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg MultiScope
- Category: analysis
- Sidechain: N/A
- Processing blueprint: Real-time metering and analysis for loudness, spectrum, and phase. MultiScope offers oscilloscope, spectrum, and phase analysis for troubleshooting.
- Key features:
  - EBU/ITU loudness standards
  - True peak detection with oversampling
  - Spectral and vector scopes
  - Logging/export of measurement sessions
  - Time-domain oscilloscope with trigger
  - FFT spectrum with averaging
  - Goniometer vector scope
  - Snapshot/hold for comparisons
- Core building blocks:
  - DSP::LoudnessMeter, DSP::TruePeakDetector, DSP::SpectrumAnalyzer, DSP::LoggingBackend, DSP::ScopeAnalyzer, DSP::FFTAnalyzer, DSP::Goniometer, DSP::HistoryBuffer
- Signal/voice flow: Input → Parallel analyzer modules → UI
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg SMPTE Generator
- Category: utility
- Sidechain: N/A
- Processing blueprint: Routing, test, and diagnostic tools for session management. Generates SMPTE/LTC timecode audio for external sync.
- Key features:
  - Routing matrices and gain trims
  - Signal generators (pink, sine, SMPTE)
  - Latency compensation helpers
  - Format conversions (6→2, mono→stereo)
  - Frame rate selection (23.976–30 fps)
  - Drop/non-drop settings
  - Level trim to match device sensitivity
  - Start time offset controls
- Core building blocks:
  - DSP::SignalRouter, DSP::Generator, DSP::MatrixMixer, DSP::LTCEncoder, DSP::TimecodeFormatter
- Signal/voice flow: Timecode settings → LTC encoder → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg TestGenerator
- Category: utility
- Sidechain: N/A
- Processing blueprint: Routing, test, and diagnostic tools for session management. Signal generator producing sine, pink/white noise, sweep, and DC.
- Key features:
  - Routing matrices and gain trims
  - Signal generators (pink, sine, SMPTE)
  - Latency compensation helpers
  - Format conversions (6→2, mono→stereo)
  - Sweep (log/linear) for calibration
  - Channel-independent level and phase
  - Pink noise with weighting filters
  - Automation for test sequences
- Core building blocks:
  - DSP::SignalRouter, DSP::Generator, DSP::MatrixMixer, DSP::SignalGenerator, DSP::SweepEngine, DSP::NoiseGenerator
- Signal/voice flow: Generator core → Output routing
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Tuner
- Category: pitch/time
- Sidechain: N/A
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Chromatic tuner for guitars and orchestral instruments.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - Needle + strobe display
  - Reference pitch and temperament options
  - Ultra fast polyphonic detection mode
  - Mute output option for live tuning
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::PitchDetector, DSP::TuningDisplay, DSP::MuteControl
- Signal/voice flow: Input → Pitch detector → Display/mute → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
