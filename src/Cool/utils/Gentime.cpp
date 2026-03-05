#include "../Cool.h"
#include "Gentime.h"

// Converted from tmp/k/src/utils/gentime.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2002 Jason Wood <jasonwood@blueyonder.co.uk>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "gentime.h"

double GenTime::s_delta = 0.00001;

GenTime::GenTime()
{
    m_time = 0.0;
}

GenTime::GenTime(double seconds)
{
    m_time = seconds;
}

GenTime::GenTime(int frames, double framesPerSecond)
{
    m_time = (double)frames / framesPerSecond;
}

double GenTime::seconds() const
{
    return m_time;
}

double GenTime::ms() const
{
    return m_time * 1000;
}

int GenTime::frames(double framesPerSecond) const
{
    return (int)floor(m_time * framesPerSecond + 0.5);
}

String GenTime::ToString() const
{
    return Format("%.2f s", m_time);
}

GenTime GenTime::operator-()
{
    return GenTime(-m_time);
}

GenTime &GenTime::operator+=(GenTime op)
{
    m_time += op.m_time;
    return *this;
}

GenTime &GenTime::operator-=(GenTime op)
{
    m_time -= op.m_time;
    return *this;
}

GenTime GenTime::operator+(GenTime op) const
{
    return GenTime(m_time + op.m_time);
}

GenTime GenTime::operator-(GenTime op) const
{
    return GenTime(m_time - op.m_time);
}

GenTime GenTime::operator*(double op) const
{
    return GenTime(m_time * op);
}

GenTime GenTime::operator/(double op) const
{
    return GenTime(m_time / op);
}

bool GenTime::operator<(GenTime op) const
{
    return m_time + s_delta < op.m_time;
}

bool GenTime::operator>(GenTime op) const
{
    return m_time > op.m_time + s_delta;
}

bool GenTime::operator>=(GenTime op) const
{
    return m_time + s_delta >= op.m_time;
}

bool GenTime::operator<=(GenTime op) const
{
    return m_time <= op.m_time + s_delta;
}

bool GenTime::operator==(GenTime op) const
{
    return fabs(m_time - op.m_time) < s_delta;
}

bool GenTime::operator!=(GenTime op) const
{
    return fabs(m_time - op.m_time) >= s_delta;
}

// static
void GenTime::setFps(double fps)
{
    s_delta = 0.9 / fps;
}
