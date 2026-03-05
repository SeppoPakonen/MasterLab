#include "../Cool.h"
#include "Thememanager.h"

// Converted from tmp/k/src/utils/thememanager.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2016 Zhigalin Alexander <alexander@zhigalin.tk>

    SPDX-License-Identifier: LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

// Qt includes

// #include "thememanager.h"
// #include "core.h"

// #include <QFileInfo>
// #include <QMenu>
// #include <QModelIndex>
// #include <QStringList>

// #include <KActionMenu>
// #include <KColorSchemeMenu>
// #include <KColorSchemeModel>
// #include <KConfigGroup>
// #include <KLocalizedString>
// #include <KSharedConfig>

ThemeManager::ThemeManager(void *parent)
{
    (void)parent;
    m_menu = nullptr;
}

QString ThemeManager::loadScheme(const QString &schemeName)
{
    return schemeName;
}

void ThemeManager::switchDarkPalette(bool dark)
{
    (void)dark;
}

QString ThemeManager::loadCurrentPath() const
{
    return String();
}

void ThemeManager::saveCurrentScheme(const QString &path)
{
    (void)path;
}

QString ThemeManager::currentSchemeName() const
{
    return String();
}

void ThemeManager::schemeActionTriggered(void *action)
{
    (void)action;
}

void ThemeManager::themeChanged(const QString &name)
{
    (void)name;
}
