#include "../Cool.h"
#if 0
#include "Uiutils.h"

// Converted from tmp/k/src/utils/uiutils.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Julius Künzel <julius.kuenzel@kde.org>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "uiutils.h"

// #include <QIcon>
// #include <QPixmap>

QIcon UiUtils::rotatedIcon(const QString &iconName, const QSize iconSize, qreal rotation)
{
    QIcon icon = QIcon::fromTheme(iconName);
    QPixmap pix = icon.pixmap(iconSize);
    QTransform trans;
    trans.rotate(rotation);
    pix = pix.transformed(trans);
    return QIcon(pix);
}
#endif
