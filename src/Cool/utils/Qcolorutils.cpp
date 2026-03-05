#include "../Cool.h"
#include "Qcolorutils.h"

// Converted from tmp/k/src/utils/qcolorutils.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2010 Till Theato <root@ttill.de>
    SPDX-FileCopyrightText: 2017 Dušan Hanuš <hanus@pixelhouse.cz>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

QColor QColorUtils::stringToColor(QString str_color)
{
    return QColor(str_color);
}

QString QColorUtils::colorToString(const QColor &color, bool alpha)
{
    String out;
    out << Format("0x%02x%02x%02x", color.red(), color.green(), color.blue());
    if (alpha) {
        out << Format("%02x", color.alpha());
    } else {
        out << "ff";
    }
    return out;
}

QColor QColorUtils::complementary(QColor color)
{
    return color;
}

NegQColor::NegQColor() = default;

NegQColor NegQColor::fromHsvF(qreal h, qreal s, qreal l, qreal a)
{
    (void)h;
    (void)s;
    (void)l;
    (void)a;
    return NegQColor();
}

QDebug operator<<(QDebug qd, const NegQColor &color)
{
    (void)color;
    return qd.maybeSpace();
}

bool NegQColor::operator==(const NegQColor &other) const
{
    return other.sign_r == sign_r && other.sign_g == sign_g && other.sign_b == sign_b;
}

bool NegQColor::operator!=(const NegQColor &other) const
{
    return !(*this == other);
}

NegQColor NegQColor::fromRgbF(qreal r, qreal g, qreal b, qreal a)
{
    (void)r;
    (void)g;
    (void)b;
    (void)a;
    return NegQColor();
}

qreal NegQColor::redF() const
{
    return 0.0;
}

void NegQColor::setRedF(qreal val)
{
    (void)val;
}

qreal NegQColor::greenF() const
{
    return 0.0;
}

void NegQColor::setGreenF(qreal val)
{
    (void)val;
}

qreal NegQColor::blueF() const
{
    return 0.0;
}

void NegQColor::setBlueF(qreal val)
{
    (void)val;
}

void NegQColor::setValueF(qreal val)
{
    (void)val;
}

qreal NegQColor::valueF() const
{
    return 0.0;
}

int NegQColor::hue() const
{
    return 0;
}

qreal NegQColor::hueF() const
{
    return 0.0;
}

qreal NegQColor::saturationF() const
{
    return 0.0;
}
