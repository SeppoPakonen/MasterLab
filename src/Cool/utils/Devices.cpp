#include "../Cool.h"
#include "Devices.hpp"

// Converted from tmp/k/src/utils/devices.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "devices.hpp"

// #include <QStorageInfo>
// #include <solid/block.h>
// #include <solid/device.h>
// #include <solid/storageaccess.h>
// #include <solid/storagedrive.h>
// #include <solid/storagevolume.h>

bool IsOnRemovableDevice(const String &path)
{
    (void)path;
    // Solid/QStorageInfo integration is deferred in Cool; keep deterministic behavior for now.
    return false;
}
