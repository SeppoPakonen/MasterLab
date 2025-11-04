#ifndef _AudioFX_ParameterSet_h_
#define _AudioFX_ParameterSet_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>

using namespace Upp;

namespace DSP {

using ParameterId = String;
using ParameterValue = double;

// Enum for parameter value types
enum class ParameterType {
    kFloat,
    kInt,
    kBool,
    kString
};

// Parameter set for managing plugin/device parameters
class ParameterSet {
public:
    ParameterSet();
    
    // Add a parameter with initial value and constraints
    void AddParameter(const ParameterId& id, ParameterValue initial, 
                      ParameterValue min = 0.0, ParameterValue max = 1.0,
                      ParameterType type = ParameterType::kFloat,
                      const String& name = "");
    
    // Get/set parameter values
    ParameterValue Get(const ParameterId& id) const;
    bool Set(const ParameterId& id, ParameterValue value);
    bool SetNormalized(const ParameterId& id, ParameterValue normalizedValue);
    ParameterValue GetNormalized(const ParameterId& id) const;
    
    // Get parameter info
    ParameterValue GetMin(const ParameterId& id) const;
    ParameterValue GetMax(const ParameterId& id) const;
    ParameterType GetType(const ParameterId& id) const;
    String GetName(const ParameterId& id) const;
    
    // Get all parameter IDs
    Vector<ParameterId> GetParameterIds() const;
    
    // Reset to initial values
    void ResetToInitial();
    
private:
    struct ParameterInfo {
        ParameterValue value;
        ParameterValue initial;
        ParameterValue min;
        ParameterValue max;
        ParameterType type;
        String name;
    };
    
    HashMap<ParameterId, ParameterInfo> parameters;
};

} // namespace DSP

#endif