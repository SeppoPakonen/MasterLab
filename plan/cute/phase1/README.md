# Cute Phase 1

## Objective
Manually convert each qtractor source file in `tmp/q/src/` root into U++ style and route it into the MasterLab package structure.

## Policy
- Do not compile in phase 1.
- Do not shrink the design into stubs; preserve the original class/function surface as closely as practical.
- Follow U++ package conventions from `AGENTS.md`: package main header owns includes, non-main headers avoid includes, `.cpp` files include only their package main header where practical.
- Reuse existing packages under `src/*` instead of inventing parallel ones unless a task explicitly lands in `Cute` assembly plumbing.

## Shared References
- Investigation: `docs/cute-phase1-investigation.md`
- Backlog index: `plan/cute/phase1/BACKLOG.md`
- Conversion rules: `plan/cute/phase1/CONVERSION_RULES.md`
