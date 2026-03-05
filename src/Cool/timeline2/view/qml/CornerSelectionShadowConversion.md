# Conversion Note: `timeline2/view/qml/CornerSelectionShadow.qml`

## Source
- `tmp/k/src/timeline2/view/qml/CornerSelectionShadow.qml`

## Target
- `src/Cool/timeline2/view/qml/CornerSelectionShadowConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2015 Meltytech LLC
    SPDX-FileCopyrightText: 2015 Harald Hvaal <harald.hvaal@gmail.com>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.15

Item {
    id: root

    property Item clip
    property bool mirrorGradient: false

    width: 100
    height: clip ? clip.height : 0
    Behavior on opacity { NumberAnimation { duration: 100 } }

    Rectangle {
        id: shadowGradient
        width: parent.height
        height: parent.width
        anchors.centerIn: parent
        rotation: mirrorGradient ? -90 : 90
        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 1.0; color: "white" }
        }
        PulsingAnimation {
            target: shadowGradient
            running: root.opacity
        }
    }
}

```
