# Task: Dependency GTK Warning Upstream Tracking
# Status: DONE

## Objective
Track and isolate the GTK startup warning to dependency-layer ownership and prepare an upstream-compatible patch strategy.

## Scope
- Define minimal reproducer based on current `Cute` startup path.
- Document dependency files/functions involved in first critical path.
- Propose patch options for `ai-upp` with risk notes.

## Inputs
- `docs/cute-gtk-startup-warning-2026-03-06.md`
- `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`
- `../ai-upp/uppsrc/CtrlLib/ChGtk3.cpp`

## Definition of Done
- [x] Upstream issue note with reproducer and call chain is prepared.
- [x] Candidate patch options and tradeoffs documented.
- [x] Decision recorded: local workaround, upstream patch, or defer.

## Evidence
- Prepared tracking note:
  - `docs/cute-gtk-upstream-tracking-2026-03-06.md`
- Reproducer and logs:
  - `scripts/cute_runtime_smoke.sh`
  - `docs/runtime-smoke/cute-runtime-summary.md`
  - `docs/runtime-smoke/cute-gdb-bt.log`
- Decision:
  - dependency-side fix preferred (`ai-upp`), repository-side patch deferred for now.
