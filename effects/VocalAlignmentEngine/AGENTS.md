# Vocal Alignment Engine Effect Stub

## Reference
- Inspired by: Alignment
- Vendor: Synchro Arts
- Source catalog: VocAlign Project 5, VocAlign Ultra

## Implementation Plan
### Synchro Arts VocAlign
- Category: alignment
- Sidechain: Requires guide track sidechain (ARA or external input).
- Processing blueprint: Guide-driven alignment utility warping dub vocals to match timing and pitch of reference performances.
- Key features:
  - Energy- and pitch-based feature extraction with adjustable sensitivity
  - Time and pitch warp graph with protected regions
  - Multiple alignment modes (tight, natural, loose)
  - ARA integration plus standalone capture buffer workflow
- Core building blocks:
  - DSP::GuideBuffer, DSP::AlignmentAnalyzer, DSP::WarpMap, DSP::PitchTimeline, DSP::RenderEngine
- Signal/voice flow: Guide + Dub inputs → Feature extraction → Warp map solver → Time/pitch resynthesis → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
