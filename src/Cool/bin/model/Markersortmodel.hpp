/*
    SPDX-FileCopyrightText: 2022 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_bin_model_MarkerSortModel_h_
#define _Cool_bin_model_MarkerSortModel_h_

#include "../../Definitions.h"

NAMESPACE_UPP

class MarkerListModel;

/** @class MarkerSortModel
    @brief Helper for filtering and sorting marker lists in UI components.
 */
class MarkerSortModel {
public:
    MarkerSortModel();
    virtual ~MarkerSortModel();

    void SetFilterString(const String& filter);
    void SetCategoryFilter(const Vector<int>& categories);
    void ClearFilters();
    
    void SetSortColumn(int column, bool descending = false);

    bool IsAccepted(int frame, const CommentedTime& marker) const;
    const Vector<int>& GetIgnoredSnapPoints() const;

private:
    Vector<int> filter_categories;
    String search_string;
    
    int  sort_column = 0;
    bool sort_descending = false;
    
    mutable Vector<int> ignored_positions;
};

END_UPP_NAMESPACE

#endif
