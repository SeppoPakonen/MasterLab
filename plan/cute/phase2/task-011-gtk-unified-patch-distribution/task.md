# Task: GTK Unified Patch Distribution
# Status: DONE

## Objective
Provide a standard unified diff patch (`patch -p0` compatible) for the dependency-side GTK warning fix.

## Scope
- Generate unified patch file from original vs patched dependency source.
- Add helper script to apply unified patch safely.
- Validate apply/revert cycle works with existing toggle workflow.

## Inputs
- `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`
- `scripts/toggle_aiupp_gtk_patch.sh`

## Definition of Done
- [x] Unified diff patch exists.
- [x] Apply helper script exists.
- [x] `patch -p0` apply verified.
- [x] Revert to original verified.

## Evidence
- Unified patch:
  - `docs/patches/ai-upp-gtkdrawimage-null-window-guard.diff`
- Apply helper:
  - `scripts/apply_aiupp_gtk_unified_patch.sh`
- Validation report:
  - `docs/runtime-smoke/cute-gtk-unified-patch-cycle-2026-03-06.md`
- Measured counts:
  - patched `0`
  - reverted `246`
