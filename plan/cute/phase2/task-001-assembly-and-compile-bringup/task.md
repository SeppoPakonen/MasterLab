# Task: Cute Assembly And Compile Bring-Up
# Status: DONE

## Objective
Create the `src/Cute` assembly/package wiring after phase 1 has produced enough converted source, then begin the first compile-driven error fixing pass.

## Scope
- Create `src/Cute/Cute.upp`, `src/Cute/Cute.h`, and `src/Cute/main.cpp` or equivalent assembly root files.
- Update touched package `.upp` manifests so converted files are actually listed.
- Resolve header/include-rule violations introduced during phase 1.
- Run the first build attempt only after the source corpus is in place.

## Inputs
- `plan/cute/phase1/BACKLOG.md`
- `docs/cute-phase1-investigation.md`
- All completed phase-1 conversion tasks.

## Definition of Done
- [x] Cute assembly root exists.
- [x] Relevant package manifests include the converted files.
- [x] First compile attempt has been run.
- [x] Compile errors are triaged into follow-up phase-2 tasks by package or subsystem.

## Evidence
- Created `src/Cute/Cute.upp`, `src/Cute/Cute.h`, and `src/Cute/main.cpp`.
- Updated reachable package `.upp` manifests so converted files are included in build graph.
- Verified compile with:
  - `script/build.py -j2 Cute`
  - Result: links `bin/Cute` successfully.
- Parity and compile evidence written in:
  - `docs/cute-parity-audit-2026-03-06.md`
  - `docs/cute-top-level-parity-mapping-2026-03-06.md`
- Related commits:
  - `17ff2d3` (`codex: complete task cute manifest parity and build stabilization`)
  - `130dd91` (`codex: complete task 001 — top-level parity mapping and CuteAtomic shim`)
