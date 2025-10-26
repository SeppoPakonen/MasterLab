# Studio Instrument Suite Instrument Stub

## Reference
- Inspired by: Instrument Suite
- Vendor: Waves
- Source catalog: Grand Rhapsody Piano, Bass Fingers, Element 2.0 Virtual Analog Synth, TRACT System Calibration, Codex Wavetable Synth, Electric 88 Piano, Flow Motion FM Synth, Bass Slapper, Sub Align, StudioVerse Instruments

## Implementation Plan
### Waves Grand Rhapsody Piano
- Category: sampled piano
- Sidechain: MIDI pedal/aftertouch; no audio sidechain.
- Processing blueprint: 8-mic sampled Fazioli concert grand with pedal resonance and studio FX chain.
- Key features:
  - Six stereo mic pairs with mix/phase controls
  - Sympathetic resonance and pedal noise modeling
  - Velocity curve designer and dynamic response control
  - Studio rack with EQ, compression, delay, and reverb
- Core building blocks:
  - Sample::StreamEngine, Sample::MicMixer, Sample::PedalModel, UI::MacroSurface, FX::InsertRack
- Signal/voice flow: Note → Velocity mapping → Mic-layer streaming → Resonance/pedal model → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Bass Fingers
- Category: sampled bass
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Fingerstyle electric bass instrument with articulations, slides, and amp modeling.
- Key features:
  - Articulation engine covering sustains, mutes, slides, and harmonics
  - Round-robin and legato scripting for realistic lines
  - Built-in amp, cabinet, and FX pedals with DI mix
  - Key-switch and velocity switching for performance control
- Core building blocks:
  - Sample::ArticulationEngine, Sample::RoundRobin, Sequencer::LegatoHandler, FX::AmpSim, UI::KeySwitchPalette
- Signal/voice flow: MIDI note/keyswitch → Articulation resolver → Sample playback → Amp/cab FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Element 2.0 Virtual Analog Synth
- Category: virtual analog
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Two-oscillator subtractive synth with sub/noise sources, flexible mod matrix, and arpeggiator.
- Key features:
  - Dual oscillators plus sub/noise with drift and sync
  - Mod matrix with four sources and eight destinations
  - Step arpeggiator with swing, gate, and chord modes
  - Onboard FX (distortion, chorus, delay, reverb)
- Core building blocks:
  - Synth::OscillatorVA, Synth::SubOsc, Synth::ModMatrix, Synth::FilterCascade, Sequencer::ArpSequencer, FX::InsertRack
- Signal/voice flow: Note → Oscillators (A/B + sub/noise) → Filter → Amp → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves TRACT System Calibration
- Category: calibration
- Sidechain: Measurement mic input and playback reference.
- Processing blueprint: Live sound calibration tool capturing venue response and deploying corrective FIR/IIR filters.
- Key features:
  - Measurement capture using swept sine or pink noise
  - Target curve library with auto-fitting algorithms
  - FIR and IIR filter designer with phase linearization
  - Integration hooks for Smaart/StudioRack workflows
- Core building blocks:
  - Calibration::MeasurementAnalyzer, DSP::FIRDesigner, DSP::IIRDesigner, DSP::TargetCurve, UI::MeasurementWorkflow
- Signal/voice flow: Measurement playback → Response capture → Filter solver → Correction filters applied to output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Codex Wavetable Synth
- Category: wavetable synth
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Dual wavetable synth with morphing spectra, formant control, and sequencing macros.
- Key features:
  - Two wavetable oscillators with spectral manipulations (formant, sync, stretch)
  - Voice section with per-voice drive and unison
  - Step sequencer and arpeggiator linked to macros
  - FX rack (chorus, delay, reverb, compression)
- Core building blocks:
  - Synth::WavetableOsc, Synth::FormantShaper, Synth::ModMatrix, Sequencer::StepSequencer, FX::InsertRack
- Signal/voice flow: Note → Wavetable oscillators → Filter/shaper → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Electric 88 Piano
- Category: sampled electric piano
- Sidechain: MIDI pedal/aftertouch; no audio sidechain.
- Processing blueprint: Sampled Fender Rhodes with amp/cab options and studio FX.
- Key features:
  - Multi-layer samples covering velocity, release, and pedal noise
  - Built-in amp/cab models with mic selections
  - Modulation FX (chorus, phaser, tremolo) and reverb
  - Velocity curve editor for tailoring feel
- Core building blocks:
  - Sample::StreamEngine, Sample::MechanicalNoise, FX::AmpCab, FX::ModulationSuite, UI::MacroSurface
- Signal/voice flow: Note → Velocity mapping → Sample layers (tine, release, pedal) → Amp/cab + FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Flow Motion FM Synth
- Category: FM/VA hybrid
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Four-operator FM synth presented with nodal routing plus subtractive filter and macro controls.
- Key features:
  - Node-based UI for connecting FM operators and feedback loops
  - Hybrid subtractive filter with drive and sequencing
  - Motion page featuring 16-step sequencer and LFOs
  - Macro pads for morphing complex modulation scenes
- Core building blocks:
  - Synth::FMOperator, UI::NodeGraph, Synth::ModMatrix, Sequencer::MotionSequencer, FX::InsertRack
- Signal/voice flow: Note → Operator matrix → Combined output → Filter/drive → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Bass Slapper
- Category: sampled bass
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Slap-bass focused instrument with pops, thumps, slides, and ghost notes plus FX.
- Key features:
  - Detailed articulation capture (thumb, pop, slap, ghost, hammer-ons)
  - String/fret noise generator with timing control
  - Built-in amp, cab, and stomp FX tailor-made for slap bass
  - Sequencer for auto articulations and riff playback
- Core building blocks:
  - Sample::ArticulationEngine, Sample::SlideEngine, Sequencer::PatternPlayer, FX::AmpSim, UI::StrokeVisualizer
- Signal/voice flow: MIDI note/keyswitch → Articulation resolver → Sample playback → Amp/cab FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves Sub Align
- Category: calibration
- Sidechain: Measurement mic input for phase matching.
- Processing blueprint: Alignment utility calculating delay/polarity corrections between subwoofers and main PA/FOH speakers.
- Key features:
  - Phase and magnitude analysis of sub vs top responses
  - Automatic delay/polarity solver with manual overrides
  - Visualization of phase wrap and summation
  - Snapshot storage for venue presets
- Core building blocks:
  - Calibration::PhaseAnalyzer, Calibration::DelaySolver, DSP::FilterDesigner, UI::AlignmentGraph
- Signal/voice flow: Measurement capture → Phase/delay solver → Apply delay/EQ filters → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Waves StudioVerse Instruments
- Category: instrument host
- Sidechain: Depends on hosted chain; supports MIDI and audio routing.
- Processing blueprint: Hosted instrument chains curated from StudioVerse with macro mapping and AI-powered search.
- Key features:
  - Chain host runs Waves/third-party instruments via StudioRack
  - AI tagging and search for style-based instrument presets
  - Macro surface exposing up to eight performance controls
  - Session recall with versioning and collaboration metadata
- Core building blocks:
  - DSP::RackHost, DSP::ChainNode, UI::PresetBrowser, Automation::MacroController, NET::CollaborationService
- Signal/voice flow: MIDI input → Hosted instrument chain (StudioRack) → Optional FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
