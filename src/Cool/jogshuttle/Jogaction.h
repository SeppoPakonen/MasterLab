// Converted from tmp/k/src/jogshuttle/jogaction.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2010 Pascal Fleury <fleury@users.sourceforge.net>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_jogshuttle_Jogaction_h_
#define _Cool_jogshuttle_Jogaction_h_

using QString = String;
using QStringList = Vector<String>;

class JogShuttle;

class JogShuttleAction
{
public:
    explicit JogShuttleAction(const JogShuttle *jog_shuttle, QStringList action_map, void *parent = nullptr);
    ~JogShuttleAction();

private:
    const JogShuttle *m_jog_shuttle;
    // this is indexed by button ID, having QString() for any non-used ones.
    QStringList m_action_map;
    QString m_last_action;

public:
    void SlotShuttlePos(int);
    void SlotButton(int);
    void slotShuttlePos(int);
    void slotButton(int);
    const QString& lastAction() const { return m_last_action; }
};

#endif
