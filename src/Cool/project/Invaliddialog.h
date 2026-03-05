// Converted from tmp/k/src/project/invaliddialog.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    SPDX-FileCopyrightText: 2013 Jean-Nicolas Artaud <jeannicolasartaud@gmail.com>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_project_Invaliddialog_h_
#define _Cool_project_Invaliddialog_h_

using QString = String;
using QStringList = Vector<String>;

class InvalidDialog {
public:
    explicit InvalidDialog(const QString &caption, const QString &message, bool info_only, void *parent = nullptr);
    ~InvalidDialog();

    void addClip(const QString &id, const QString &path);
    QStringList getIds() const;

private:
    Vector<String> m_ids;
    Vector<String> m_paths;
};

#endif
