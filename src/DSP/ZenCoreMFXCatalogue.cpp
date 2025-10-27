#include "ZenCoreMFXCatalogue.h"

namespace DSP {

ZenCoreMFXCatalogue::ZenCoreMFXCatalogue() {
}

ZenCoreMFXCatalogue::~ZenCoreMFXCatalogue() {
}

void ZenCoreMFXCatalogue::RegisterAlgorithm(const MFXAlgorithm& algorithm) {
    // Since MFXAlgorithm contains Vector members that can't be copied,
    // we'll use a different approach - create a new one and assign fields individually
    MFXAlgorithm& alg = algorithms.GetAdd(algorithm.id);
    alg.id = algorithm.id;
    alg.name = algorithm.name;
    alg.description = algorithm.description;
    alg.category = algorithm.category;
    alg.supports_combination = algorithm.supports_combination;
    alg.parameters <<= algorithm.parameters;
}

const MFXAlgorithm* ZenCoreMFXCatalogue::GetAlgorithm(const String& id) const {
    int idx = algorithms.Find(id);
    if (idx >= 0) {
        return &algorithms[idx];
    }
    return nullptr;
}

Vector<String> ZenCoreMFXCatalogue::GetAlgorithmsByCategory(MFXCategory category) const {
    Vector<String> result;
    for (int i = 0; i < algorithms.GetCount(); i++) {
        if (algorithms[i].category == category) {
            result.Add(algorithms.GetKey(i));
        }
    }
    return result;
}

bool ZenCoreMFXCatalogue::SupportsCombination(const String& id) const {
    int idx = algorithms.Find(id);
    if (idx >= 0) {
        return algorithms[idx].supports_combination;
    }
    return false;
}

Vector<MFXCategory> ZenCoreMFXCatalogue::GetCategories() const {
    Vector<MFXCategory> categories;
    Vector<bool> seen_category(9, false); // Assuming 9 categories based on enum
    
    for (int i = 0; i < algorithms.GetCount(); i++) {
        MFXCategory cat = algorithms[i].category;
        if (!seen_category[cat]) {
            categories.Add(cat);
            seen_category[cat] = true;
        }
    }
    return categories;
}

ValueMap ZenCoreMFXCatalogue::GetMetadata(const String& id) const {
    ValueMap metadata;
    int idx = algorithms.Find(id);
    if (idx >= 0) {
        const MFXAlgorithm& alg = algorithms[idx];
        metadata.Set("id", alg.id);
        metadata.Set("name", alg.name);
        metadata.Set("description", alg.description);
        metadata.Set("category", (int)alg.category);
        metadata.Set("supports_combination", alg.supports_combination);
        
        ValueArray params;
        for (const String& param : alg.parameters) {
            params.Add(param);
        }
        metadata.Set("parameters", params);
    }
    return metadata;
}

}