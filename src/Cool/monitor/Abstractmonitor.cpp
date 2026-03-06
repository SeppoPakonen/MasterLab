/*
    SPDX-FileCopyrightText: 2011 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#include "Abstractmonitor.h"
#include "Monitormanager.h"

NAMESPACE_UPP

// --- AbstractRender ---

AbstractRender::AbstractRender(Kdenlive::MonitorId name)
    : id(name)
{
}

// --- AbstractMonitor ---

AbstractMonitor::AbstractMonitor(Kdenlive::MonitorId id, MonitorManager* manager)
    : id(id)
    , monitor_manager(manager)
{
}

END_UPP_NAMESPACE
