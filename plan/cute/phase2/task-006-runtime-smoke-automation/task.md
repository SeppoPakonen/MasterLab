# Task: Runtime Smoke Automation
# Status: DONE

## Objective
Automate a reproducible runtime smoke pass for `Cute` that captures startup warnings and optional GDB backtrace evidence.

## Scope
- Add script to run bounded startup smoke (`timeout`).
- Capture runtime log and optional fatal-critical backtrace.
- Emit simple summary file for phase-2 evidence.

## Inputs
- `bin/Cute`
- Existing manual commands used in phase-2.

## Definition of Done
- [x] Script exists and is executable.
- [x] Script generates runtime and gdb logs.
- [x] Summary report produced under `docs/`.
- [x] Script run completed successfully in current environment.

## Evidence
- Script:
  - `scripts/cute_runtime_smoke.sh`
- Artifacts:
  - `docs/runtime-smoke/cute-runtime.log`
  - `docs/runtime-smoke/cute-gdb-bt.log`
  - `docs/runtime-smoke/cute-runtime-summary.md`
- Latest run result:
  - `exit=124` from bounded timeout run, warning/backtrace captured successfully.
