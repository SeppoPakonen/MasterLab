# Transformer MIDI Insert Stub

## Reference
- Inspired by: Cubase Transformer
- Category: Rule-based MIDI processor (filter/transform/insert)
- Foundation for: MidiModifiers advanced presets and global logical editor

## Summary
Transformer evaluates logical conditions on MIDI events and executes actions (delete, transform, insert). It exposes the same rule/action primitives that MidiModifiers wraps in a simplified UI, ensuring preset compatibility. The logical expression builder relies on `MidiLogic::RuleEngine`, which is intended to become the basis for the project-wide Logical Editor.

## Core Classes
- `MidiGraph::InputCollector` — Event intake.
- `MidiLogic::RuleEngine` — Parses and evaluates conditions with boolean operators; shared with future Logical Editor.
- `MidiLogic::ConditionNode` — Represents individual filter rows, including parentheses handling; shared with MidiModifiers advanced presets.
- `MidiLogic::ActionNode` — Encodes actions (Add, Subtract, Set, Random, Mirror, etc.).
- `MidiLogic::ContextCache` — Provides “Last Event” lookups and Eventcounter tracking reused by MidiMonitor analysis tools.
- `MidiLogic::ExecutionPlanner` — Applies Function mode (Delete/Transform/Insert/Insert Exclusive) by orchestrating the ActionNodes.

## Graph Layout
Input → `InputCollector`
→ `RuleEngine` (condition evaluation) → `ExecutionPlanner`
→ Output events (may include inserted events) with optional feed into `MidiGraph::EventMerger` for new items.

## Implementation Notes
- UI ArrayCtrls map one-to-one with `ConditionNode` and `ActionNode` structures; boolean operators are stored as edges in `RuleEngine` to support parentheses.
- Preset management uses shared storage format so menus/shortcuts (MenuBar, Window shortcuts) can list user presets.
- Context cache shares event history with MidiMonitor allowing consistent comment fields (Value 1, Value 2, etc.).

## TODO
- Implement parser for textual preset import/export to support advanced scripting.
- Add live preview meter to show counts of matched events per rule.
- Integrate with MidiModifiers to allow “Edit in Transformer” round-trip editing.
