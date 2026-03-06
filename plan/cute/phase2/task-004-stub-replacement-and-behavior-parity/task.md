# Task: Stub Replacement And Behavior Parity
# Status: TODO

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
- [ ] Stub inventory documented.
- [ ] Each stub has implemented behavior or explicit guarded exclusion.
- [ ] Build remains green after changes.
