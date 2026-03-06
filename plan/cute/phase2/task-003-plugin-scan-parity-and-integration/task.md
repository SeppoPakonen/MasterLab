# Task: Plugin Scan Parity And Integration
# Status: TODO

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
- [ ] Mapping decision documented in task file or docs.
- [ ] Build includes plugin scan units through package manifests.
- [ ] No unresolved plugin-scan parity items remain in mapping audit.
