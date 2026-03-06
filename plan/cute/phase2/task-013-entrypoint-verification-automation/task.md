# Task: Entrypoint Verification Automation
# Status: DONE

## Objective
Ensure phase-2 automation scripts execute the `Cute` binary and do not accidentally launch `daw`.

## Scope
- Add verification script scanning runtime/patch/status scripts.
- Confirm executable paths and command usage reference `bin/Cute`.
- Produce a report under `docs/phase2`.

## Inputs
- `scripts/cute_runtime_smoke.sh`
- `scripts/cute_gtk_ab_runner.sh`
- `scripts/cute_phase2_status.sh`

## Definition of Done
- [x] Verification script exists and is executable.
- [x] Report generated with pass/fail checks.
- [x] No `bin/daw` launch in phase-2 Cute scripts.

## Evidence
- Script:
  - `scripts/verify_cute_entrypoint.sh`
- Report:
  - `docs/phase2/cute-entrypoint-verification.md`
- Aggregate result:
  - `PASS`
