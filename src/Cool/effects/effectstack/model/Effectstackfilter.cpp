#include "../../../Cool.h"
#include "Effectstackfilter.hpp"

// Converted from tmp/k/src/effects/effectstack/model/effectstackfilter.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2024 Jean-Baptiste Mardelle
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "effectstackfilter.hpp"
// #include "effectitemmodel.hpp"
// #include "effectstackmodel.hpp"

EffectStackFilter::EffectStackFilter(void *parent)
{
    (void)parent;
}

bool EffectStackFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    (void)sourceRow;
    (void)sourceParent;
    return true;
}

bool EffectStackFilter::isVisible(const QModelIndex &sourceIndex)
{
    return filterAcceptsRow(sourceIndex.row(), QModelIndex{});
}
