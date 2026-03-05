#include "../Cool.h"
#include "Jogshuttleconfig.h"

// Converted from tmp/k/src/jogshuttle/jogshuttleconfig.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2010 Pascal Fleury <fleury@users.sourceforge.net>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "jogshuttleconfig.h"

// #include <cstdio>
// #include <sstream>
// #include <string>
// #include <vector>

// #include <cstdlib>

static const char DELIMITER = ';';
static const char KEY_VALUE_SEP = '=';
static const char *BUTTON_PREFIX = "button";

QStringList JogShuttleConfig::ActionMap(const QString &actions_config)
{
    QStringList action_map;
    const QStringList mappings = Split(actions_config, DELIMITER);

    for (const String &mapping : mappings) {
        Vector<String> parts = Split(mapping, KEY_VALUE_SEP);
        if (parts.GetCount() != 2) {
            RLOG("Invalid button configuration: " << mapping);
            continue;
        }
        String key = parts[0];
        if (key.StartsWith(BUTTON_PREFIX)) {
            key = key.Mid(6);
        }
        int button_id = ScanInt(key);
        while (action_map.GetCount() <= button_id) {
            action_map.Add(String());
        }
        action_map[button_id] = parts[1];
    }
    return action_map;
}

QString JogShuttleConfig::ActionMap(const QStringList &action_map)
{
    QStringList mappings;
    for (int i = 0; i < action_map.GetCount(); ++i) {
        if (action_map[i].IsEmpty()) {
            continue;
        }
        mappings.Add(Format("%s%d%c%s", BUTTON_PREFIX, i, KEY_VALUE_SEP, action_map[i].Begin()));
    }
    return Join(mappings, ";");
}
