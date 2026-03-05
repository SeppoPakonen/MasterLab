// Converted from tmp/k/src/monitor/view/qmliconprovider.hpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2026 Jean-Baptiste Mardelle
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_monitor_view_Qmliconprovider_hpp_
#define _Cool_monitor_view_Qmliconprovider_hpp_

class QObject {};
using QString = String;
struct QSize {
    int w{0};
    int h{0};
    QSize() = default;
    QSize(int w, int h) : w(w), h(h) {}
    int width() const { return w; }
    int height() const { return h; }
};
struct QPixmap {};
class QQuickImageProvider {
public:
    enum ImageType { Pixmap };
    explicit QQuickImageProvider(ImageType) {}
    virtual ~QQuickImageProvider() = default;
};

/** @class QmlIconProvider
    @brief Provides icon pixmap from the icon name to Qml
 */
class QmlIconProvider : public QQuickImageProvider
{
public:
    explicit QmlIconProvider(QSize iconSize, QObject *parent);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    QSize m_defaultSize;
};

#endif
