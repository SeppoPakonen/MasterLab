# Pitch Time Suite Effect Stub

## Reference
- Inspired by: Pitch & Time
- Vendor: Steinberg
- Source catalog: Pitch Conect, Vocoder, Octaver, Mix6to2

## Summary
Focus on legacy Cubase/Nuendo processors. Reuse the same parameter idioms and UI styling to ease migration from the original DAW while modernizing DSP where needed.

## Implementation Plan
### Steinberg Pitch Correct
- Category: pitch/time
- Sidechain: MIDI notes optionally set target pitch.
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Real-time pitch correction similar to older AutoTune EFX with scale selection and retune speed.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - Scale/key presets plus MIDI control
  - Formant preserve switch
  - Dual-mode retune (tight/natural)
  - Vibrato amount and speed
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::PitchDetector, DSP::CorrectionCurve, DSP::FormantPreserver
- Signal/voice flow: Input → Pitch detector → Correction curve → Formant adjust → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Vocoder
- Category: pitch/time
- Sidechain: External carrier via sidechain bus or internal synth.
- Processing blueprint: Multi-band vocoder blending carrier synth with modulator input, with sibilance detection. 16-band vocoder requiring carrier and modulator inputs.
- Key features:
  - 8/16/32 band filter sets
  - Integrated carrier oscillators and noise
  - Unvoiced detector for sibilance passthrough
  - Formant shift and bandwidth controls
  - Band count selection and bandwidth controls
  - Integrated noise carrier for sibilance
  - Formant shift and gender controls
  - Freeze and legato modes
- Core building blocks:
  - DSP::FilterBank, DSP::EnvelopeFollower, DSP::ModulatorRouter, DSP::SynthOsc, DSP::CarrierSynth
- Signal/voice flow: Modulator + Carrier → Analysis filterbank → Envelope followers → Carrier filterbank → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Octaver
- Category: pitch/time
- Sidechain: N/A
- Processing blueprint: Phase vocoder / time-domain pitch engine with formant control and time-stretch. Octave shifter suitable for guitar/bass doubling.
- Key features:
  - Monophonic vs polyphonic modes
  - Formant shifting/preservation
  - Graphical time/pitch editing
  - Low-latency live mode vs offline HD
  - +1/-1 octave blend controls
  - Tracking gate to reduce mistriggers
  - Tone control for synth or guitar voicing
  - Latency compensation for tight timing
- Core building blocks:
  - DSP::PhaseVocoder, DSP::FormantFilter, DSP::TransientPreserver, DSP::TimelineWarp, DSP::PitchShifter, DSP::EnvelopeFollower, DSP::MixStage
- Signal/voice flow: Input → Pitch shifters ±1 octave → Mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Steinberg Mix6to2
- Category: utility
- Sidechain: N/A
- Processing blueprint: Routing, test, and diagnostic tools for session management. Utility mixer folding surround/6-channel stems down to stereo.
- Key features:
  - Routing matrices and gain trims
  - Signal generators (pink, sine, SMPTE)
  - Latency compensation helpers
  - Format conversions (6→2, mono→stereo)
  - Matrix with adjustable coefficients
  - Bass management for LFE fold-down
  - Phase invert per channel
  - Preset alignments (ITU, film, music)
- Core building blocks:
  - DSP::SignalRouter, DSP::Generator, DSP::MatrixMixer, DSP::BassManager, DSP::GainTrim
- Signal/voice flow: 6-channel input → Matrix mix → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
