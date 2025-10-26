# Songwriter Instrument Pack Instrument Stub

## Reference
- Inspired by: Songwriting Instruments
- Vendor: Toontrack
- Source catalog: EZkeys 2, EZdrummer 2

## Implementation Plan
### Toontrack EZkeys 2
- Category: songwriting piano
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Songwriting assistant pairing sample-based piano with chord detection, MIDI patterns, and arranger tools.
- Key features:
  - Chord tracker suggests substitutions and voice-leading
  - Bandmate audio/MIDI analysis to generate accompaniment patterns
  - Sampled piano engine with sympathetic resonance and pedal noise
  - Song track with sections, humanization, and DAW drag-and-drop
- Core building blocks:
  - MIDI::ChordLibrary, MIDI::SongTrack, Arranger::StylePlayer, Sample::PianoEngine, Sample::PedalModel, FX::InsertRack
- Signal/voice flow: Chord progression → Pattern generator → Piano engine (velocity layers + resonance) → FX rack → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Toontrack EZdrummer 2
- Category: drum instrument
- Sidechain: MIDI only; no audio sidechain.
- Processing blueprint: Multi-mic drum sampler with groove library, humanization, and built-in mixer.
- Key features:
  - Articulation system with round-robin and velocity morphing
  - Tap-to-Find and Bandmate groove suggestion tools
  - Integrated mixer with bleed, overhead, and room controls
  - E-drum mapping and humanization for realistic playback
- Core building blocks:
  - Sample::DrumCell, Sample::RoundRobin, Humanize::TimingRandomizer, Sequencer::GroovePlayer, Mixer::DrumBus, FX::InsertRack
- Signal/voice flow: MIDI hit → Articulation resolver → Sample playback (direct/overhead/room) → Internal mixer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
