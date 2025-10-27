#ifndef _DSP_ZenCoreMFXCatalogue_h_
#define _DSP_ZenCoreMFXCatalogue_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

enum MFXCategory {
    FILTER,
    EQ,
    DYNAMICS,
    MODULATION,
    DELAY,
    REVERB,
    SPECIAL,
    PITCH,
    SPATIAL
};

struct MFXAlgorithm : public Moveable<MFXAlgorithm> {
    String id;
    String name;
    String description;
    MFXCategory category;
    bool supports_combination;
    Vector<String> parameters;
    
    MFXAlgorithm() : category(FILTER), supports_combination(false) {}
    MFXAlgorithm(const String& alg_id, const String& alg_name, MFXCategory cat)
        : id(alg_id), name(alg_name), category(cat), supports_combination(true) {}
};

class ZenCoreMFXCatalogue {
public:
    typedef ZenCoreMFXCatalogue CLASSNAME;
    
    ZenCoreMFXCatalogue();
    virtual ~ZenCoreMFXCatalogue();
    
    // Register an MFX algorithm
    void RegisterAlgorithm(const MFXAlgorithm& algorithm);
    
    // Get algorithm by ID
    const MFXAlgorithm* GetAlgorithm(const String& id) const;
    
    // Enumerate algorithms by category
    Vector<String> GetAlgorithmsByCategory(MFXCategory category) const;
    
    // Check if algorithm supports combination
    bool SupportsCombination(const String& id) const;
    
    // Get all available categories
    Vector<MFXCategory> GetCategories() const;
    
    // Get algorithm metadata
    ValueMap GetMetadata(const String& id) const;
    
private:
    VectorMap<String, MFXAlgorithm> algorithms;
};

}

#endif