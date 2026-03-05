# Cool Phase 2 Backlog

## Objective
After phase 1 source conversion coverage is high enough, wire `src/Cool` as an assembly, update package manifests, compile, and fix errors.

## Current Bring-Up Findings (first full build)
From `script/build.py -j2 Cool` with full converted `Cool.upp` file list:
- C vendor files in `lib/external/*` fail immediately because phase-1 conversion prepended `#include "Cool.h"` to `.c` units.
- Core subsystem translation (`src/Cool/Core.cpp`) fails on unresolved Qt/KDE symbols and missing type graph (`QUrl`, `QString`, `LinuxPackageType`, etc.).
- Build currently halts at the first 20+ errors in `Core.cpp`, meaning broader subsystem errors are still pending triage.

## Task Queue
- `task-001-assembly-and-compile-bringup`: initial Cool assembly root and first compile pass.
- `task-002-restore-c-vendor-compilability`: remove/adjust phase-1 C-source preambles in `lib/external/*` and similar C units so they compile under U++ toolchain.
- `task-003-bootstrap-main-header-and-type-shims`: establish interim Cool main-header/type bridge so converted units can compile before full Qt->U++ replacement.
- `task-004-core-subsystem-porting-pass`: port `Core.cpp/.h` and immediate dependencies from Qt/KDE runtime assumptions to compile-time-safe Cool/U++ equivalents.
- `task-005-error-harvest-pass-2`: rerun build after tasks 002-004 and produce next grouped compile-error backlog by subsystem.
