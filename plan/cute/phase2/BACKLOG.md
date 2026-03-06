# Cute Phase 2 Backlog

## Objective
After phase 1 source conversion coverage is high enough, wire `src/Cute` as an assembly, update package manifests, compile, and fix errors.

## Seed Tasks
- `task-001-assembly-and-compile-bringup`: create the Cute assembly, finalize `uses(...)` and `.upp` entries, then begin compile-error triage.
- `task-002-gtk-startup-warning-hardening`: investigate and mitigate GTK/GDK startup critical warnings.
- `task-003-plugin-scan-parity-and-integration`: close remaining plugin-scan mapping/integration parity.
- `task-004-stub-replacement-and-behavior-parity`: replace temporary compile-safe stubs with behavior or guarded exclusions.
- `task-005-dependency-gtk-warning-upstream-tracking`: prepare dependency-layer patch strategy and ownership note.
- `task-006-runtime-smoke-automation`: add and run runtime smoke evidence automation for `Cute`.
- `task-007-gtkdrawimage-upstream-patch-artifact`: provide concrete ai-upp patch artifact for GTK startup warning.
