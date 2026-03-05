// Converted from tmp/k/src/effects/effectstack/view/abstractcollapsiblewidget.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2012 Jean-Baptiste Mardelle <jb@kdenlive.org>

SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_effects_effectstack_view_Abstractcollapsiblewidget_h_
#define _Cool_effects_effectstack_view_Abstractcollapsiblewidget_h_

class AbstractCollapsibleWidget
{
public:
    AbstractCollapsibleWidget();
    virtual ~AbstractCollapsibleWidget() = default;

    virtual bool IsGroup() const = 0;
    bool isGroup() const { return IsGroup(); }
};

#endif
