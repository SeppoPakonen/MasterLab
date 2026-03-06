# Task: GTK Upstream Patch A/B Validation
# Status: DONE

## Objective
Validate the proposed `ai-upp` GTK patch with before/after runtime smoke measurements.

## Scope
- Measure baseline warning count.
- Apply patch candidate to dependency file.
- Rebuild and re-measure warning count.
- Restore dependency file and re-measure baseline.

## Inputs
- `docs/patches/ai-upp-gtkdrawimage-null-window-guard.patch`
- `scripts/cute_runtime_smoke.sh`
- `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`

## Definition of Done
- [x] Baseline and patched warning counts recorded.
- [x] Dependency file restored after trial.
- [x] Build remains green.

## Evidence
- `docs/cute-gtk-upstream-patch-ab-validation-2026-03-06.md`
