/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_Undohelper_h_
#define _Cool_Undohelper_h_

#include "Cool.h"

NAMESPACE_UPP

typedef std::function<bool(void)> Fun;

/** @brief this macro executes an operation after a given lambda
 */
#define PUSH_LAMBDA(operation, lambda) \
    { \
        auto old_lambda = lambda; \
        lambda = [old_lambda, operation]() { \
            bool v = old_lambda(); \
            return v && operation(); \
        }; \
    }

/** @brief this macro executes an operation before a given lambda
 */
#define PUSH_FRONT_LAMBDA(operation, lambda) \
    { \
        auto old_lambda = lambda; \
        lambda = [old_lambda, operation]() { \
            bool v = operation(); \
            return v && old_lambda(); \
        }; \
    }

/** @class FunctionalUndoCommand
    @brief A generic class that takes functors as undo and redo actions.
 */
class FunctionalUndoCommand : public QUndoCommand {
public:
    FunctionalUndoCommand(Fun undo, Fun redo, const String& text, QUndoCommand* parent = nullptr);
    virtual ~FunctionalUndoCommand();

    virtual void Undo() override;
    virtual void Redo() override;

private:
    Fun  undo_action;
    Fun  redo_action;
    bool undone = false;
};

END_UPP_NAMESPACE

#endif
