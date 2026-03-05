#include "../../../Cool.h"
#include "Transitionfilter.hpp"

// Converted from tmp/k/src/transitions/transitionlist/model/transitionfilter.cpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// #include "transitionfilter.hpp"
// #include "abstractmodel/treeitem.hpp"
// #include "assets/assetlist/model/assettreemodel.hpp"

TransitionFilter::TransitionFilter(void *parent)
{
    (void)parent;
    m_type_enabled = false;
    m_type_value = static_cast<AssetListType::AssetType>(0);
}

void TransitionFilter::setFilterType(bool enabled, AssetListType::AssetType type)
{
    m_type_enabled = enabled;
    m_type_value = type;
}

void TransitionFilter::reloadFilterOnFavorite()
{
    // No-op in placeholder phase.
}
