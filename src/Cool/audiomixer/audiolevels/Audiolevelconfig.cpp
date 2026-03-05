#include "../../Cool.h"
#include "Audiolevelconfig.h"

// Converted from tmp/k/src/audiomixer/audiolevels/audiolevelconfig.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Kdenlive contributors
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "audiolevelconfig.h"
// #include "core.h"

AudioLevelConfig &AudioLevelConfig::instance()
{
    static AudioLevelConfig instance;
    return instance;
}

AudioLevelConfig::AudioLevelConfig()
{
    readConfig();
}

void AudioLevelConfig::readConfig()
{
    // Placeholder in-memory defaults for phase-1 conversion.
    m_config.levelStyle = AudioLevel::LevelStyle::Gradient;
    m_config.drawBlockLines = false;
    m_config.peakIndicatorStyle = AudioLevel::PeakIndicatorStyle::Monochrome;
}

void AudioLevelConfig::writeConfig()
{
    // No persistent backend in phase-1 placeholder.
}

void AudioLevelConfig::setLevelStyle(AudioLevel::LevelStyle style)
{
    if (m_config.levelStyle != style) {
        m_config.levelStyle = style;
        writeConfig();
        configChanged();
    }
}

void AudioLevelConfig::setDrawBlockLines(bool draw)
{
    if (m_config.drawBlockLines != draw) {
        m_config.drawBlockLines = draw;
        writeConfig();
        configChanged();
    }
}

void AudioLevelConfig::setPeakIndicatorStyle(AudioLevel::PeakIndicatorStyle style)
{
    if (m_config.peakIndicatorStyle != style) {
        m_config.peakIndicatorStyle = style;
        writeConfig();
        configChanged();
    }
}

void AudioLevelConfig::configChanged()
{
    // Notification wiring is deferred to later integration phase.
}
