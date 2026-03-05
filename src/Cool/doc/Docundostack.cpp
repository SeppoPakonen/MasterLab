#include "../Cool.h"
#include "Docundostack.hpp"

// Converted from tmp/k/src/doc/docundostack.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "docundostack.hpp"
// #include <QUndoCommand>
// #include <QUndoGroup>

DocUndoStack::DocUndoStack(QUndoGroup *parent)
{
    (void)parent;
}

// TODO: custom undostack everywhere do that
void DocUndoStack::push(QUndoCommand *cmd)
{
    (void)cmd;
    if (index() < count()) {
        m_count = index();
    }
    ++m_count;
    m_index = m_count;
}
