// Converted from tmp/k/src/utils/uiutils.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Julius Künzel <julius.kuenzel@kde.org>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_utils_Uiutils_h_
#define _Cool_utils_Uiutils_h_

using QString = String;
using QIcon = String;
using qreal = double;
struct QSize {
    int cx{0};
    int cy{0};
};

class UiUtils
{
public:
    /** @returns a rotated version of the icon associated with @param iconName.
     *  It will be of size @param iconSize and @param rotation.
     */
    static QIcon RotatedIcon(const QString &icon_name, const QSize icon_size, qreal rotation = -90);
    static QIcon rotatedIcon(const QString &icon_name, const QSize icon_size, qreal rotation = -90) { return RotatedIcon(icon_name, icon_size, rotation); }
};

#endif
