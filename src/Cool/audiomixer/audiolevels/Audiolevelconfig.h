// Converted from tmp/k/src/audiomixer/audiolevels/audiolevelconfig.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Kdenlive contributors
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_audiomixer_audiolevels_Audiolevelconfig_h_
#define _Cool_audiomixer_audiolevels_Audiolevelconfig_h_

#include "Audioleveltypes.h"
// #include <KConfigGroup>
// #include <KSharedConfig>
// #include <QColor>

class AudioLevelConfig
{
public:
    struct Config
    {
        AudioLevel::LevelStyle levelStyle = AudioLevel::LevelStyle::Solid;
        bool drawBlockLines = true;
        AudioLevel::PeakIndicatorStyle peakIndicatorStyle = AudioLevel::PeakIndicatorStyle::Colorful;
    };

    static AudioLevelConfig &instance();

    // Getters
    AudioLevel::LevelStyle levelStyle() const { return m_config.levelStyle; }
    bool drawBlockLines() const { return m_config.drawBlockLines; }
    AudioLevel::PeakIndicatorStyle peakIndicatorStyle() const { return m_config.peakIndicatorStyle; }

    // Setters
    void setLevelStyle(AudioLevel::LevelStyle style);
    void setDrawBlockLines(bool draw);
    void setPeakIndicatorStyle(AudioLevel::PeakIndicatorStyle style);

    // Signal for configuration changes
    void configChanged();

private:
    AudioLevelConfig(); // Private constructor for singleton
    void readConfig();
    void writeConfig();

    Config m_config;
};

#endif
