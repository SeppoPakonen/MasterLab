#ifndef _AudioFX_ParameterSet_h_
#define _AudioFX_ParameterSet_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>

using namespace Upp;

namespace AudioFX {

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
    struct ParameterInfo : Moveable<ParameterInfo> {
        ParameterValue value;
        ParameterValue initial;
        ParameterValue min;
        ParameterValue max;
        ParameterType type;
        String name;
        
        ParameterInfo() : value(0.0), initial(0.0), min(0.0), max(1.0), type(ParameterType::kFloat) {}
        ParameterInfo(ParameterValue v, ParameterValue init, ParameterValue mn, ParameterValue mx, ParameterType t, const String& n)
            : value(v), initial(init), min(mn), max(mx), type(t), name(n) {}
            
        // Support for U++ container operations
        void  operator<<=(const ParameterInfo& s) { 
            value = s.value; initial = s.initial; min = s.min; max = s.max; type = s.type; name = s.name; 
        }
        bool  operator==(const ParameterInfo& b) const { 
            return value == b.value && initial == b.initial && min == b.min && 
                   max == b.max && type == b.type && name == b.name; 
        }
        int   Compare(const ParameterInfo& b) const { return name.Compare(b.name); }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(ParameterInfo& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(JsonIO& jio) {
            int typ = (int)type;
            jio("value", value)("initial", initial)("min", min)("max", max)("type", typ)("name", name);
            type = (ParameterType)typ;
        }
    };

    Upp::VectorMap<ParameterId, ParameterInfo> parameters;

    // Support for U++ container operations
    void  operator<<=(const ParameterSet& s) {
        parameters <<= s.parameters;
    }
    bool  operator==(const ParameterSet& b) const {
        return parameters == b.parameters;
    }
    int   Compare(const ParameterSet& b) const { 
        if (parameters.GetCount() < b.parameters.GetCount()) return -1;
        if (parameters.GetCount() > b.parameters.GetCount()) return 1;
        return 0; // Basic comparison
    }

    // U++ guest requirement
    void  Guest() const {}

    // Support for U++ deep copy
    void  Move(ParameterSet& s) { *this = pick(s); }
    
    // JSON serialization for guest type compatibility
    void Jsonize(JsonIO& jio) {
        jio("parameters", parameters);
    }
};

} // namespace AudioFX

// Register ParameterInfo as a U++ guest type
namespace Upp {
    template<>
    inline constexpr bool is_upp_guest<AudioFX::ParameterSet::ParameterInfo> = true;
}

#endif