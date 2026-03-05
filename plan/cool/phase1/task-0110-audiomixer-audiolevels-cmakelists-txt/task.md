# Task: Convert `audiomixer/audiolevels/CMakeLists.txt` to U++
# Status: DONE

## Objective
Manually read `tmp/k/src/audiomixer/audiolevels/CMakeLists.txt` and convert it into MasterLab U++ conventions without attempting to compile.

## Source
- `tmp/k/src/audiomixer/audiolevels/CMakeLists.txt`

## Target
- Cool assembly anchor: `src/Cool`
- Suggested package: `Cool`
- Suggested output root: `src/Cool`
- Package rationale: phase-1 landing in Cool assembly; split to additional packages can be planned after first-pass conversion coverage.

## Conversion Notes
- Preserve main classes/functions and approximate code volume.
- Convert Qt/kdenlive framework usage to U++ conventions.
- Keep converted naming aligned with track rules (`CapitalCase` for classes/functions, `lower_underscore` for variables).
- Do not keep kdenlive product naming in converted code; use Cool/MusicEditor naming.
- Update package `.upp` manifest entries for created outputs.

## Output
- `src/Cool/audiomixer/audiolevels/CMakeListsConversion.md`

## Definition of Done
- [x] Source file has been read manually.
- [x] U++-style converted output has been written to the target package.
- [x] Required `.upp` manifest additions are recorded/applied.
- [x] No compile/build work was attempted as part of this task.
