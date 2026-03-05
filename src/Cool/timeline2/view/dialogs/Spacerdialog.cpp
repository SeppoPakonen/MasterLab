#include "../../../Cool.h"
#include "Spacerdialog.h"
#include "../../../utils/Gentime.h"

// Converted from tmp/k/src/timeline2/view/dialogs/spacerdialog.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2008 Jean-Baptiste Mardelle <jb@kdenlive.org>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "spacerdialog.h"

// #include "doc/kthumb.h"
// #include "kdenlivesettings.h"

// #include <QFontDatabase>
// #include <QWheelEvent>

// #include "klocalizedstring.h"

SpacerDialog::SpacerDialog(const GenTime &duration, const Timecode &tc, void *parent)
{
    (void)duration;
    (void)tc;
    (void)parent;
}

GenTime SpacerDialog::selectedDuration() const
{
    return GenTime();
}

bool SpacerDialog::affectAllTracks() const
{
    return m_affect_all_tracks;
}

int SpacerDialog::selectedTrack() const
{
    return m_selected_track;
}
