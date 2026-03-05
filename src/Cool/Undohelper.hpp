// Converted from tmp/k/src/undohelper.hpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_Undohelper_hpp_
#define _Cool_Undohelper_hpp_

// #include <functional>

using Fun = std::function<bool(void)>;

/** @brief this macro executes an operation after a given lambda
 */
#define PUSH_LAMBDA(operation, lambda)                                                                                                                         \
    lambda = [lambda, operation]() {                                                                                                                           \
        bool v = lambda();                                                                                                                                     \
        return v && operation();                                                                                                                               \
    };

/** @brief this macro executes an operation before a given lambda
 */
#define PUSH_FRONT_LAMBDA(operation, lambda)                                                                                                                   \
    lambda = [lambda, operation]() {                                                                                                                           \
        bool v = operation();                                                                                                                                  \
        return v && lambda();                                                                                                                                  \
    };

// #include <QUndoCommand>
using QString = String;

class QUndoCommand {
public:
    explicit QUndoCommand(QUndoCommand *parent = nullptr) { (void)parent; }
    virtual ~QUndoCommand() = default;
    virtual void undo() {}
    virtual void redo() {}
    void setText(const QString& text) { m_text = text; }

private:
    QString m_text;
};

/** @brief this is a generic class that takes fonctors as undo and redo actions. It just executes them when required by Qt
  Note that QUndoStack actually executes redo() when we push the undoCommand to the stack
  This is bad for us because we execute the command as we construct the undo Function. So to prevent it to be executed twice, there is a small hack in this
  command that prevent redoing if it has not been undone before.
 */
class FunctionalUndoCommand : public QUndoCommand
{
public:
    FunctionalUndoCommand(Fun undo, Fun redo, const QString &text, QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    Fun m_undo, m_redo;
    bool m_undone;
};

#endif
