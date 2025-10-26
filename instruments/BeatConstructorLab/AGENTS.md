# Beat Constructor Lab Instrument Stub

## Reference
- Inspired by: Clip/loop-based beat workstations with intelligent suggestions
- Vendor analogues: Ableton Drum Rack + Session View, Native Instruments Maschine, Serato Studio

## Summary
Hybrid clip-based beat workstation combining phrase suggestion, pattern morphing, and performance pads. Extends loop slicing and generation beyond `MomentumLoopStation` with AI-assisted beat construction and Bandmate integration.

## Implementation Plan
### Clip Engine & Phrase Suggestions
- Category: loop workstation / AI assist
- Sidechain: Drag-and-drop audio/MIDI for Bandmate analysis
- Processing blueprint: Multi-track clip engine with AI phrase recommender that adapts loops to key/tempo and user-provided stems.
- Key features:
  - Tracks for drums, bass, chords, melodic loops with per-track FX
  - Harmonic/key detection and auto-translation of loops to project key
  - AI suggestion engine ranking loops based on dropped reference material
  - Elastic audio time-stretch with transient preservation
- Core building blocks:
  - Sample::LoopPool
  - Sample::TimeStretch
  - Sequencer::ClipGrid
  - DSP::AIRecommender
  - DSP::MaskingAnalyzer (for matching references)
- Voice graph: Reference inputs → Analysis → Clip scheduler → Track FX → Master bus
- TODO:
  - Encode track nodes and AI suggestion links in graph visualization
  - Coordinate with FileIO for loop browsing metadata

### Performance Pads & Arrangement
- Category: performance / arranger
- Sidechain: MIDI triggers for live scene launching
- Processing blueprint: Performance pads trigger scenes, pattern morphing, and probability variations. Arrangement timeline records pad triggers.
- Key features:
  - Scene morph controls for smooth transitions between arrangements
  - Probability and density macros to evolve patterns live
  - Drag-and-drop export of generated MIDI/audio clips
  - Automation lanes for FX and mix parameters per scene
- Core building blocks:
  - UI::PerformancePads
  - DSP::SceneMorph
  - Sequencer::ProbabilityEngine
  - DSP::MacroController
  - PluginSDK::GraphVisualization for scene/track mapping
- TODO:
  - Provide interactive visualization of scene transitions and active tracks
  - Hook automation lanes into ParameterSet for snapshot recall
