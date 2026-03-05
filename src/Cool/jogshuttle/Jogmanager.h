// Converted from tmp/k/src/jogshuttle/jogmanager.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

    This file is part of Kdenlive. See www.kdenlive.org.
*/

#ifndef _Cool_jogshuttle_Jogmanager_h_
#define _Cool_jogshuttle_Jogmanager_h_

using QString = String;

class JogShuttle;
class JogShuttleAction;

/**
 * @class JogManager
 * @brief Turns JogShuttle support on/off according to KdenliveSettings and connects between JogShuttleAction and the actual actions.
 */
class JogManager {
public:
    explicit JogManager(void *parent = nullptr);

private:
    void slotDoAction(const QString &actionName);
    void slotConfigurationChanged();

private:
    JogShuttle *m_shuttle{nullptr};
    JogShuttleAction *m_shuttleAction{nullptr};
};

#endif
