# Conversion Note: `monitor/view/OverlayLabel.qml`

## Source
- `tmp/k/src/monitor/view/OverlayLabel.qml`

## Target
- `src/Cool/monitor/view/OverlayLabelConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2025 Kdenlive Contributors
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.15

Item {
    id: overlayLabel
    property alias text: label.text
    property color backgroundColor: Qt.rgba(0, 0, 0, 0.5)
    property color textColor: "white"
    property int padding: 6
    property alias font: label.font
    property bool flipText: false
    width: label.width + 2 * padding
    height: label.height + padding

    Rectangle {
        anchors.fill: parent
        color: overlayLabel.backgroundColor
        radius: 4
    }
    Text {
        id: label
        anchors.centerIn: parent
        color: overlayLabel.textColor
        font.bold: true
        text: ""
        rotation: overlayLabel.flipText ? 180 : 0
    }
} 
```
