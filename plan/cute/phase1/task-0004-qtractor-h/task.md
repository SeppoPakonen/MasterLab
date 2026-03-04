# Task: Convert `qtractor.h` to U++
# Status: DONE

## Objective
Manually read `tmp/q/src/qtractor.h` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/q/src/qtractor.h`

## Target
- Cute assembly anchor: `src/Cute`
- Suggested package: `AudioMaster`
- Suggested output root: `src/AudioMaster`
- Package rationale: Main application shell, message surfaces, and top-level window hosting.

## Conversion Notes
- Write the converted source into `src/AudioMaster/qtractor.h` or the closest package-local equivalent once the package manifest is updated.
- Preserve the original main classes/functions and roughly similar code volume.
- Reuse existing stub types or packages when they already express the same responsibility.
- Follow `plan/cute/phase1/CONVERSION_RULES.md` and `docs/cute-phase1-investigation.md`.

## Output
- `src/AudioMaster/qtractor.h`
- `src/AudioMaster/qtractorAbout.h`
- updated `src/AudioMaster/qtractor.cpp` to move declarations out of the implementation file
- updated `src/AudioMaster/AudioMaster.h` to surface the converted headers through the package main header

## Manifest Notes
- Later add `qtractor.h`, `qtractorAbout.h`, and `qtractor.cpp` to `src/AudioMaster/AudioMaster.upp`.

## Definition of Done
- [x] Source file has been read manually.
- [x] U++-style converted output has been written to the target package or Cute assembly notes.
- [x] Any required `.upp` manifest additions are recorded for later package updates.
- [x] No compile/build work was attempted as part of this task.
