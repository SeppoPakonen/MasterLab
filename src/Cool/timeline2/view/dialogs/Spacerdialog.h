// Converted from tmp/k/src/timeline2/view/dialogs/spacerdialog.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2008 Jean-Baptiste Mardelle <jb@kdenlive.org>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_timeline2_view_dialogs_Spacerdialog_h_
#define _Cool_timeline2_view_dialogs_Spacerdialog_h_

class GenTime;
class Timecode;

/** @class SpacerDialog
    @brief A dialog to specify length and track of inserted space.
    @author Jean-Baptiste Mardelle
 */
class SpacerDialog
{
public:
    SpacerDialog(const GenTime &duration, const Timecode &tc, void *parent = nullptr);
    GenTime selectedDuration() const;
    int selectedTrack() const;
    bool affectAllTracks() const;

private:
    bool m_affect_all_tracks{false};
    int m_selected_track{0};
};

#endif
