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
    Upp::String id;
    Upp::String name;
    Upp::String description;
    MFXCategory category;
    bool supports_combination;
    Upp::Vector<Upp::String> parameters;
    
    MFXAlgorithm() : category(FILTER), supports_combination(false) {}
    MFXAlgorithm(const Upp::String& alg_id, const Upp::String& alg_name, MFXCategory cat)
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
    const MFXAlgorithm* GetAlgorithm(const Upp::String& id) const;
    
    // Enumerate algorithms by category
    Upp::Vector<Upp::String> GetAlgorithmsByCategory(MFXCategory category) const;
    
    // Check if algorithm supports combination
    bool SupportsCombination(const Upp::String& id) const;
    
    // Get all available categories
    Upp::Vector<MFXCategory> GetCategories() const;
    
    // Get algorithm metadata
    ValueMap GetMetadata(const Upp::String& id) const;
    
private:
    VectorMap<Upp::String, MFXAlgorithm> algorithms;
};

}

#endif