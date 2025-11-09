#include "ParameterSet.h"

namespace AudioFX {

ParameterValue ParameterSet::Get(const ParameterId& id) const {
    const ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        return pInfo->value;
    }
    return 0.0;  // Default value if parameter doesn't exist
}

void ParameterSet::AddParameter(const ParameterId& id, ParameterValue initial,
                                ParameterValue min, ParameterValue max,
                                ParameterType type, const String& name) {
    ParameterInfo info;
    info.value = initial;
    info.initial = initial;
    info.min = min;
    info.max = max;
    info.type = type;
    info.name = name;
    parameters.GetAdd(id) = info;
}

bool ParameterSet::Set(const ParameterId& id, ParameterValue value) {
    ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        // Clamp the value to min/max range
        value = max(pInfo->min, min(pInfo->max, value));
        pInfo->value = value;
        return true;
    }
    return false;
}

bool ParameterSet::SetNormalized(const ParameterId& id, ParameterValue normalizedValue) {
    ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        // Convert normalized value (0.0 to 1.0) to parameter range
        ParameterValue value = pInfo->min + normalizedValue * (pInfo->max - pInfo->min);
        value = max(pInfo->min, min(pInfo->max, value));
        pInfo->value = value;
        return true;
    }
    return false;
}

ParameterValue ParameterSet::GetNormalized(const ParameterId& id) const {
    const ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        // Convert parameter value to normalized (0.0 to 1.0) range
        if (pInfo->max != pInfo->min) {
            return (pInfo->value - pInfo->min) / (pInfo->max - pInfo->min);
        }
        return 0.0;
    }
    return 0.0;
}

ParameterValue ParameterSet::GetMin(const ParameterId& id) const {
    const ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        return pInfo->min;
    }
    return 0.0;
}

ParameterValue ParameterSet::GetMax(const ParameterId& id) const {
    const ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        return pInfo->max;
    }
    return 1.0;
}

ParameterType ParameterSet::GetType(const ParameterId& id) const {
    const ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        return pInfo->type;
    }
    return ParameterType::kFloat;
}

String ParameterSet::GetName(const ParameterId& id) const {
    const ParameterInfo* pInfo = parameters.FindPtr(id);
    if (pInfo) {
        return pInfo->name;
    }
    return "";
}

Vector<ParameterId> ParameterSet::GetParameterIds() const {
    Vector<ParameterId> ids;
    for(int i = 0; i < parameters.GetCount(); i++) {
        ids.Add(parameters.GetKey(i));
    }
    return ids;
}

void ParameterSet::ResetToInitial() {
    for(int i = 0; i < parameters.GetCount(); i++) {
        ParameterInfo& info = parameters[i];
        info.value = info.initial;
    }
}

ParameterSet::ParameterSet() {
    // Initialize with no parameters
}

} // namespace AudioFX