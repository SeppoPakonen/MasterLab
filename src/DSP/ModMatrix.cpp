#include "ModMatrix.h"

namespace DSP {

ModMatrix::ModMatrix() {
}

ModMatrix::~ModMatrix() {
}

void ModMatrix::AddSource(const ModSource& source) {
    sources.GetAdd(source.name) = source;
}

void ModMatrix::AddDestination(const ModDestination& destination) {
    destinations.GetAdd(destination.name) = destination;
}

void ModMatrix::Connect(const String& source, const String& destination, double depth, double offset) {
    connections.Add(ModConnection(source, destination, depth, offset));
}

void ModMatrix::ComputeConnections() {
    // Process all connections and apply modulation
    for (const auto& conn : connections) {
        int src_idx = sources.Find(conn.source);
        int dst_idx = destinations.Find(conn.destination);
        
        if (src_idx >= 0 && dst_idx >= 0) {
            const ModSource& src = sources[src_idx];
            ModDestination& dst = destinations[dst_idx];
            
            // Calculate modulated value
            double modulated_value = src.value * conn.depth + conn.offset;
            
            // Apply to target with bounds checking
            if (dst.target) {
                double clamped_value = max(dst.min_value, min(dst.max_value, modulated_value));
                *dst.target = clamped_value;
            }
        }
    }
}

void ModMatrix::SetSourceValue(const String& source, double value) {
    int idx = sources.Find(source);
    if (idx >= 0) {
        sources[idx].value = max(sources[idx].min_value, min(sources[idx].max_value, value));
    }
}

double ModMatrix::GetSourceValue(const String& source) const {
    int idx = sources.Find(source);
    if (idx >= 0) {
        return sources[idx].value;
    }
    return 0.0;
}

}