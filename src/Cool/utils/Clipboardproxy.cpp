#include "../Cool.h"
#include "Clipboardproxy.hpp"

// Converted from tmp/k/src/utils/clipboardproxy.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2018 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "clipboardproxy.hpp"
// #include <QClipboard>
// #include <QGuiApplication>
// #include <QMimeData>

Vector<String> ClipboardProxy::MimeTypes() const
{
    return {};
}
