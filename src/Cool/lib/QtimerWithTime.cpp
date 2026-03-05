#include "../Cool.h"
#include "QtimerWithTime.h"

// Converted from tmp/k/src/lib/qtimerWithTime.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2012 Simon A. Eugster <simon.eu@gmail.com>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "qtimerWithTime.h"

void QTimerWithTime::Start(int msec)
{
    m_interval_msec = msec;
    m_start_time = std::chrono::steady_clock::now();
    m_is_valid = true;
}

int64 QTimerWithTime::Elapsed() const
{
    if (!m_is_valid) {
        return 0;
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_start_time).count();
}

bool QTimerWithTime::IsValid() const
{
    return m_is_valid;
}
