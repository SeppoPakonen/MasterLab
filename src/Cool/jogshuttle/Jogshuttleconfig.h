// Converted from tmp/k/src/jogshuttle/jogshuttleconfig.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2012 Jean-Baptiste Mardelle <jb@kdenlive.org>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_jogshuttle_Jogshuttleconfig_h_
#define _Cool_jogshuttle_Jogshuttleconfig_h_

using QString = String;
using QStringList = Vector<String>;

class JogShuttleConfig {
public:
    static QStringList ActionMap(const QString &action_map);
    static QString ActionMap(const QStringList &action_map);

    // Compatibility wrappers.
    static QStringList actionMap(const QString &action_map) { return ActionMap(action_map); }
    static QString actionMap(const QStringList &action_map) { return ActionMap(action_map); }
};

#endif
