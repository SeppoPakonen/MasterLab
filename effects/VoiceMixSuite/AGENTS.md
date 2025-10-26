# Voice Mix Suite Effect Stub

## Reference
- Inspired by: Voice & Mix Suite
- Vendor: iZotope
- Source catalog: Dialogue Match, Nectar 4 Advanced, Nectar 4 Elements, Neutron 4, Neutron Elements, Velvet (Exponential Audio), R4 Velvet, Ozone 11 Advanced

## Implementation Plan
### iZotope Dialogue Match
- Category: dialog
- Sidechain: N/A – uses captured reference profiles rather than live sidechain.
- Processing blueprint: Profile-matching processor transferring EQ, reverb, and ambience from a reference clip to production dialogue.
- Key features:
  - Machine-learned early/late reverb separation with convolution synthesis
  - Multi-band EQ matching with smoothing and outlier rejection
  - Ambience re-synthesis with noise floor interpolation
  - Profile library with scene metadata, tagging, and recall
- Core building blocks:
  - DSP::ProfileCapture, DSP::MatchEQ, DSP::ReverbProfiler, DSP::AmbienceSynthesizer, DSP::ProfileLibrary
- Signal/voice flow: Reference analysis → Profile diff computation → EQ/Reverb/ambience application → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### iZotope Nectar 4 Advanced
- Category: vocal channel
- Sidechain: External sidechain for compressor/gate modules and MIDI harmony triggering.
- Processing blueprint: Modular vocal channel strip with AI-assisted setup covering pitch correction, dynamics, EQ, harmonies, and spatial effects.
- Key features:
  - Vocal Assistant proposes module ordering and target curves
  - Dynamic EQ with Unmasking vs music-bed sidechain
  - Dual-stage compression plus limiter and de-essing
  - Harmony, Backer, and Auto-Level modules for stacked vocals
- Core building blocks:
  - DSP::VocalAssistant, DSP::ModuleRouter, DSP::DynamicEQ, DSP::MultiStageCompressor, DSP::HarmonyGenerator, DSP::AutoLeveler
- Signal/voice flow: Input → Assistant analysis → Module graph (Pitch → EQ → Dynamics → FX) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### iZotope Neutron
- Category: mixing suite
- Sidechain: External sidechain for Unmasking and compressor/expander modules.
- Processing blueprint: AI-guided mix channel strip providing EQ, dynamics, saturation, transient shaping, and masking analysis.
- Key features:
  - Mix Assistant with instrument-aware target curves
  - Sculptor spectral shaper with classifier-driven profiles
  - Masking Meter follows sidechain source to carve space
  - Per-module multiband splits with zero-latency or linear-phase modes
- Core building blocks:
  - DSP::MixAssistant, DSP::SculptorShaper, DSP::MaskingMeter, DSP::DynamicEQ, DSP::MultiBandCompressor, DSP::TransientShaper, DSP::ModuleGraph
- Signal/voice flow: Input → Assistant and classifier → Module processing (EQ/Sculptor/Dynamics/Saturation) → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### iZotope Velvet Reverb
- Category: reverb
- Sidechain: N/A
- Processing blueprint: Lush algorithmic reverb revolving around modulated diffusion networks derived from Exponential Audio Velvet algorithms.
- Key features:
  - Multi-tap early reflection designer with diffusion control
  - Modulated all-pass loop for smooth long tails
  - Frequency-dependent damping with tempo-sync pre-delay
  - Freeze and infinite sustain for ambient design
- Core building blocks:
  - DSP::VelvetReverbCore, DSP::EarlyReflectionDesigner, DSP::ModulatedAllpass, DSP::DampingFilters, DSP::TailFreezer
- Signal/voice flow: Input → Pre-EQ → Early reflection builder → Modulated tail loop → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint

### iZotope Ozone Advanced 11
- Category: mastering
- Sidechain: External sidechain for Stabilizer/Impact referencing and Mid/Side detection.
- Processing blueprint: Flagship mastering suite with AI Master Assistant, dynamic EQ, spectral shaping, transient impact, and multiband maximization.
- Key features:
  - Master Assistant builds chain suggestions from reference tracks
  - Stabilizer adaptive spectral balancing across tonal bands
  - Impact transient shaper with independent mid/side targets
  - Maximizer with IRC IV/V, delta monitoring, and codec preview
- Core building blocks:
  - DSP::MasterAssistant, DSP::DynamicEQ, DSP::Stabilizer, DSP::ImpactShaper, DSP::Maximizer, DSP::CodecPreview, DSP::ReferenceMatch
- Signal/voice flow: Input → Assistant analysis / reference match → Module stack (EQ/Stabilizer/Impact/Imager) → Maximizer → Output
- TODO:
  - Wire PluginSDK parameter/route scaffolding to match the modules above
  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint
