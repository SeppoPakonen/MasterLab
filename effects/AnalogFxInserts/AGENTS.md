# Analog Fx Inserts Effect Stub

## Reference
- Inspired by: Analog FX Inserts
- Vendor: Arturia
- Source catalog: ARP2600 V Efx, minimoogvEfx

## Summary
Analog modelling of synth-derived processors. Modular routing and high oversampling keep authenticity.

## Implementation Plan
### Arturia ARP 2600 V
- Category: experimental fx
- Sidechain: N/A – operates as self-contained modular effect.
- Processing blueprint: Semi-modular synth-derived effect rack (filters, delays, reverbs, drives). Modular ARP2600-inspired multi-effect with voltage-controlled filters, ring modulation, and spring reverb available as an insert effect.
- Key features:
  - Modulation matrix with envelopes/LFOs
  - Patching options for serial/parallel
  - Tempo syncable sequencers
  - Snapshots/morphing between patches
  - Patchable modulation matrix for audio-rate modulation
  - Dual multimode filters with serial/parallel routing
  - Internal sequencer/LFO for rhythmic sweeps
  - Spring reverb and preamp saturation blocks
- Core building blocks:
  - DSP::ModMatrix, DSP::FilterBank, DSP::DelayReverb, DSP::NonlinearStage, DSP::VCF, DSP::RingMod, DSP::SpringReverb
- Signal/voice flow: Input → Preamp/saturator → Modular patch (filters/modulators) → Reverb → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### Arturia MiniMoog V FX
- Category: experimental fx
- Sidechain: N/A
- Processing blueprint: Semi-modular synth-derived effect rack (filters, delays, reverbs, drives). Effect version of the MiniMoog ladder filter and drive stages with modulation routings for creative filtering.
- Key features:
  - Modulation matrix with envelopes/LFOs
  - Patching options for serial/parallel
  - Tempo syncable sequencers
  - Snapshots/morphing between patches
  - Classic ladder filter with steep resonance
  - Stereo widening using dual filter paths
  - Drive section replicating Moog mixer overload
  - Assignable LFO/envelope followers
- Core building blocks:
  - DSP::ModMatrix, DSP::FilterBank, DSP::DelayReverb, DSP::NonlinearStage, DSP::LadderFilter, DSP::DriveStage, DSP::StereoWidth
- Signal/voice flow: Input → Drive/Mixer emulation → Ladder filter → Modulated stereo spread → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
