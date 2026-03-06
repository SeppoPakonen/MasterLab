/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Assetfilter.hpp"
#include "../../abstractmodel/Treeitem.hpp"

NAMESPACE_UPP

AssetFilter::AssetFilter() {
}

AssetFilter::~AssetFilter() {
}

void AssetFilter::SetFilterName(bool enabled, const String& pattern) {
    name_enabled = enabled;
    name_value = pattern;
}

void AssetFilter::SetIncludeList(bool enabled) {
    include_list_enabled = enabled;
}

bool AssetFilter::IsVisible(const std::shared_ptr<TreeItem>& item) const {
    if (include_list_enabled) {
        // TODO: Check include list property from item
    }
    return ApplyAll(item);
}

bool AssetFilter::FilterName(const std::shared_ptr<TreeItem>& item) const {
    if (!name_enabled || name_value.IsEmpty()) return true;
    
    // String name = item->GetName(); // Assuming TreeItem has GetName
    // String normalized_name = NormalizeText(name);
    // String normalized_pattern = NormalizeText(name_value);
    
    // return normalized_name.Find(normalized_pattern) >= 0;
    return true;
}

String AssetFilter::NormalizeText(const String& text) {
    String res;
    for(int i = 0; i < text.GetCount(); i++) {
        int c = text[i];
        if (IsAlNum(c) || IsSpace(c)) res.Cat(c);
    }
    return res;
}

bool AssetFilter::ApplyAll(std::shared_ptr<TreeItem> item) const {
    return FilterName(item);
}

END_UPP_NAMESPACE
