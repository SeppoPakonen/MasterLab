// Converted from tmp/k/src/utils/clipboardproxy.hpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2018 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_utils_Clipboardproxy_hpp_
#define _Cool_utils_Clipboardproxy_hpp_

/** @class ClipboardProxy
    @brief Provides an interface to the clipboard, to use directly from QML
    Inspired by https://stackoverflow.com/questions/40092352/passing-qclipboard-to-qml
 */
class ClipboardProxy
{
public:
    ClipboardProxy() = default;
    Vector<String> MimeTypes() const;
};

#endif
