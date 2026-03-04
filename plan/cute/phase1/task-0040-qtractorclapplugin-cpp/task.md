# Task: Convert `qtractorClapPlugin.cpp` to U++
# Status: TODO

## Objective
Manually read `tmp/q/src/qtractorClapPlugin.cpp` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorClapPlugin.cpp`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `VSTHost`
- Suggested output root: `src/VSTHost`
- Package rationale: Plugin discovery, wrappers, scan surfaces, and plugin-facing UI.

## Conversion Notes
- Write the converted source into `src/VSTHost/qtractorClapPlugin.cpp` or the closest package-local equivalent once the package manifest is updated.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Definition of Done
- [ ] Source file has been read manually.
- [ ] U++-style converted output has been written to the target package or Cute assembly notes.
- [ ] Any required `.upp` manifest additions are recorded for later package updates.
- [ ] No compile/build work was attempted as part of this task.
