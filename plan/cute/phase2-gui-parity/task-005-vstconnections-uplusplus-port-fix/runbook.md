# Runbook

## Steps
1. Replace invalid `TreeCtrl` multi-column calls with U++-compatible control structure.
2. Rebuild package and resolve compile errors incrementally.
3. Reconnect `AudioMaster` to `VSTConnections` and wire into `CuteMainForm`.

## Evidence
- Port/fix work completed in `src/VSTConnections`:
  - Removed duplicate local `CuteBus` class definitions from:
    - `src/VSTConnections/CuteConnections.cpp`
    - `src/VSTConnections/CuteBusForm.cpp`
  - Replaced invalid `CtrlLayout(*this, ...)` usage in `src/VSTConnections/VSTConnections.cpp` (`ParentCtrl` wrapper) with direct `Add(connectionsCtrl.SizePos())`.
  - Earlier in this task thread, `VSTConnectionsCtrl` was ported from invalid Qt-style tree API assumptions to U++ control usage and package manifest was aligned.
- Integration in `AudioMaster`:
  - `CuteMainForm` lower dock tabs now use real `VSTConnections::VSTConnectionsCtrl` in the `Connections` tab.
- Build verification:
  - Command: `script/build.py -j2 Cute`
  - Result: success; `bin/Cute` linked.
- Runtime smoke:
  - Command: `timeout 6 ./bin/Cute`
  - Result: process remained alive for timeout window (`EXIT:124`), indicating no immediate startup crash; GTK/GDK warnings still present and tracked separately.
