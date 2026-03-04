# Task: Convert `qtractorTimeScaleCommand.h` to U++
# Status: DONE

## Objective
Manually read `tmp/q/src/qtractorTimeScaleCommand.h` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractorTimeScaleCommand.h`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `ProjectMgmt`
- Suggested output root: `src/ProjectMgmt`
- Package rationale: Undoable command surfaces and command-routing definitions.

## Conversion Notes
- Write the converted source into `src/ProjectMgmt/qtractorTimeScaleCommand.h` or the closest package-local equivalent once the package manifest is updated.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Definition of Done
- [ ] Source file has been read manually.
- [ ] U++-style converted output has been written to the target package or Cute assembly notes.
- [ ] Any required `.upp` manifest additions are recorded for later package updates.
- [ ] No compile/build work was attempted as part of this task.
