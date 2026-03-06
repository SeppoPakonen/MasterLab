# Cool Conversion Backlog

## Status Summary
- **Phase 1 (Manual Conversion)**: RESTARTED. Auditing all mechanical moves.
- **Phase 2 (Compilation)**: PAUSED. Blocked until genuine conversion of core headers is complete.
- **Phase 3 (Expansion)**: PENDING.

## Core System - Genuinely Converted (SETTING THE STANDARD)
- [x] Task-0178: `core.cpp` -> `Core.cpp`
- [x] Task-0179: `core.h` -> `Core.h`
- [x] Task-0230: `mltconnection.cpp` -> `Mltconnection.cpp`
- [x] Task-0231: `mltconnection.h` -> `Mltconnection.h`
- [x] Task-0220: `mainwindow.cpp` -> `Mainwindow.cpp`
- [x] Task-0221: `mainwindow.h` -> `Mainwindow.h`
- [x] Task-0050: `bin/bin.cpp` -> `Bin.cpp`
- [x] Task-0051: `bin/bin.h` -> `Bin.h`
- [x] Task-0400: `project/projectmanager.cpp` -> `Projectmanager.cpp`
- [x] Task-0401: `project/projectmanager.h` -> `Projectmanager.h`
- [x] Task-0100: `doc/kdenlivedoc.cpp` -> `Kdenlivedoc.cpp`
- [x] Task-0101: `doc/kdenlivedoc.h` -> `Kdenlivedoc.h`
- [x] Task-0060: `bin/projectitemmodel.cpp` -> `Projectitemmodel.cpp`
- [x] Task-0061: `bin/projectitemmodel.h` -> `Projectitemmodel.h`
- [x] Task-0300: `audiomixer/mixermanager.cpp` -> `Mixermanager.cpp`
- [x] Task-0301: `audiomixer/mixermanager.hpp` -> `Mixermanager.hpp`
- [x] Task-0003: `abstractmodel/abstracttreemodel.hpp` -> `Abstracttreemodel.hpp`
- [x] Task-0005: `abstractmodel/treeitem.hpp` -> `Treeitem.hpp`
- [x] Task-0200: `jobs/taskmanager.h` -> `Taskmanager.h`
- [x] Task-0201: `jobs/abstracttask.h` -> `Abstracttask.h`

## High Priority - Pending Genuine Conversion (RESTART REQUIRED)
- [ ] Task-0800: `utils/timecode.h` - Essential utility.
- [ ] Task-0801: `utils/timecode.cpp` - Essential utility.
- [ ] Task-0600: `timeline2/model/timelinemodel.cpp` - Major DSP/Logic core.
- [ ] Task-0601: `timeline2/model/timelinemodel.hpp` - Currently partial.
- [ ] Task-0610: `timeline2/model/trackmodel.hpp`
- [ ] Task-0620: `timeline2/model/clipmodel.hpp`

## Audit Checklist for Future Tasks
1. No `#if 0` for class methods.
2. `CapitalCase` for all public/private methods.
3. `lower_underscore` for all member variables.
4. Qt types replaced with U++ (QString -> String, QMap -> VectorMap, etc.).
5. No `Kdenlive` or `Q` prefix in class/namespace names (where possible).
