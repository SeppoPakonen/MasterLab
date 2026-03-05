#include "Cool.h"
#include "Undohelper.hpp"

// Converted from tmp/k/src/undohelper.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "undohelper.hpp"
#ifdef CRASH_AUTO_TEST
// #include "logger.hpp"
#endif
// #include <QDebug>
// #include <QTime>
// #include <utility>
FunctionalUndoCommand::FunctionalUndoCommand(Fun undo, Fun redo, const QString &text, QUndoCommand *parent)
    : QUndoCommand(parent)
    , m_undo(std::move(undo))
    , m_redo(std::move(redo))
    , m_undone(false)
{
    setText(text);
}

void FunctionalUndoCommand::undo()
{
#ifdef CRASH_AUTO_TEST
    Logger::log_undo(true);
#endif
    m_undone = true;
    bool res = m_undo();
    ASSERT(res);
    QUndoCommand::undo();
}

void FunctionalUndoCommand::redo()
{
    if (m_undone) {
#ifdef CRASH_AUTO_TEST
        Logger::log_undo(false);
#endif
        bool res = m_redo();
        ASSERT(res);
    }
    QUndoCommand::redo();
}
