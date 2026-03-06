# Runbook

## Steps
1. Inventory converted panel classes and compatible parent controls.
2. Replace placeholder panes with converted controls.
3. Verify no regressions in `script/build.py -j2 Cute`.

## Evidence
- Updated `src/AudioMaster/CuteMainForm.h` and `src/AudioMaster/CuteMainForm.cpp`:
  - left pane now uses converted `CuteTrackView`
  - files tab now uses converted `CuteFileListView` for audio/midi lists
  - lower tabbed pane includes Events/Messages/Files/Connections sections
  - Connections tab now uses converted `VSTConnections::VSTConnectionsCtrl`
- Build verification:
  - `script/build.py -j2 Cute`
  - Result: success, linked `bin/Cute`.
- Runtime smoke:
  - `timeout 6 ./bin/Cute` stayed alive for timeout window (no immediate startup crash).
