# Task: Convert `qtractorObserverWidget.h` to U++
# Status: TODO

## Objective
Manually read `tmp/q/src/qtractorObserverWidget.h` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorObserverWidget.h`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `Tooling`
- Suggested output root: `src/Tooling`
- Package rationale: Low-level utility helpers and observer/container primitives.

## Conversion Notes
- Write the converted source into `src/Tooling/qtractorObserverWidget.h` or the closest package-local equivalent once the package manifest is updated.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Definition of Done
- [ ] Source file has been read manually.
- [ ] U++-style converted output has been written to the target package or Cute assembly notes.
- [ ] Any required `.upp` manifest additions are recorded for later package updates.
- [ ] No compile/build work was attempted as part of this task.
