/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Asseticonprovider.hpp"

NAMESPACE_UPP

VectorMap<String, Image> AssetIconProvider::icon_cache;

AssetIconProvider::AssetIconProvider(bool is_effect)
    : is_effect(is_effect)
{
}

AssetIconProvider::~AssetIconProvider() {
}

Image AssetIconProvider::MakeIcon(const String& name) {
    if (icon_cache.Find(name) >= 0) return icon_cache.Get(name);
    
    Image img = CreateIcon(name);
    icon_cache.Add(name, img);
    return img;
}

Image AssetIconProvider::CreateIcon(const String& name) {
    ImageDraw id(30, 30);
    id.DrawRect(0, 0, 30, 30, White());
    
    // Simple placeholder icon generation
    Color col = Blue();
    if (is_effect) col = Red();
    
    id.DrawEllipse(2, 2, 26, 26, col);
    
    if (!name.IsEmpty()) {
        String label = name.Mid(name.GetLength() - 1);
        Font font = StdFont().Bold().Height(20);
        Size sz = GetTextSize(label, font);
        id.DrawText((30 - sz.cx) / 2, (30 - sz.cy) / 2, label, font, White());
    }
    
    return id;
}

END_UPP_NAMESPACE
