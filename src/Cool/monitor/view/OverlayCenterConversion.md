# Conversion Note: `monitor/view/OverlayCenter.qml`

## Source
- `tmp/k/src/monitor/view/OverlayCenter.qml`

## Target
- `src/Cool/monitor/view/OverlayCenterConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2020 Jean-Baptiste Mardelle <jb@kdenlive.org>
    SPDX-FileCopyrightText: 2018 Willian Pessoa
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.15

Item {
    id: overlay
    property color color
    Rectangle {
        color: overlay.color
        width: parent.width
        height: 1
        anchors.centerIn: parent
    }
    Rectangle {
        color: overlay.color
        height: parent.height
        width: 1
        anchors.centerIn: parent
    }
}

```
