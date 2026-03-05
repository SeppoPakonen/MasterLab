# Conversion Note: `timeline2/view/qml/MixShape.qml`

## Source
- `tmp/k/src/timeline2/view/qml/MixShape.qml`

## Target
- `src/Cool/timeline2/view/qml/MixShapeConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2020 Jean-Baptiste Mardelle <jb@kdenlive.org>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

import QtQuick 2.15
import QtQuick.Shapes 1.15

Shape {
    anchors.fill: parent
    asynchronous: true
    opacity: 0.4
    ShapePath {
        fillColor: "#AAFFFFFF"
        strokeColor: "transparent"
        PathLine {x: 0; y: 0}
        PathLine {x: mixBackground.width; y: mixBackground.height}
        PathLine {x: 0; y: mixBackground.height}
        PathLine {x: 0; y: 0}
    }
    /*ShapePath {
        fillColor: "#66FFFFFF"
        strokeColor: "transparent"
        PathLine {x: mixBackground.width; y: 0}
        PathLine {x: mixBackground.width; y: mixBackground.height}
        PathLine {x: 0; y: mixBackground.height}
        PathLine {x: mixBackground.width; y: 0}
    }*/
}

```
