#include "../Cool.h"
#include "Jogmanager.h"
#include "Jogaction.h"

// Converted from tmp/k/src/jogshuttle/jogmanager.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

    This file is part of Kdenlive. See www.kdenlive.org.
*/

// #include "jogmanager.h"
// #include "core.h"
// #include "jogaction.h"
// #include "jogshuttle.h"
// #include "jogshuttleconfig.h"
// #include "kdenlivesettings.h"
// #include "mainwindow.h"

JogManager::JogManager(void *parent)
{
    (void)parent;
    slotConfigurationChanged();
}

void JogManager::slotConfigurationChanged()
{
    m_shuttleAction = nullptr;
    m_shuttle = nullptr;

    // Device wiring is deferred for phase-2 integration.
}

void JogManager::slotDoAction(const QString &actionName)
{
    (void)actionName;
}
