// Converted from tmp/k/src/audiomixer/mixerseparator.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Kdenlive contributors
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_audiomixer_Mixerseparator_h_
#define _Cool_audiomixer_Mixerseparator_h_

struct QPaintEvent;
struct QSize {
    int cx{0};
    int cy{0};
};

class MixerSeparator
{
public:
    MixerSeparator();

    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
};

#endif
