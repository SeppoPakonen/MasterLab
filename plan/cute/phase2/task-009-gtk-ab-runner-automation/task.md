# Task: GTK A/B Runner Automation
# Status: DONE

## Objective
Automate baseline/patched/restored GTK warning measurement for the dependency patch candidate.

## Scope
- Add script to run A/B sequence safely with dependency file backup/restore.
- Capture counts and summary report under `docs/runtime-smoke`.
- Keep project build green after restore.

## Inputs
- `scripts/cute_runtime_smoke.sh`
- `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`
- `docs/patches/ai-upp-gtkdrawimage-null-window-guard.patch`

## Definition of Done
- [x] Runner script exists and is executable.
- [x] Script produces baseline/patched/restored counts.
- [x] Dependency file is restored automatically.
- [x] Report written to `docs/runtime-smoke`.

## Evidence
- Runner script:
  - `scripts/cute_gtk_ab_runner.sh`
- Report:
  - `docs/runtime-smoke/cute-gtk-ab-runner-summary.md`
- Latest measured counts:
  - baseline `246`
  - patched `0`
  - restored `246`
