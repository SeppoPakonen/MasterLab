# Task: Stub Replacement And Behavior Parity
# Status: IN_PROGRESS

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
- [ ] Each stub has implemented behavior or explicit guarded exclusion.
- [ ] Build remains green after changes.

## Progress Notes
- Stub inventory completed and documented in:
  - `docs/cute-stub-inventory-2026-03-06.md`
- Next execution step:
  - Decide per-file strategy (implement vs. guarded exclusion) for the confirmed compile-safe stubs.
