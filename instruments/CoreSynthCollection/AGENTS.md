# Core Synth Collection Instrument Stub

## Reference
- Inspired by: Core Synths
- Vendor: Native Instruments
- Source catalog: Massive, Massive X inspirations, Kontakt 7, Battery 4, Reaktor 6

## Implementation Plan
### Native Instruments Massive
- Category: wavetable synth
- Sidechain: MIDI/MPE; no audio sidechain.
- Processing blueprint: Three-oscillator wavetable synth with flexible routing, macro controls, and performance sequencers.
- Key features:
  - 170+ wavetables with morphing and modulation per oscillator
  - Serial/parallel dual-filter topology with insert effect slots
  - Modulation sequencers (Stepper, Performer) tied to macros
  - Extensive FX rack with routing to outputs or feedback loops
- Core building blocks:
  - Synth::WavetableOsc, Synth::NoiseOsc, Synth::FilterDual, Synth::ModMatrix, Sequencer::Performer, FX::InsertRack
- Signal/voice flow: Note on → Wavetable oscillators (3) + noise → Filter routing → Insert FX → Master FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Native Instruments Kontakt
- Category: sampler
- Sidechain: MIDI and script events; no audio sidechain.
- Processing blueprint: Deep sampling platform with disk streaming (DFD), scripting, and multi-bus mixing.
- Key features:
  - Zone/Group architecture with velocity, key, and round-robin rules
  - KSP scripting engine for custom UI and articulation logic
  - DFD streaming optimized for large libraries
  - Per-group and bus FX plus send routing
- Core building blocks:
  - Sample::DFDStream, Sample::Zone, Script::Engine, Mixer::Bus, FX::InsertRack, Automation::EventRouter
- Signal/voice flow: Note on → Zone selection (velocity/key/round robin) → Sample streaming → Group modulators (env/LFO/scripts) → Bus FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Native Instruments Battery
- Category: drum sampler
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: 4×16 pad drum sampler with layering, cell FX, and flexible routing.
- Key features:
  - Up to four layers per cell with velocity/fade switching
  - Cell-level FX (compressor, transient, saturation) and sends
  - Per-cell articulation rules and humanization
  - Drag-and-drop sample and MIDI mapping
- Core building blocks:
  - Sample::CellMatrix, Sample::RoundRobin, Mixer::CellBus, FX::DrumRack, Sequencer::StepAutomation
- Signal/voice flow: Trigger → Cell layer selection → Amp/filter envelopes → Cell FX → Bus FX → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Native Instruments Reaktor
- Category: modular environment
- Sidechain: Depends on ensemble; supports audio and MIDI IO.
- Processing blueprint: Modular synthesis and DSP construction kit with Blocks, Core, and ensembles.
- Key features:
  - Graph-based Blocks environment with patchable modules
  - Core/Primary layers for custom DSP authoring
  - Macro controls and snapshots per ensemble
  - Extensive library of instrument and effect ensembles
- Core building blocks:
  - Modular::GraphCompiler, Modular::Block, DSP::CoreCell, UI::ModuleBrowser, Automation::MacroMapper
- Signal/voice flow: Event/audio inputs → Compiled module graph → DSP evaluation → Outputs
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
