# Task: Convert `qtractorConnectForm.ui` to U++
# Status: TODO

## Objective
Manually read `tmp/q/src/qtractorConnectForm.ui` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorConnectForm.ui`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `VSTConnections`
- Suggested output root: `src/VSTConnections`
- Package rationale: Audio/MIDI connection dialogs and bus-routing UI.

## Conversion Notes
- Convert the form into a U++ layout/control implementation associated with `src/VSTConnections`.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Definition of Done
- [ ] Source file has been read manually.
- [ ] U++-style converted output has been written to the target package or Cute assembly notes.
- [ ] Any required `.upp` manifest additions are recorded for later package updates.
- [ ] No compile/build work was attempted as part of this task.
