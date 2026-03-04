# Task: Convert `qtractorAudioIOMatrixForm.ui` to U++
# Status: DONE

## Objective
Manually read `tmp/q/src/qtractorAudioIOMatrixForm.ui` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorAudioIOMatrixForm.ui`

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
- [x] Source file has been read manually.
- [x] U++-style converted output has been written to the target package or Cute assembly notes.
- [x] Any required `.upp` manifest additions are recorded for later package updates.
- [x] No compile/build work was attempted as part of this task.
