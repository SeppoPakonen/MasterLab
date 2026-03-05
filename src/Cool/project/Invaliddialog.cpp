#include "../Cool.h"
#include "Invaliddialog.h"

// Converted from tmp/k/src/project/invaliddialog.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    SPDX-FileCopyrightText: 2013 Jean-Nicolas Artaud <jeannicolasartaud@gmail.com>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// Self
// #include "invaliddialog.h"

// Qt
// #include <QLabel>
// #include <QListWidget>
// #include <QVBoxLayout>

// KDE
// #include <QDialogButtonBox>
// #include <QPushButton>

InvalidDialog::InvalidDialog(const QString &caption, const QString &message, bool info_only, void *parent)
{
    (void)caption;
    (void)message;
    (void)info_only;
    (void)parent;
}

InvalidDialog::~InvalidDialog()
{
}

void InvalidDialog::addClip(const QString &id, const QString &path)
{
    m_ids.Add(id);
    m_paths.Add(path);
}

QStringList InvalidDialog::getIds() const
{
    return clone(m_ids);
}
