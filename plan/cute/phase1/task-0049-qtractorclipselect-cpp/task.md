# Task: Convert `qtractorClipSelect.cpp` to U++
# Status: DONE

## Objective
Manually read `tmp/q/src/qtractorClipSelect.cpp` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorClipSelect.cpp`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `AudioEditing`
- Suggested output root: `src/AudioEditing`
- Package rationale: Edit operations, range/tempo dialogs, and offline audio-edit helpers.

## Conversion Notes
- Write the converted source into `src/AudioEditing/qtractorClipSelect.cpp` or the closest package-local equivalent once the package manifest is updated.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Definition of Done
- [x] Source file has been read manually.
- [x] U++-style converted output has been written to the target package or Cute assembly notes.
- [x] Any required `.upp` manifest additions are recorded for later package updates.
- [x] No compile/build work was attempted as part of this task.
