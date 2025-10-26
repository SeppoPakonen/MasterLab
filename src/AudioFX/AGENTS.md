# AudioFX Package — Effect Engine Blueprint

## Overview
AudioFX owns the reusable processing blocks required by the effect implementations documented in `EFFECTS.md`. It provides signal routing, parameter handling, modulation, and specialist DSP components that higher-level packages compose into finished plug-ins or internal processors.

## Shared DSP Infrastructure

- **`DSP::SignalBus`** — Manages multi-channel audio frames, consolidates bus formats (mono/stereo/surround), and exposes helpers such as `AcquireBlock(int frames)` and `Route(const BusLayout& src, const BusLayout& dst)` for sample-accurate routing with latency accounting.
- **`DSP::ParameterSet`** — Registers automatable parameters, performs smoothing with `ApplySmoothing(double milliseconds)`, and emits host descriptors; integrates with automation to resolve parameter IDs.
- **`DSP::ModMatrix`** — Normalised modulation matrix with `AddSource`, `AddDestination`, and `ComputeConnections()` to produce per-sample modulation buffers driven by LFOs, envelopes, MIDI, or macro controllers.
- **`DSP::LatencyBuffer`** — Provides `Configure(int lookahead)` and `Process(BufferView in, BufferView out)` to support look-ahead stages; reports latency to host and to `SignalBus`.
- **`DSP::PresetManager`** — JSON-backed preset service. Core methods include `LoadPreset(const String& id)`, `StorePreset(const Preset& preset)`, and `EnumerateLibrary()`; shared between internal FX and exported plug-ins.

## Modulation, Sequencing, and Macro Control

- **`DSP::MotionSequencer`** — Tempo-aware step sequencer supporting probability, ratcheting, and automation capture. Supplies `Advance(int samples)` and `RenderModulation()` used by movement-heavy effects (Zenology FX, Effectrix, Kaleidoscopes).
- **`DSP::SceneMorph`** — Manages dual scene snapshots, providing `Interpolate(double morph)` to blend parameter sets for macro morphing transitions.
- **`DSP::ModuleSwitcher`** — Parameter-driven selector that activates one processor lane (Kick/Bass/Synth/Vocal) at a time with smooth crossfades.
- **`DSP::MacroController`** — Maps high-level macro knobs to multiple parameter destinations, offering `Attach(int macroId, ParamRef target, double depth)` and real-time `Update(double value)`.
- **`UI::RackView` hooks** — AudioFX exposes rack descriptors (cards, macro knobs, meters) consumed by AudioUI to render the consistent rack shell.

## Specialist Processors

- **Vocal & Pitch**
  - `DSP::VoiceFeatureExtractor` — Extracts pitch, formants, spectral flux; core methods `AnalyzeBlock`, `GetPitchTrack()`, `GetFormantProfile()`.
  - `DSP::HarmonyGenerator` — Generates detuned/delayed harmonies with `RenderVoices(const HarmonySetup&)`, forming the Omnivox and Nectar harmony engines.
  - `DSP::StyleTransferNet` — Runtime wrapper around neural voice style models, exposing `LoadModel`, `ProcessFrame`.
  - `DSP::FormantMorpher` — Applies vocal tract length transformations with `ConfigureTargets` and `Process`.
  - `DSP::VoiceEncoder` / `DSP::VoiceDecoder` — Low-latency neural codec pair supporting Replay voice conversion.

- **Mastering & Loudness**
  - `DSP::LUFSMeter`, `DSP::ISPDetector`, and `DSP::AutoGainScheduler` share weighted integration, peak oversampling, and gain staging utilities for APU, Ozone, and Crest-related processors.
  - `DSP::MasterAssistant`, `DSP::Stabilizer`, `DSP::ImpactShaper`, `DSP::PriorityAllocator`, `DSP::DitherEngine` provide the adaptive spectral shaping, transient management, and limiter priority systems used by Ozone/Ozone-derived designs.

- **Transient / Dynamic Hybrid**
  - `DSP::AttackSustainSplitter`, `DSP::DynamicNotchBank`, `DSP::TransientDesigner`, `DSP::SubSynth`, `DSP::HarmonicEnhancer` deliver the Crave Transient EQ, Kick Shaper, and Vitamin-style modules.

- **Spatial / Immersive**
  - `DSP::OrbitalPanner`, `DSP::SurroundLimiter`, `DSP::ConvolutionEngine`, `DSP::HybridReverb`, `DSP::SpringReverb`, and `DSP::BinauralRenderer` (shared with Devices) handle surround, convolution, and hybrid reverb processing.

## Hosting & Rack Services

- **`DSP::RackHost`** and **`DSP::ChainNode`** — Execute modular chains for StudioRack/StudioVerse and Guitar Rig style setups with serial/parallel routing, zero-CLR macros, and shared latency management.
- **`DSP::LatencyManager`** — Aggregates node latencies, exposing `GetTotalLatency()` and compensation callbacks for host transport.
- **`DSP::PresetBrowser`** — Works with StudioVerse cloud metadata to surface curated effect chains.

## Inter-Package Contracts

- Consumes analysis data from `AudioAnalysis` (`DSP::Analyzer`, `DSP::SpectrumAnalyzer`).
- Exposes UI descriptors to `AudioUI` for rack and macro rendering.
- Shares calibration and spatial engines with `Devices` (Ambisonics encoder, head tracking).
- Supplies modulation hooks to `AudioCore` for instrument macro integration.
