/*
    SPDX-FileCopyrightText: 2022 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#include "Markersortmodel.hpp"
#include "Markerlistmodel.hpp"

NAMESPACE_UPP

MarkerSortModel::MarkerSortModel() {
}

MarkerSortModel::~MarkerSortModel() {
}

void MarkerSortModel::SetFilterString(const String& filter) {
    search_string = filter;
}

void MarkerSortModel::SetCategoryFilter(const Vector<int>& categories) {
    filter_categories <<= categories;
}

void MarkerSortModel::ClearFilters() {
    search_string.Clear();
    filter_categories.Clear();
}

void MarkerSortModel::SetSortColumn(int column, bool descending) {
    sort_column = column;
    sort_descending = descending;
}

bool MarkerSortModel::IsAccepted(int frame, const CommentedTime& marker) const {
    if (!filter_categories.IsEmpty()) {
        // bool found = false;
        // for(int cat : filter_categories) if(cat == marker.GetType()) found = true;
        // if(!found) { ignored_positions.Add(frame); return false; }
    }
    
    if (!search_string.IsEmpty()) {
        if (marker.GetComment().Find(search_string) < 0) {
            ignored_positions.Add(frame);
            return false;
        }
    }
    
    return true;
}

Vector<int> MarkerSortModel::GetIgnoredSnapPoints() const {
    return ignored_positions;
}

END_UPP_NAMESPACE
