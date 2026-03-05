#include "../Cool.h"
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

QIcon UiUtils::RotatedIcon(const QString &icon_name, const QSize icon_size, qreal rotation)
{
    (void)icon_size;
    (void)rotation;
    return icon_name;
}
