# Task: GtkDrawImage Upstream Patch Artifact
# Status: DONE

## Objective
Provide an actionable patch artifact for `ai-upp` to remove invalid `gdk_cairo_create(NULL)` usage in GTK image extraction path.

## Scope
- Produce patch file against `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`.
- Keep patch minimal and low-risk.
- Document apply instructions and expected effect.

## Inputs
- `docs/cute-gtk-upstream-tracking-2026-03-06.md`
- `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`

## Definition of Done
- [x] Patch artifact exists in repository.
- [x] Apply instructions are included.
- [x] Patch rationale references observed startup warning.

## Evidence
- `docs/patches/ai-upp-gtkdrawimage-null-window-guard.patch`
