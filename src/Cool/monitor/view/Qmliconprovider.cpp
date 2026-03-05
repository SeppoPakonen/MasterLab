#include "../../Cool.h"
#include "Qmliconprovider.hpp"

// Converted from tmp/k/src/monitor/view/qmliconprovider.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2026 Jean-Baptiste Mardelle
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "qmliconprovider.hpp"

// #include <QDebug>
// #include <QIcon>
// #include <QStyle>

QmlIconProvider::QmlIconProvider(QSize iconSize, QObject *parent)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , m_defaultSize(iconSize)
{
    (void)parent;
}

QPixmap QmlIconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    (void)id;
    if (size) {
        *size = m_defaultSize;
    }
    (void)requestedSize;
    return QPixmap();
}
