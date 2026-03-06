# Task: Dependency GTK Warning Upstream Tracking
# Status: TODO

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
- [ ] Upstream issue note with reproducer and call chain is prepared.
- [ ] Candidate patch options and tradeoffs documented.
- [ ] Decision recorded: local workaround, upstream patch, or defer.
