# Cool Track

## Purpose
Plan the kdenlive-to-U++ conversion into the MasterLab package layout without attempting to compile in phase 1.

## Scope
- Source inventory: files under `tmp/k/src/`.
- Output model: `src/Cool` is the assembly anchor while converted sources are written in U++ style.
- Phase 1 is manual source conversion only.
- Phase 2 starts assembly wiring, compilation, and error fixing.

## Phase Layout
- `phase1/`: one task per source file to be manually read and converted.
- `phase2/`: compile and integration backlog after source corpus conversion exists.

## Key Assumptions
- Phase 1 focuses on source-code and source-adjacent artifacts in `tmp/k/src`.
- Converted code keeps the main class/function surface and approximate code volume.
- No compile/link work in phase 1.
