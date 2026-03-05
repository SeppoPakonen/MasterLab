// Converted from tmp/k/src/timeline2/view/qml/timelinetriangle.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2015-2016 Meltytech LLC
    SPDX-FileCopyrightText: 2019 Jean-Baptiste Mardelle <jb@kdenlive.org>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
#ifndef _Cool_timeline2_view_qml_Timelinetriangle_h_
#define _Cool_timeline2_view_qml_Timelinetriangle_h_

struct QQuickItem;
struct QPainter;
#ifndef _Cool_qml_QColor_placeholder_
#define _Cool_qml_QColor_placeholder_
struct QColor {
    int r{255};
    int g{255};
    int b{255};
    int a{255};
};
#endif

class TimelineTriangle {
public:
    TimelineTriangle(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);
    void curveChanged();

private:
    QColor m_color;
    int m_curveType{0};
    bool m_endFade{false};

};

#endif
