# Task: GTK Patch Toggle Automation
# Status: DONE

## Objective
Provide a safe, repeatable way to apply and revert the dependency-side GTK warning patch for local validation workflows.

## Scope
- Add script with `apply` and `revert` modes.
- Ensure operation is idempotent and validates expected line presence.
- Verify with build and runtime smoke.

## Inputs
- `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`
- `scripts/cute_runtime_smoke.sh`

## Definition of Done
- [x] Toggle script exists and is executable.
- [x] `apply` modifies target line as expected.
- [x] `revert` restores original target line.
- [x] Build and smoke run succeed after toggle cycle.

## Evidence
- Script:
  - `scripts/toggle_aiupp_gtk_patch.sh`
- Toggle-cycle report:
  - `docs/runtime-smoke/cute-gtk-toggle-cycle-2026-03-06.md`
- Measured counts:
  - patched `0`
  - reverted `246`
