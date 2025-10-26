# Zen Core FX Rack Effect Stub

## Reference Snapshot (tmp/ZENOLOGY.md)
- Built atop ZEN-Core FX engine used by Zenology Pro and compatible hardware (Fantom, Jupiter-X).
- Ships with **90+ algorithms**: modulation (JUNO chorus, SBF-325 flanger), delays, amp sims, filters, pitch shifters, mastering tools.
- Supports **Combination** processors (dual chains, amp+delay, enhancer+chorus) plus ABM model-specific FX for expansions (JX-8P PG-800, JD-800 dual-stage FX).
- Motion Designer extends modulation with step LFOs, envelope follower, probability per step.
- Scene morphing crossfades between two FX states; tied to macro hardware controls.

## Rack Architecture
| Stage | Role | Notes |
|-------|------|-------|
| **Pre** | Conditioning | HPF/level match, dry kill, stereo width. |
| **IFX Slots (A–C)** | Serial FX | Any algorithm, including Combination processors; optionally modulated by Motion Designer lanes. |
| **MFX** | Shared bus | Time/modulation FX, gating, amp sims; can be repositioned pre/post IFX chain. |
| **TFX** | Master FX | Delay, reverb, mastering limiter; last in chain. |
| **Macro Morph** | Transition | `DSP::SceneMorph` blending between Scene A/B snapshots. |

- Envelope follower taps input dynamics for modulation sources.
- Combination processors instantiate sub-chains internally; graph metadata should expose nested nodes for UI highlight.
- Works standalone or as internal rack for `Instruments::ZenCoreWorkstation`.

## Graph Definition Guidelines
- Nodes: `Input`, `Pre`, `IFX.A`, `IFX.B`, `IFX.C`, `MFX`, `TFX`, `Output`, `MotionDesigner`, `EnvelopeFollower`, `MacroMorph`.
- Audio Edges: `Input → Pre → IFX.A → IFX.B → IFX.C → MFX → TFX → Output`.
- Control Edges: `MotionDesigner → IFX.*`, `EnvelopeFollower → IFX.*`, `MacroMorph → IFX/MFX/TFX`.
- Active path toggles per-slot; `PluginSDK::GraphVisualization` should show edges disabling when slot bypassed.

## Repository Integration
- Parameter groups:
  - Slot enable/algorithm selectors (`slotA_algorithm`, `slotA_mix`, etc.).
  - Motion Designer lanes (`motion_rate`, `motion_depth`, `motion_probability`).
  - Scene morph controls (`scene_morph`, `scene_balance`, `macro_assign1`).
  - Envelope follower attack/release/sensitivity.
- Uses `PluginSDK::RoutingMap` to publish serial chain plus optional parallel returns (e.g., Combination dual parallel path).
- Shares algorithm catalogue via `DSP::ZenCoreMFXCatalogue` (AudioFX package) to surface slot labels and combination flags.

## TODO / Next Steps
1. Enrich `DSP::ZenCoreMFXCatalogue` entries with parameter templates and combination signal maps.
2. Expose Combination processor routing to `PluginSDK::GraphVisualization` (nested nodes).
3. Integrate with `AudioAnalysis::DSP::Analyzer` for per-slot metering.
4. Coordinate preset metadata with instrument patches (shared macros, scene morph snapshots).
