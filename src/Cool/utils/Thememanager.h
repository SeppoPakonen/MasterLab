// Converted from tmp/k/src/utils/thememanager.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2016 Zhigalin Alexander <alexander@zhigalin.tk>

    SPDX-License-Identifier: LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef _Cool_utils_Thememanager_h_
#define _Cool_utils_Thememanager_h_

// Qt includes

// #include <QAction>
// #include <QtGlobal>

// KDE includes
// #include <KColorSchemeManager>

using QString = String;

class KActionMenu {};

class ThemeManager {
public:
    ThemeManager(void *parent);
    KActionMenu *menu() { return m_menu; };

    void switchDarkPalette(bool dark);
    void themeChanged(const QString &name);

private:
    void schemeActionTriggered(void *action);

    KActionMenu *m_menu;

    QString loadCurrentScheme() const;
    QString loadCurrentPath() const;
    void saveCurrentScheme(const QString & path);
    QString currentSchemeName() const;
    QString loadScheme(const QString &schemeName);
};

#endif
