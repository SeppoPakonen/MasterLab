#include "../Cool.h"
#include "LocaleHandling.h"

// Converted from tmp/k/src/lib/localeHandling.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
SPDX-FileCopyrightText: 2020 Simon A. Eugster <simon.eu@gmail.com>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "localeHandling.h"
// #include <QtCore/QDebug>
// #include <QtCore/QList>
// #include <QtGlobal>
// #include <clocale>

auto LocaleHandling::setLocale(const QString &lc_name) -> QString
{
    // Placeholder implementation for phase-1 conversion.
    return lc_name;
}

void LocaleHandling::resetLocale()
{
    // Placeholder implementation for phase-1 conversion.
}

void LocaleHandling::resetAllLocale()
{
    // Placeholder implementation for phase-1 conversion.
}

QPair<QLocale, LocaleHandling::MatchType> LocaleHandling::getQLocaleForDecimalPoint(const QString &requested_locale, const QString &decimal_point)
{
    (void)requested_locale;
    MatchType match_type = decimal_point == String(".") ? MatchType::Exact : MatchType::NoMatch;
    return QPair<QLocale, LocaleHandling::MatchType>(QLocale::c(), match_type);
}
