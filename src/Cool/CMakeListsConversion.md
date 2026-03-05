# kdenlive `src/CMakeLists.txt` Conversion Notes

## Source
- Original file: `tmp/k/src/CMakeLists.txt`
- Phase: Cool phase 1
- Intent: convert CMake/Qt build inventory into U++ assembly planning without compile work.

## What The Original File Does
- Detects MLT runtime paths and generates `mlt_config.h`.
- Conditionally enables jog shuttle sources based on Linux input headers.
- Pulls many source subdirectories (`abstractmodel`, `assets`, `timeline2`, `render`, `monitor`, `widgets`, `xml`, etc.).
- Defines top-level sources (`core.cpp`, `definitions.cpp`, `mainwindow.cpp`, `undohelper.cpp`, `filefilter.cpp`, etc.).
- Builds static library `kdenliveLib` plus executable `kdenlive`.
- Registers logging category and optional DBus adaptor.
- Adds large QML/UI/resource inventories.
- Links to KDE Frameworks, Qt modules, MLT, FFmpeg, KDDockWidgets, and optional platform libraries.

## U++ Interpretation For Cool
- `src/Cool` is the assembly anchor replacing this CMake target graph in phase 2.
- Phase 1 converts each `tmp/k/src/*` source artifact manually; no target wiring yet.
- Converted outputs can initially land under `src/Cool` while preserving class/function surface.
- In phase 2, code can be split into internal packages once dependency seams are clear.

## Planned Cool Assembly Shape (Phase 2)
Expected root files:
- `src/Cool/Cool.upp`
- `src/Cool/Cool.h`
- `src/Cool/main.cpp`

Expected responsibilities:
- Define `uses(...)` closure for converted packages.
- Replace Qt/CMake source aggregation with U++ package manifests.
- Provide startup path for the Cool executable (and optional helper tools if needed).

## Source Coverage Reference
- See `plan/cool/phase1/BACKLOG.md` for per-file conversion task index.
- Current phase-1 scope from `tmp/k/src`: 808 tasks.

## QML/UI/Resource Translation Notes
- Qt `.ui` and QML artifacts should be translated into U++ controls/layouts or kept as conversion notes when no immediate 1:1 mapping is practical in phase 1.
- Resource collections (`*.qrc`) become asset-manifest notes first; runtime packaging is phase-2 work.

## Dependency Translation Notes
Original link graph includes:
- KDE Frameworks modules
- Qt Quick/Widgets/Multimedia stack
- MLT + FFmpeg + platform optional libs

Cool phase-2 should convert this into:
- explicit U++ package `uses(...)`
- optional external wrapper packages for runtime/media backends
- build flags handled in assembly/build scripts instead of generated CMake headers

## Manifest Notes For Later
When `Cool.upp` is introduced in phase 2:
- list `AGENTS.md` first
- include `Cool.h`, `main.cpp`, and phase-level conversion notes
- keep package boundaries explicit instead of reproducing one giant target list
