/*
    SPDX-FileCopyrightText: 2002 Jason Wood <jasonwood@blueyonder.co.uk>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_utils_Gentime_h_
#define _Cool_utils_Gentime_h_

#include "../Cool.h"

NAMESPACE_UPP

class GenTime {
public:
    GenTime();
    explicit GenTime(double seconds);
    GenTime(int frames, double frames_per_second);

    double Seconds() const;
    double Ms() const;
    int    Frames(double frames_per_second) const;

    String ToString() const;

    GenTime operator-();
    GenTime& operator+=(GenTime op);
    GenTime& operator-=(GenTime op);
    GenTime operator+(GenTime op) const;
    GenTime operator-(GenTime op) const;
    GenTime operator*(double op) const;
    GenTime operator/(double op) const;

    bool operator<(GenTime op) const;
    bool operator>(GenTime op) const;
    bool operator>=(GenTime op) const;
    bool operator<=(GenTime op) const;
    bool operator==(GenTime op) const;
    bool operator!=(GenTime op) const;

    static void SetFps(double fps);

private:
    double time; // seconds
    static double delta;
};

END_UPP_NAMESPACE

#endif
