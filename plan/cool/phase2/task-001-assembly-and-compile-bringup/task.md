# Task: Cool Assembly And Compile Bring-Up
# Status: TODO

## Objective
Create the `src/Cool` assembly/package wiring after phase 1 has produced enough converted source, then begin the first compile-driven error fixing pass.

## Scope
- Create `src/Cool/Cool.upp`, `src/Cool/Cool.h`, and `src/Cool/main.cpp` or equivalent assembly root files.
- Update touched package `.upp` manifests so converted files are listed.
- Resolve header/include-rule violations introduced during phase 1.
- Run the first build attempt only after source corpus is in place.

## Inputs
- `plan/cool/phase1/BACKLOG.md`
- All completed phase-1 conversion tasks.

## Definition of Done
- [ ] Cool assembly root exists.
- [ ] Relevant package manifests include converted files.
- [ ] First compile attempt has been run.
- [ ] Compile errors are triaged into follow-up phase-2 tasks by package or subsystem.
