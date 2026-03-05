# Conversion Note: `timeline2/view/qml/GuidesMenu.qml`

## Source
- `tmp/k/src/timeline2/view/qml/GuidesMenu.qml`

## Target
- `src/Cool/timeline2/view/qml/GuidesMenuConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
/*
    SPDX-FileCopyrightText: 2019 Jean-Baptiste Mardelle
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Menu {
    id: menuRoot
    property alias menuModel: itemRepeater.model
    signal guideSelected(int assetFrame)

    Instantiator {
        id: itemRepeater
        onObjectAdded: menuRoot.insertItem( index, object )
        onObjectRemoved: menuRoot.removeItem( object )
        delegate: MenuItem {
            id: menuItem
            text: model.comment
            property int assetFrame: model.frame
            onTriggered: {
                menuRoot.guideSelected(menuItem.assetFrame)
            }
        }
    }
}

```
