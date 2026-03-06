/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Undohelper.hpp"

NAMESPACE_UPP

FunctionalUndoCommand::FunctionalUndoCommand(Fun undo, Fun redo, const String& text, QUndoCommand* parent)
    : QUndoCommand(parent)
    , undo_action(std::move(undo))
    , redo_action(std::move(redo))
{
    setText(text);
}

FunctionalUndoCommand::~FunctionalUndoCommand() {
}

void FunctionalUndoCommand::Undo() {
    undone = true;
    bool res = undo_action();
    ASSERT(res);
}

void FunctionalUndoCommand::Redo() {
    if (undone) {
        bool res = redo_action();
        ASSERT(res);
    }
}

END_UPP_NAMESPACE
