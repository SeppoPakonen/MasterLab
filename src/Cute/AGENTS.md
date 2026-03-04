# Cute Package

## Overview
Cute is the future assembly root for the qtractor-to-U++ port. In phase 1 it serves as the integration anchor and migration notebook while converted qtractor source files are distributed into the existing `src/*` package structure.

## Phase 1 Role
- Hold assembly-level conversion notes for qtractor artifacts that do not map directly to one existing package.
- Track how the qtractor executable and helper tools should later be represented in U++ assemblies and package manifests.
- Avoid compile-oriented bring-up until phase 2.

## Expected Phase 2 Role
- Provide the `Cute` assembly entrypoint used by `script/build.py Cute`.
- Collect the final `uses(...)` closure for packages populated during phase 1.
- Own top-level startup wiring analogous to `src/daw`, but for the qtractor-derived application.
