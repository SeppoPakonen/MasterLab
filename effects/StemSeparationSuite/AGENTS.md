# Stem Separation Suite Effect Stub

## Reference
- Inspired by: Music Rebalance / stem extraction tools
- Vendor analogues: iZotope Music Rebalance, Hit'n'Mix RipX, SpectraLayers Unmix

## Summary
Spectral source separation and remix workstation that extracts vocals, drums, bass, and other stems in real-time for creative remixing or repair. Integrates with Analyzer services for spectral editing and dynamic stem control.

## Implementation Plan
### Source Separation Engine
- Category: spectral processing / remix
- Sidechain: Optional guide stem to bias separation
- Processing blueprint: Hybrid machine-learned mask estimator combined with classic NMF refinement to generate separation masks per stem.
- Key features:
  - Vocal, drums, bass, instrumentation, and user-defined stem slots
  - Confidence-weighted masks with smoothing to reduce artifacts
  - Latency-managed preview and offline HD modes
  - Snapping masks to musical grid for better transient alignment
- Core building blocks:
  - DSP::AISeparator
  - DSP::MaskingAnalyzer
  - DSP::SpectralGate
  - DSP::LatencyBuffer
  - DSP::ConfidenceMeter
- Signal/voice flow: Input → Spectral analysis → Mask estimation → Stem reconstruction mix bus
- TODO:
  - Expose per-stem mask visualization using PluginSDK::GraphVisualization
  - Integrate with AnalyzerTap for heat-map overlays in UI

### Remix & Effects Routing
- Category: creative remixing
- Sidechain: Per-stem internal busses only
- Processing blueprint: Each separated stem feeds dedicated FX racks (EQ, compression, spatialization) with macro controls for quick remix workflows.
- Key features:
  - Parallel FX lanes per stem with shared macro controls
  - Stem-level gain, pan, width, and send routing to global FX
  - Automation-ready freeze/bounce stem export
  - Drag-and-drop stem export to DAW timeline
- Core building blocks:
  - DSP::SignalRouter
  - DSP::FXRack
  - DSP::MacroController
  - DSP::PresetManager
  - UI::RackView integration via PluginSDK graph edges
- Signal/voice flow: Stem buses → Per-stem FX chains → Master mix bus
- TODO:
  - Add routing metadata to visualize stem-to-FX connections
  - Coordinate with FileIO for stem export hooks when implemented
