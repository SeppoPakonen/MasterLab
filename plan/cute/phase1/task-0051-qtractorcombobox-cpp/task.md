# Task: Convert `qtractorComboBox.cpp` to U++
# Status: TODO

## Objective
Manually read `tmp/q/src/qtractorComboBox.cpp` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorComboBox.cpp`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `Theme`
- Suggested output root: `src/Theme`
- Package rationale: Reusable visual widgets with application-wide look/feel implications.

## Conversion Notes
- Write the converted source into `src/Theme/qtractorComboBox.cpp` or the closest package-local equivalent once the package manifest is updated.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Definition of Done
- [ ] Source file has been read manually.
- [ ] U++-style converted output has been written to the target package or Cute assembly notes.
- [ ] Any required `.upp` manifest additions are recorded for later package updates.
- [ ] No compile/build work was attempted as part of this task.
