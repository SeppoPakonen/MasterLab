// Converted from tmp/k/src/doc/docundostack.hpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_doc_Docundostack_hpp_
#define _Cool_doc_Docundostack_hpp_

class QUndoGroup;
class QUndoCommand;

class DocUndoStack {
public:
    explicit DocUndoStack(QUndoGroup *parent = nullptr);
    void push(QUndoCommand *cmd);

    int index() const { return m_index; }
    int count() const { return m_count; }

private:
    int m_index{0};
    int m_count{0};
};

#endif
