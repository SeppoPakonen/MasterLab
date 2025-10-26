# Zen Core Workstation Instrument Stub

## Reference Snapshot (tmp/ZENOLOGY.md)
- Release: Roland ZENOLOGY (May 2020) — expandable softsynth built on the ZEN-Core engine found in Fantom, Jupiter-X/Xm, MC-707.
- Library: Ships with **3,597 presets** plus themed expansions; patches are compatible with ZEN-Core hardware.
- Engine: Hybrid PCM + virtual analog partials, analog behaviour modelling (ABM) model expansions, motion-sequencing and macro morphing.
- UX: Browser-driven UI with partial edit panes, drum kit editor (16 rotaries for per-voice params), and deep integration with onboard FX racks.

## Engine Layers & Scenes
| Layer | Source | Notes |
|-------|--------|-------|
| **Partial A–D** | `Synth::ZenPartial` (PCM, VA, noise, supersaw) | Cross/FM/sync options, per-partial filter & amp, per-partial MFX send. |
| **Tone Scene** | `Synth::VoiceManager` + `Synth::ModMatrix` | Four partials layered/split with Motion Designer modulation, velocity zones, macro morph. |
| **Drum Kits** | Drum tone mode | 16 lanes each with level/pan/ADSR, mapped to partial engine, uses per-lane FX macros. |
| **Model Expansions** | ABM variants (JX-8P, SH-101, JUNO-106, Jupiter-8, JD-800, etc.) | Swap core oscillators/filter blocks and expose dedicated macro panels. |

- Scenes morph between two tone snapshots via `Automation::MotionDesigner` + `DSP::SceneMorph`.
- Motion Designer provides step-LFOs, probability per-step, and macro destinations for vibrato/filters.
- Macro system bridges to `AudioUI` rack surfaces to surface the Scene FX (TFX) parameters alongside instrument macros.

## FX & Routing Overview
- Uses `FX::ZenCoreFxRack` internally for MFX/IFX/TFX order: **Pre** (conditioning) → **IFX** per partial → **MFX** shared rack → **TFX** master bus.
- Drum kits substitute IFX with per-pad processors while sharing MFX + TFX.
- `PluginSDK::RoutingMap` captures lane connections (Scene → Partial → IFX → MFX → TFX → Output).

### Graph Nodes (for `PluginSDK::GraphVisualization`)
- `Tone.In` — voice allocation entry.
- `Partial.A/B/C/D` — audio generators (PCM/VA).
- `CrossMod.Bus` — modulation bus for ring/FM routing.
- `IFX.A/B/C/D` — per-partial insert processing.
- `Scene.MFX` — shared multi-FX slot (90+ algorithms, including combinations).
- `Scene.TFX` — time-based FX master (delay/reverb/comp).
- `Output` — stereo out, feeds Analyzer taps.
- `MotionDesigner` — modulation sequencer lane (control edges only).
- `MacroMorph` — morph interpolation between Scene snapshots.

### Graph Edges
- Audio: `Tone.In → Partial.X`, `Partial.X → IFX.X`, `IFX.X → Scene.MFX`, `Scene.MFX → Scene.TFX → Output`.
- Control: `MotionDesigner → Partial.X`, `MacroMorph → Scene.MFX`, `MacroMorph → Scene.TFX`, `HardwarePatch → Tone.In`.

## Repository Integration
- Parameters registered through `PluginSDK::ParameterSet` with grouped IDs (`partial1_cutoff`, `scene_morph`, `motion_rate`, `drumPad05_decay`, etc.).
- Graph metadata exposed via `PluginSDK::GraphVisualization` for UI rack diagrams and ACTIVE-PATH highlighting.
- Forward-looking hooks:
  - `Synth::VoiceManager` and `Sample::StreamEngine` from `AudioCore` for voice + sampling duties.
  - `Automation::MotionDesigner` and `DSP::SceneMorph` (AudioFX) for modulation/morphing.
  - `FX::ZenCoreFxRack` (effects package) for shared FX catalogue.

## TODO / Next Steps
1. Bridge to `AudioCore::Synth::VoiceManager` once implemented (Task 86).
2. Implement drum kit mode parameter templating (per-pad rotaries) using `PluginSDK::GraphVisualization` detail nodes.
3. Provide preset import/export to `DSP::PresetManager` with patch compatibility metadata.
4. Evaluate splitting package into per-model instrument shells (e.g., `ZenModel_JX8P`, `ZenModel_JUNO106`) that reuse shared partial/FX scaffolding.

## Package Split Consideration
- Model expansions feature unique parameter panels; likely best represented as thin packages layering on top of `ZenCoreWorkstation`.
- Proposed approach: maintain core engine here, spin out Model UI stubs as optional packages referencing shared partial rack.
