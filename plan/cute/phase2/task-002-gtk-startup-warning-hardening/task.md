# Task: GTK Startup Warning Hardening
# Status: DONE

## Objective
Investigate and reduce startup GTK/GDK critical warnings observed when launching `bin/Cute`, while keeping build compatibility with the current ai-upp stack.

## Scope
- Reproduce startup warnings with a deterministic command.
- Capture stack trace/evidence for first critical warning.
- Determine whether warning source is in project code or ai-upp dependency layer.
- Implement in-project mitigation if feasible without patching external dependencies.

## Inputs
- `src/Cute/main.cpp`
- Runtime logs from `./bin/Cute`
- GDB backtrace evidence

## Definition of Done
- [x] Warning reproduction command and output documented.
- [x] Root source file/function identified for first warning.
- [x] If project-side mitigation exists, implemented and validated.
- [x] If dependency-side only, create explicit follow-up note with decision.

## Evidence
- Runtime log reproduced via: `timeout 5s ./bin/Cute`
- Backtrace captured via:
  - `gdb -q --batch -ex 'set env G_DEBUG fatal-criticals' -ex run -ex bt --args ./bin/Cute`
- Decision and call chain documented in:
  - `docs/cute-gtk-startup-warning-2026-03-06.md`
- Outcome: warning source is dependency-side (`ai-upp` GTK skin init), no safe project-side fix in this pass.
