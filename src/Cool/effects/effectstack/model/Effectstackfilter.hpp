// Converted from tmp/k/src/effects/effectstack/model/effectstackfilter.hpp
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2024 Jean-Baptiste Mardelle
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef _Cool_effects_effectstack_model_Effectstackfilter_hpp_
#define _Cool_effects_effectstack_model_Effectstackfilter_hpp_

struct QModelIndex {
    int row_{0};
    int row() const { return row_; }
};

/** @brief This class is used as a proxy model to filter the profile tree based on given criterion (fps, interlaced,...)
 */
class EffectStackFilter {
public:
    EffectStackFilter(void *parent = nullptr);

    /** @brief Returns true if the ModelIndex in the source model is visible after filtering
     */
    bool isVisible(const QModelIndex &sourceIndex);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
};

#endif
