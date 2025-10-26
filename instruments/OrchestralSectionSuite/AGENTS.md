# Orchestral Section Suite Instrument Stub

## Reference
- Inspired by: Ensemble orchestral libraries with articulation management
- Vendor analogues: Spitfire Symphonic Orchestra, EastWest Hollywood Orchestra, Orchestral Tools Metropolis Ark

## Summary
Sample-based orchestral instrument delivering section articulations (strings, brass, woodwinds, choir) with legato scripting, dynamic layering, and articulation switching. Integrates with articulation maps and UI graph showing signal/cv flow.

## Implementation Plan
### Sample & Articulation Engine
- Category: orchestral sampling
- Sidechain: MIDI CCs for dynamics/vibrato
- Processing blueprint: Multi-mic sample playback with velocity/dynamic crossfades, legato transition samples, and articulation switching via keyswitch or UI.
- Key features:
  - Sections: strings high/low, brass, woodwinds, choir with multiple articulations
  - Dynamic crossfade between pp/p/mf/f/ff using mod wheel (CC1)
  - Legato engine with interval detection and true transition samples
  - Round-robin and humanization for repeated notes
- Core building blocks:
  - Sample::StreamEngine
  - Sample::ArticulationEngine
  - Sample::MicMixer
  - Sample::RoundRobin
  - Synth::VoiceManager
- Voice graph: Note → Articulation resolver → Sample layer selection → Mic mix → Section bus → Output
- TODO:
  - Populate GraphVisualization with section nodes, mic busses, and articulation routing
  - Define articulation map schema for UI integration

### Performance Tools & Mixing
- Category: performance utilities
- Sidechain: Optional sidechain to duck sections during dialogue
- Processing blueprint: Section mixer with convolution halls, compressor, EQ, and adaptive reverb send. Includes articulation editor and expression maps.
- Key features:
  - Section mixer with mic positions (Close, Decca, Outriggers, Room)
  - Auto-divisi and voice allocation for intelligent chord distribution
  - Articulation editor for user-defined key/CC mapping
  - Score view showing active articulations per section
- Core building blocks:
  - Mixer::SectionBus
  - DSP::ConvolutionEngine
  - DSP::Compressor
  - DSP::ParametricEQ
  - UI::MacroSurface for expression macros
- TODO:
  - Encode mixer nodes/sends in graph for visual feedback
  - Hook articulation editor to PluginSDK parameter set for recall
