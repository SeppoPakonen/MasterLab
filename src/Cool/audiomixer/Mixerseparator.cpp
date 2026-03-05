#include "../Cool.h"
#include "Mixerseparator.h"

// Converted from tmp/k/src/audiomixer/mixerseparator.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Kdenlive contributors
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "mixerseparator.h"
// #include <QLinearGradient>
// #include <QPainter>
// #include <QPalette>

MixerSeparator::MixerSeparator()
{
}

QSize MixerSeparator::sizeHint() const
{
    return QSize{1, 10};
}

void MixerSeparator::paintEvent(QPaintEvent *event)
{
    (void)event;
}
