# Task: Dock Panels And Views
# Status: DONE

## Objective
Wire converted Cute panel/view classes into the main skeleton so the workspace reflects qtractor-like panes (files, connections, messages, tracks, timeline).

## Progress
- Integrated converted `CuteTrackView` as the left track pane.
- Integrated converted `CuteFileListView` (audio + midi) into a files tab.
- Added lower tab structure (`Events`, `Messages`, `Files`) to mirror qtractor-style dockable workflow sections.
- Added `Connections` dock tab using converted `VSTConnections::VSTConnectionsCtrl`.
