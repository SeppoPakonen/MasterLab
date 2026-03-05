// Converted from tmp/k/src/utils/qcolorutils.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Dušan Hanuš <hanus@pixelhouse.cz>
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_utils_Qcolorutils_h_
#define _Cool_utils_Qcolorutils_h_

// #include <QDebug>
// #include <QtGlobal>
// #include <QColor>

using QString = String;
using qreal = double;

class QDebug {
public:
    QDebug& maybeSpace() { return *this; }
};

class QColor {
public:
    QColor() = default;
    explicit QColor(const QString& value) : text_value(value) {}

    int red() const { return red_value; }
    int green() const { return green_value; }
    int blue() const { return blue_value; }
    int alpha() const { return alpha_value; }
    qreal redF() const { return red_value / 255.0; }
    qreal greenF() const { return green_value / 255.0; }
    qreal blueF() const { return blue_value / 255.0; }
    qreal valueF() const { return blueF(); }
    int hue() const { return 0; }
    qreal hueF() const { return 0.0; }
    qreal saturationF() const { return 0.0; }

    void setRgb(int r, int g, int b, int a) { red_value = r; green_value = g; blue_value = b; alpha_value = a; }
    void setRedF(qreal) {}
    void setGreenF(qreal) {}
    void setBlueF(qreal) {}
    void setHsv(int, int, int) {}

    int hsvHue() const { return 0; }
    int hsvSaturation() const { return 0; }
    int value() const { return 0; }

    static QColor fromString(const QString& value) { return QColor(value); }
    static QColor fromHsvF(qreal, qreal, qreal, qreal = 1.0) { return QColor(); }
    static QColor fromRgbF(qreal, qreal, qreal, qreal = 1.0) { return QColor(); }
    QColor toHsv() const { return *this; }

private:
    QString text_value;
    int red_value = 0;
    int green_value = 0;
    int blue_value = 0;
    int alpha_value = 255;
};

class QColorUtils
{
public:
    static QColor stringToColor(QString strColor);
    static QString colorToString(const QColor &color, bool alpha);
    static QColor complementary(QColor color);
};

class NegQColor
{
public:
    NegQColor();
    int8_t sign_r = 1;
    int8_t sign_g = 1;
    int8_t sign_b = 1;
    QColor qcolor;
    static NegQColor fromHsvF(qreal h, qreal s, qreal l, qreal a = 1.0);
    static NegQColor fromRgbF(qreal r, qreal g, qreal b, qreal a = 1.0);
    qreal redF() const;
    void setRedF(qreal val);
    qreal greenF() const;
    void setGreenF(qreal val);
    qreal blueF() const;
    void setBlueF(qreal val);
    qreal valueF() const;
    void setValueF(qreal val);
    int hue() const;
    qreal hueF() const;
    qreal saturationF() const;
    /** @brief overload of comparison operators */
    bool operator==(const NegQColor &other) const;
    bool operator!=(const NegQColor &other) const;
};

QDebug operator<<(QDebug qd, const NegQColor &color);

#endif
