# MIDI Modifiers Insert Stub

## Reference
- Inspired by: Cubase MIDI Modifiers
- Category: Comprehensive note/controller transformer
- Shares logic with: Transformer (rule actions) and Density (randomisation)

## Summary
MidiModifiers provides a compact set of transforms (transpose, velocity shift/compression, length compression, randomisation grids, range filters, delay, scale quantiser). It acts as a simplified front-end to the `MidiLogic::RuleEngine` used by Transformer, meaning both inserts share the same transformation primitives. Random grids reuse `MidiRandom::DeterministicStream` to ensure consistent results when paired with Density or Transformer macros.

## Core Classes
- `MidiGraph::InputCollector` — Base intake path.
- `MidiModifiers::TransformGrid` — Holds parameterised transforms for position/pitch/velocity/length; reused by Transformer presets.
- `MidiModifiers::Randomizer` — Implements random min/max operations using deterministic seeds shared with Density.
- `MidiFilters::RangeLimiter` — Range grid (velocity/note limit/filter) uses same limiter as ContextGate.
- `MidiTiming::DelayOperator` — Adds fixed delay in ms; shared with Quantizer delay parameter for live compensation.
- `MidiHarmony::ScaleQuantizer` — Applies scale and root note; same engine as Quantizer's scaling stage.

## Graph Layout
Input → `InputCollector` → `TransformGrid`
→ `Randomizer` → `RangeLimiter` → `DelayOperator`
→ `ScaleQuantizer` → Output.

## Implementation Notes
- UI grids map to `TransformGrid` rows. Each cell writes into shared parameter blocks, ensuring Transformer can import/export configurations seamlessly.
- Random operations respect `DeterministicStream` seeds that depend on note properties (pitch, position) for reproducibility.
- Scale/Root parameters reuse global scale dictionary shared with Quantizer and HarmonyPhraseStudio.

## TODO
- Add per-channel override toggles for transforms (channel-specific operations) via `MidiRouting::ChannelRouter`.
- Provide preview panel showing cumulative transform effect using shared `MidiVisualization::DeltaList` component.
- Surface factory presets (soft humanise, EDM gate) stored alongside Transformer macros.
