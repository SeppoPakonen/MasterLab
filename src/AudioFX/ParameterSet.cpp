#include "ParameterSet.h"

namespace AudioFX {

ParameterValue ParameterSet::Get(const ParameterId& id) const {
    auto it = parameters.Find(id);
    if (it) {
        return it->value.value;
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
    auto it = parameters.Find(id);
    if (it) {
        // Clamp the value to min/max range
        value = max(it->value.min, min(it->value.max, value));
        it->value.value = value;
        return true;
    }
    return false;
}

bool ParameterSet::SetNormalized(const ParameterId& id, ParameterValue normalizedValue) {
    auto it = parameters.Find(id);
    if (it) {
        // Convert normalized value (0.0 to 1.0) to parameter range
        ParameterValue value = it->value.min + normalizedValue * (it->value.max - it->value.min);
        value = max(it->value.min, min(it->value.max, value));
        it->value.value = value;
        return true;
    }
    return false;
}

ParameterValue ParameterSet::GetNormalized(const ParameterId& id) const {
    auto it = parameters.Find(id);
    if (it) {
        // Convert parameter value to normalized (0.0 to 1.0) range
        if (it->value.max != it->value.min) {
            return (it->value.value - it->value.min) / (it->value.max - it->value.min);
        }
        return 0.0;
    }
    return 0.0;
}

ParameterValue ParameterSet::GetMin(const ParameterId& id) const {
    auto it = parameters.Find(id);
    if (it) {
        return it->value.min;
    }
    return 0.0;
}

ParameterValue ParameterSet::GetMax(const ParameterId& id) const {
    auto it = parameters.Find(id);
    if (it) {
        return it->value.max;
    }
    return 1.0;
}

ParameterType ParameterSet::GetType(const ParameterId& id) const {
    auto it = parameters.Find(id);
    if (it) {
        return it->value.type;
    }
    return ParameterType::kFloat;
}

String ParameterSet::GetName(const ParameterId& id) const {
    auto it = parameters.Find(id);
    if (it) {
        return it->value.name;
    }
    return "";
}

Vector<ParameterId> ParameterSet::GetParameterIds() const {
    Vector<ParameterId> ids;
    for (const auto& param : parameters) {
        ids.Add(param.key);
    }
    return ids;
}

void ParameterSet::ResetToInitial() {
    for (auto& param : parameters) {
        param.value = param.value.initial;
    }
}

ParameterSet::ParameterSet() {
    // Initialize with no parameters
}

} // namespace AudioFX