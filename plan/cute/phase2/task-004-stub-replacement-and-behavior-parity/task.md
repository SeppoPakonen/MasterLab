# Task: Stub Replacement And Behavior Parity
# Status: DONE

## Objective
Replace temporary compile-safe stubs introduced during phase-2 bring-up with behaviorally meaningful implementations or explicit guarded exclusions.

## Scope
- Identify files currently stubbed only for link/compile stability.
- For each, decide one path:
  - implement minimal functional behavior, or
  - exclude cleanly via package/config guards with rationale.
- Maintain successful `script/build.py -j2 Cute` build.

## Inputs
- Recent phase-2 commits and diff history.
- Build logs from `script/build.py -j2 Cute`.
- Package manifests under `src/*/*.upp`.

## Definition of Done
- [x] Stub inventory documented.
- [x] Each stub has implemented behavior or explicit guarded exclusion.
- [x] Build remains green after changes.

## Progress Notes
- Stub inventory completed and documented in:
  - `docs/cute-stub-inventory-2026-03-06.md`
- Confirmed bring-up stubs moved to explicit compile-time guarded exclusions using:
  - `CUTE_ENABLE_LEGACY_CUTECLIP_IMPL`
  - `CUTE_ENABLE_LEGACY_CUTEMIXER_IMPL`
  - `CUTE_ENABLE_LEGACY_AUDIOFX_CALIBRATION_IMPL`
  - `CUTE_ENABLE_LEGACY_SPATIALDSP_IMPL`
  - `CUTE_ENABLE_LEGACY_SPATIALDSP_ADDITIONAL_IMPL`
