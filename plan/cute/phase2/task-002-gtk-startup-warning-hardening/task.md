# Task: GTK Startup Warning Hardening
# Status: TODO

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
- [ ] Warning reproduction command and output documented.
- [ ] Root source file/function identified for first warning.
- [ ] If project-side mitigation exists, implemented and validated.
- [ ] If dependency-side only, create explicit follow-up note with decision.
