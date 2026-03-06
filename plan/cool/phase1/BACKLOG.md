# Cool Conversion Backlog

## Status Summary
- **Phase 1 (Manual Conversion)**: RESTARTED. Auditing all mechanical moves.
- **Phase 2 (Compilation)**: PAUSED. Blocked until genuine conversion of core headers is complete.
- **Phase 3 (Expansion)**: PENDING.

## Core System - Genuinely Converted (SETTING THE STANDARD)
- [x] Task-0178: `core.cpp` -> `Core.cpp` (U++ Idiomatic)
- [x] Task-0179: `core.h` -> `Core.h` (U++ Idiomatic)
- [x] Task-0230: `mltconnection.cpp` -> `Mltconnection.cpp` (U++ Idiomatic)
- [x] Task-0231: `mltconnection.h` -> `Mltconnection.h` (U++ Idiomatic)
- [x] Task-0220: `mainwindow.cpp` -> `Mainwindow.cpp` (U++ Foundation set)
- [x] Task-0221: `mainwindow.h` -> `Mainwindow.h` (U++ Idiomatic)

## High Priority - Pending Genuine Conversion (RESTART REQUIRED)
- [ ] Task-0050: `bin/bin.cpp` - Currently mechanical move. Need full U++ conversion.
- [ ] Task-0051: `bin/bin.h` - Currently mechanical move. Need full U++ conversion.
- [ ] Task-0400: `project/projectmanager.cpp` - Currently mechanical move.
- [ ] Task-0600: `timeline2/model/timelinemodel.cpp` - Major DSP/Logic core.

## Audit Checklist for Future Tasks
1. No `#if 0` for class methods.
2. `CapitalCase` for all public/private methods.
3. `lower_underscore` for all member variables.
4. Qt types replaced with U++ (QString -> String, QMap -> VectorMap, etc.).
5. No `Kdenlive` or `Q` prefix in class/namespace names (where possible).
