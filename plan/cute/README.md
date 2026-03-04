# Cute Track

## Purpose
Plan the qtractor-to-U++ conversion into the MasterLab package layout without attempting to compile in phase 1.

## Scope
- Source inventory: `294` qtractor-owned source files under `tmp/q/src/`.
- Output model: `src/Cute` acts as the new assembly anchor while converted classes are routed into existing stub packages under `src/*`.
- Phase 1 is manual source conversion only.
- Phase 2 starts assembly wiring, compilation, and error fixing.

## Phase Layout
- `phase1/`: one task per qtractor source file to be manually read and converted to U++ conventions.
- `phase2/`: compile and integration backlog after the source corpus exists in the target packages.

## Key Assumptions
- Vendored SDK trees, assets, translations, and images below nested `tmp/q/src/*/` subdirectories are not phase-1 conversion targets.
- Class names, function names, and rough code volume should remain close to the original qtractor sources.
- Existing stub packages in `src/*` should be filled whenever a file cleanly maps to one of them.
