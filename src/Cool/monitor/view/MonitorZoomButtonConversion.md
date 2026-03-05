# Conversion Note: `monitor/view/MonitorZoomButton.qml`

## Source
- `tmp/k/src/monitor/view/MonitorZoomButton.qml`

## Target
- `src/Cool/monitor/view/MonitorZoomButtonConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2022 Julius Künzel <julius.kuenzel@kde.org>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

import org.kde.kdenlive as Kdenlive

Kdenlive.MonitorToolButton {
    iconName: "zoom"
    toolTipText: i18n("Zoom")
    property bool menuVisible: zoomContextMenu.visible
    onClicked: {
        if (zoomContextMenu.visible) {
            zoomContextMenu.close()
        } else {
            zoomContextMenu.open()
        }
    }
    Popup {
        id: zoomContextMenu
        x: parent.x - width
        padding: 0
        margins: 0
        onAboutToHide: {
            if (!barZone.containsMouse) {
                scenetoolbar.opacity = 0
            }
        }

        ColumnLayout {
            spacing: 0
            anchors.fill: parent
            Kdenlive.MonitorToolButton {
                iconName: "zoom-in"
                toolTipText: i18n("Zoom In")
                onClicked: {
                    controller.activateClipMonitor(root.isClipMonitor)
                    controller.triggerAction('monitor_zoomin')
                }
            }
            Kdenlive.MonitorToolButton {
                iconName: "zoom-out"
                toolTipText: i18n("Zoom Out")
                onClicked: {
                    controller.activateClipMonitor(root.isClipMonitor)
                    controller.triggerAction('monitor_zoomout')
                }
            }
            Kdenlive.MonitorToolButton {
                iconName: "zoom-original"
                toolTipText: i18n("Reset Zoom")
                onClicked: {
                    controller.activateClipMonitor(root.isClipMonitor)
                    controller.triggerAction('monitor_zoomreset')
                }
            }
        }
    }
}

```
