#include "../Cool.h"
#include "Colortools.h"

// Converted from tmp/k/src/utils/colortools.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2010 Simon Andreas Eugster <simon.eu@gmail.com>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

ColorTools::ColorTools(QObject *parent)
    : QObject(parent)
{
}

QImage ColorTools::yuvColorWheel(const QSize &size, int Y, float scaling, bool modifiedVersion, bool circleOnly)
{
    (void)Y;
    (void)scaling;
    (void)modifiedVersion;
    (void)circleOnly;
    return QImage(size);
}

QImage ColorTools::yuvVerticalPlane(const QSize &size, int angle, float scaling)
{
    (void)angle;
    (void)scaling;
    return QImage(size);
}

QImage ColorTools::rgbCurvePlane(const QSize &size, const ColorTools::ColorsRGB &color, float scaling, const QRgb &background)
{
    (void)color;
    (void)scaling;
    (void)background;
    return QImage(size);
}

QImage ColorTools::rgbCurveLine(const QSize &size, const ColorTools::ColorsRGB &color, const QRgb &background)
{
    (void)color;
    (void)background;
    return QImage(size);
}

QImage ColorTools::yPbPrColorWheel(const QSize &size, int Y, float scaling, bool circleOnly)
{
    (void)Y;
    (void)scaling;
    (void)circleOnly;
    return QImage(size);
}

QImage ColorTools::hsvHueShiftPlane(const QSize &size, int S, int V, int MIN, int MAX)
{
    (void)S;
    (void)V;
    (void)MIN;
    (void)MAX;
    return QImage(size);
}

QImage ColorTools::hsvCurvePlane(const QSize &size, const QColor &baseColor, const ComponentsHSV &xVariant, const ComponentsHSV &yVariant, bool shear, const float offsetY)
{
    (void)baseColor;
    (void)xVariant;
    (void)yVariant;
    (void)shear;
    (void)offsetY;
    return QImage(size);
}

QImage ColorTools::FixedColorCircle(const QSize &size, QRgb color)
{
    (void)color;
    return QImage(size);
}
