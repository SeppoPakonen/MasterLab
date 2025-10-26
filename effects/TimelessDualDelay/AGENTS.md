# Timeless Dual Delay Effect Stub

## Reference
- Inspired by: Timeless
- Vendor: FabFilter
- Source catalog: Timeless 2

## Implementation Plan
### FabFilter Timeless 2
- Category: delay
- Sidechain: External sidechain for ducking envelope follower.
- Processing blueprint: Dual delay line with multimode filters, drive, diffusion, and modulation matrix for creative time-based effects.
- Key features:
  - Six-slot modulation matrix with drag-and-drop routing
  - Per-delay-channel multimode filters and saturation
  - Diffusion module and dynamics for tape-like smearing
  - Freeze, reverse, and time-stretch behaviors for creative design
- Core building blocks:
  - DSP::DelayLinePair, DSP::FilterBlock, DSP::DiffusionEngine, DSP::ModulationMatrix, DSP::SaturationStage, DSP::SidechainEnvelope
- Signal/voice flow: Input → Pre-filters/drive → Dual delay lines with feedback insert slots → Output mixer
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
