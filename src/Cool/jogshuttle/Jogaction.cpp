#include "../Cool.h"
#include "Jogaction.h"

// Converted from tmp/k/src/jogshuttle/jogaction.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2010 Pascal Fleury <fleury@users.sourceforge.net>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "jogaction.h"
// #include "core.h"
// #include "monitor/monitormanager.h"

// #include "kdenlive_debug.h"
// #include <KLocalizedString>
// #include <cstdio>
// #include <cstdlib>
// #include <utility>
JogShuttleAction::JogShuttleAction(const JogShuttle *jog_shuttle, QStringList action_map, void *parent)
    : m_jog_shuttle(jog_shuttle)
    , m_action_map(std::move(action_map))
{
    (void)parent;
    // Add action map 0 used for stopping the monitor when the shuttle is in neutral position.
    if (m_action_map.IsEmpty()) {
        m_action_map.Add("monitor_pause");
    }
}

JogShuttleAction::~JogShuttleAction() = default;

void JogShuttleAction::SlotShuttlePos(int shuttle_pos)
{
    slotShuttlePos(shuttle_pos);
}

void JogShuttleAction::slotShuttlePos(int shuttle_pos)
{
    (void)shuttle_pos;
    if (m_action_map.GetCount() > 0) {
        m_last_action = m_action_map[0];
    }
}

void JogShuttleAction::SlotButton(int button_id)
{
    slotButton(button_id);
}

void JogShuttleAction::slotButton(int button_id)
{
    if (button_id < 0 || button_id >= m_action_map.GetCount() || m_action_map[button_id].IsEmpty()) {
        return;
    }
    m_last_action = m_action_map[button_id];
}
