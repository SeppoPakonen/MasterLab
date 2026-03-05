# Conversion Note: `monitor/view/OverlayMinimal.qml`

## Source
- `tmp/k/src/monitor/view/OverlayMinimal.qml`

## Target
- `src/Cool/monitor/view/OverlayMinimalConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2018 Jean-Baptiste Mardelle <jb@kdenlive.org>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.15

Item {
    id: overlay
    property color color

    Rectangle {
        color: overlay.color
        width: frame.width / 20
        height: 1
        anchors.centerIn: parent
    }
    Rectangle {
        color: overlay.color
        height: frame.width / 20
        width: 1
        anchors.centerIn: parent
    }
}

```
