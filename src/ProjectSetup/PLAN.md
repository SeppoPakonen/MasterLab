# ProjectSetup Plan

## Short-Term Tasks
1. Attach dialog to `AudioMaster::MainWindow::OnProjectSetup` so it opens from the Project menu.
2. Wire `SetModel` with real project metadata (start time, length, frame rate, etc.).
3. Implement `ProjectSetupValidator` to sanity-check offsets, timecode values, and sample rate/bit-depth combinations.
4. Provide `WhenApply` callback so controller can persist settings to `ProjectMgmt::Project` and update transport immediately.

## Medium-Term
- Add preset management (store/load project setup snapshots).
- Integrate help button with documentation viewer.
- Enable live preview mode where changing display format updates rulers while dialog remains open.

## Long-Term
- Support multi-sample-rate workflows by exposing additional conversion policies.
- Surface warnings when selected frame rate conflicts with imported video assets.
