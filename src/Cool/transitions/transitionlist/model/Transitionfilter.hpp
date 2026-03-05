// Converted from tmp/k/src/transitions/transitionlist/model/transitionfilter.hpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_transitions_transitionlist_model_Transitionfilter_hpp_
#define _Cool_transitions_transitionlist_model_Transitionfilter_hpp_

namespace AssetListType {
enum class AssetType : int;
}

/** @brief This class is used as a proxy model to filter the effect tree based on given criterion (name, type).
   It simply adds a filter of type
 */
class TransitionFilter {
public:
    TransitionFilter(void *parent = nullptr);

    /** @brief Manage the type filter
       @param enabled whether to enable this filter
       @param type Effect type to display
    */
    void setFilterType(bool enabled, AssetListType::AssetType type);
    void reloadFilterOnFavorite();

    bool m_type_enabled;
    AssetListType::AssetType m_type_value;
};

#endif
