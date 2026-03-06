# Task: VSTConnections U++ Port Fix
# Status: DONE

## Objective
Port `VSTConnections` package controls to valid U++ widgets/APIs (remove Qt-multicolumn-tree assumptions), restore package compileability, and integrate the real converted connections panel into `CuteMainForm` dock tabs.

## Scope
- Fix `src/VSTConnections/VSTConnectionsCtrl.*` API usage that currently prevents package compilation.
- Keep current `Cute` build green while iterating.
- Replace interim `Connections` list tab in `CuteMainForm` with converted `VSTConnections` panel when stable.

## Definition of Done
- [x] `script/build.py -j2 Cute` succeeds with `AudioMaster` using `VSTConnections` package.
- [x] `CuteMainForm` Connections tab uses converted `VSTConnections` control (not interim fallback list).
- [x] task evidence documented in runbook.
