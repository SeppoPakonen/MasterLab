# Conversion Note: `monitor/view/MonitorToolButton.qml`

## Source
- `tmp/k/src/monitor/view/MonitorToolButton.qml`

## Target
- `src/Cool/monitor/view/MonitorToolButtonConversion.md`

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


ToolButton {
    id: toolButton
    property alias iconName: toolButton.icon.name
    property string toolTipText
    width: parent.width
    height: width
    focusPolicy: Qt.NoFocus
    onPressed: {
        root.captureRightClick = true
    }
    onReleased: {
        root.captureRightClick = false
    }
    ToolTip {
        visible: toolButton.hovered
        delay: Qt.styleHints.mousePressAndHoldInterval
        text: toolButton.toolTipText
        timeout: 3000
    }
}

```
