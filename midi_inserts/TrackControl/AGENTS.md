# Track Control MIDI Insert Stub

## Reference
- Inspired by: Cubase Track Control (GS/XG editors)
- Category: Multi-tab controller macro editor
- Integrates with: MidiController rows, AutoLFO, MicroTuner tuning tables

## Summary
TrackControl provides GS/XG macro panels with pre-defined controller mappings, reset/off buttons, and effect selectors. It reuses `MidiRouting::ControllerMatrix` and `MidiRouting::ControllerLibrary` from MidiController, while profile/preset data is sourced from `MidiSysEx::ProfileLibrary`, also intended for future SysEx editors. Automation-friendly sliders share the same parameter descriptors as MidiController and AutoLFO to keep CC automation consistent.

## Core Classes
- `MidiSysEx::ProfileLibrary` — Holds GS/XG profile definitions, including default/off presets; shared with upcoming SysEx tools.
- `MidiRouting::ControllerMatrix` — Applies control changes; reused broadly.
- `MidiRouting::ControllerLibrary` — Provides human-readable names; same as MidiController.
- `MidiDynamics::MacroSnapshot` — Stores current slider states for reset/off operations; also used by MidiModifiers preset capture.
- `MidiVisualization::TabModel` — Drives multi-tab UI representation (GS1/XG1/XG2).
- `MidiEffects::EffectSelector` — Handles effect drop-downs (Hall1, Chorus1, etc.) mapping to SysEx/CC combos.

## Graph Layout
Input → `MidiRouting::ControllerMatrix` injections from macro sliders/presets → Output (pass-through notes + injected CC/SysEx events). Profile resets call into `MacroSnapshot` to emit default values via `ControllerMatrix` or SysEx routes from `ProfileLibrary`.

## Implementation Notes
- Reset/Off buttons fetch presets from ProfileLibrary and write them through shared routing utilities.
- Effect drop-downs use `EffectSelector` to map selection to appropriate SysEx + controller values.
- Master Volume, Send levels, ADSR etc. share slider models with MidiController enabling consistent automation ranges.

## TODO
- Populate GS/XG profile data in `MidiSysEx::ProfileLibrary` (JSON/asset format shared with future editors).
- Implement snapshot compare to highlight parameter changes vs defaults.
- Add MicroTuner integration to show tuning offsets when GS/XG profiles expose micro-tuning entries.
