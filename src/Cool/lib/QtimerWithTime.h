// Converted from tmp/k/src/lib/qtimerWithTime.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2012 Simon A. Eugster <simon.eu@gmail.com>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_lib_QtimerWithTime_h_
#define _Cool_lib_QtimerWithTime_h_

#include <chrono>

class QTimerWithTime
{
public:
    void Start(int msec);
    int64 Elapsed() const;
    bool IsValid() const;

    // Qt-name compatibility wrappers for phased conversion.
    void start(int msec) { Start(msec); }
    int64 elapsed() const { return Elapsed(); }
    bool isValid() const { return IsValid(); }

private:
    int m_interval_msec{0};
    bool m_is_valid{false};
    std::chrono::steady_clock::time_point m_start_time;
};

#endif
