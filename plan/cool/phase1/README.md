# Cool Phase 1

## Objective
Manually convert each kdenlive source file in `tmp/k/src/` into U++ style and route it into the Cool target structure.

## Policy
- Do not compile in phase 1.
- Do not shrink design into stubs; preserve main classes/functions and rough code volume.
- Follow U++ package conventions from `AGENTS.md`: package main header owns includes, non-main headers avoid includes, and implementation files include the package main header where practical.
- Output location is `src/Cool` for this track unless a task explicitly documents a split target.

## Shared References
- Backlog index: `plan/cool/phase1/BACKLOG.md`
- Conversion rules: `plan/cool/phase1/CONVERSION_RULES.md`
