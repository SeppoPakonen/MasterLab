# Polyphonic Pitch Editor Effect Stub

## Reference
- Inspired by: Melodyne
- Vendor: Celemony
- Source catalog: Melodyne 5 Essential, Assistant, Editor, Studio

## Implementation Plan
### Celemony Melodyne 5
- Category: pitch/time
- Sidechain: N/A
- Processing blueprint: Polyphonic pitch and timing editor based on DNA (Direct Note Access) technology for correction and creative manipulation.
- Key features:
  - DNA engine separating polyphonic material into editable notes
  - Pitch, drift, formant, amplitude, and timing tools with note-level resolution
  - Chord track and scale detection with macros for quantization
  - Multitrack comparison with ARA integration for DAW tightness
- Core building blocks:
  - DSP::DNAAnalyzer, DSP::NoteModel, DSP::PitchDriftEditor, DSP::TimingEditor, DSP::FormantProcessor, DSP::ARAService
- Signal/voice flow: Input → DNA note detection → Note parameter editing → Resynthesis → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
