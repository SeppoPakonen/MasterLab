# Task: Cute Assembly And Compile Bring-Up
# Status: TODO

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
- [ ] Cute assembly root exists.
- [ ] Relevant package manifests include the converted files.
- [ ] First compile attempt has been run.
- [ ] Compile errors are triaged into follow-up phase-2 tasks by package or subsystem.
