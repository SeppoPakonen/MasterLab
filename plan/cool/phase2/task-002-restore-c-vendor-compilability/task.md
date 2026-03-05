# Task: Restore C Vendor Compilability
# Status: DONE

## Objective
Fix immediate C compilation blockers introduced by mechanical phase-1 conversion in vendor C sources.

## Scope
- Remove `#include "Cool.h"` from converted `.c` units under `src/Cool/lib/external/*` and any other plain-C files.
- Keep C units framework-agnostic and compilable with C compiler rules.
- Do not perform behavioural rewrites; only compile bring-up hygiene.

## Inputs
- First failing files from build:
- `src/Cool/lib/external/kiss_fft/KissFft.cpp`
- `src/Cool/lib/external/kiss_fft/KissFftr.cpp`
- `src/Cool/lib/external/media_ctrl/Mediactrl.cpp`

## Definition of Done
- [ ] Vendor C units no longer include C++-only Cool headers.
- [ ] Build passes beyond current C vendor failures.
