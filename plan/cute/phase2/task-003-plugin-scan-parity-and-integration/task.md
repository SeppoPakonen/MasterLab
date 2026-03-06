# Task: Plugin Scan Parity And Integration
# Status: DONE

## Objective
Close remaining plugin-scan naming/parity gap from qtractor conversion and verify integration into Cute startup/module wiring.

## Scope
- Confirm mapping from `qtractor_plugin_scan.{h,cpp}` to current Cute equivalents.
- Validate package manifest inclusion and `uses(...)` dependencies.
- Ensure naming follows project conventions (CapitalCase files, no qtractor references).
- Add compatibility shim only where necessary.

## Inputs
- `tmp/q/src/qtractor_plugin_scan.h`
- `tmp/q/src/qtractor_plugin_scan.cpp`
- `src/VSTHost/*`
- `docs/cute-top-level-parity-mapping-2026-03-06.md`

## Definition of Done
- [x] Mapping decision documented in task file or docs.
- [x] Build includes plugin scan units through package manifests.
- [x] No unresolved plugin-scan parity items remain in mapping audit.

## Evidence
- Mapping from source files:
  - `tmp/q/src/qtractor_plugin_scan.h` -> `src/VSTHost/CutePluginScan.h`
  - `tmp/q/src/qtractor_plugin_scan.cpp` -> `src/VSTHost/CutePluginScan.cpp`
- Package wiring:
  - `src/VSTHost/VSTHost.upp` includes `CutePluginScan.h` and `CutePluginScan.cpp`.
  - `src/VSTHost/VSTHost.h` includes `CutePluginScan.h`.
- Mapping audit:
  - `docs/cute-top-level-parity-mapping-2026-03-06.md`
  - `unmapped: 0` for top-level `tmp/q/src/*.{h,cpp}`.
