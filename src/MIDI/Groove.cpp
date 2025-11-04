#include "Groove.h"

namespace Midi {

// GrooveExtractor implementation
GrooveExtractor::GrooveExtractor() {
    // Initialize
}

GroovePattern GrooveExtractor::ExtractGroove(const VectorMap<int, int>& midiEvents, int ticksPerBeat) {
    GroovePattern groove;
    groove.resolution = ticksPerBeat;
    
    // Extract timing and velocity information from MIDI events
    Vector<int> offsets;
    Vector<double> velocities;
    
    // For simplicity, just create a basic swing pattern
    // In a real implementation, this would analyze actual performance timing
    for (int i = 0; i < 8; i++) {  // 8th notes in a beat
        if (i % 2 == 1) {  // Odd-numbered 8th notes (2, 4, 6, 8)
            offsets.Add((int)(ticksPerBeat * 0.5 * 1.1));  // Slightly late (swing)
        } else {
            offsets.Add((int)(ticksPerBeat * 0.5 * 0.9));  // Slightly early (swing)
        }
        velocities.Add(0.8 + 0.2 * rand() / RAND_MAX);  // Random velocity between 0.8-1.0
    }
    
    groove.offsets <<= offsets;
    groove.velocities <<= velocities;
    
    return groove;
}

GroovePattern GrooveExtractor::ExtractGrooveFromSequence(const Vector<ValueMap>& noteSequence) {
    GroovePattern groove;
    
    if (noteSequence.GetCount() == 0) {
        return groove;  // Return empty groove
    }
    
    Vector<int> offsets;
    Vector<double> velocities;
    Vector<double> lengths;
    
    // Calculate the timing differences relative to a grid
    for (int i = 0; i < noteSequence.GetCount(); i++) {
        int position = noteSequence[i]["position"];
        double velocity = noteSequence[i]["velocity"];
        int duration = noteSequence[i]["duration"];
        
        // Calculate offset from nearest grid position
        int gridPos = (position / 480) * 480;  // Nearest beat
        int offset = position - gridPos;
        offsets.Add(offset);
        
        velocities.Add(velocity);
        lengths.Add(duration / 480.0);  // Normalize to beats
    }
    
    groove.offsets <<= offsets;
    groove.velocities <<= velocities;
    groove.lengths <<= lengths;
    groove.resolution = 480;
    
    return groove;
}

Vector<ValueMap> GrooveExtractor::ApplyGroove(const Vector<ValueMap>& sequence, const GroovePattern& groove) {
    Vector<ValueMap> result;
    result.SetCount(sequence.GetCount());
    
    for (int i = 0; i < sequence.GetCount(); i++) {
        result[i] = sequence[i];  // Copy each element
    }
    
    for (int i = 0; i < result.GetCount() && i < groove.offsets.GetCount(); i++) {
        int originalPos = result[i].Get("position", 0);
        result[i].Set("position", originalPos + groove.offsets[i]);
        
        if (i < groove.velocities.GetCount()) {
            result[i].Set("velocity", groove.velocities[i]);
        }
    }
    
    return result;
}

Vector<int> GrooveExtractor::CalculateTimingVariations(const Vector<ValueMap>& sequence) {
    Vector<int> variations;
    
    for (const auto& event : sequence) {
        int position = event["position"];
        int gridPos = (position / 480) * 480;  // Snap to beat grid
        int variation = position - gridPos;
        variations.Add(variation);
    }
    
    return variations;
}

Vector<double> GrooveExtractor::CalculateVelocityVariations(const Vector<ValueMap>& sequence) {
    Vector<double> variations;
    
    // Calculate average velocity to use as reference
    double avgVelocity = 0.0;
    for (const auto& event : sequence) {
        avgVelocity += (double)event["velocity"];
    }
    if (sequence.GetCount() > 0) {
        avgVelocity /= sequence.GetCount();
    }
    
    for (const auto& event : sequence) {
        double velocity = event["velocity"];
        variations.Add(velocity / max(0.001, avgVelocity));  // Normalize
    }
    
    return variations;
}

GroovePattern GrooveExtractor::CreateStandardGroove(const String& style) {
    GroovePattern groove;
    groove.name = style;
    groove.resolution = 480;
    
    if (style == "swing") {
        // Classic swing pattern
        groove.swing = 0.6;
        groove.offsets.Add(0);           // 1st 8th note on time
        groove.offsets.Add(480/3);       // 2nd 8th note late (2/3 of beat)
        groove.offsets.Add(480);         // 3rd 8th note on time
        groove.offsets.Add(480 + 480/3); // 4th 8th note late
        
        // Set some velocity variations for swing feel
        groove.velocities.Add(0.9); // Strong beat
        groove.velocities.Add(0.7); // Weak beat
        groove.velocities.Add(0.8); // Medium beat
        groove.velocities.Add(0.6); // Weak beat
    } else if (style == "shuffle") {
        // Shuffle pattern (similar to swing but with triplets)
        groove.swing = 0.65;
        groove.offsets.Add(0);                // 1st triplet note on time
        groove.offsets.Add(480 * 2.0/3.0);    // 2nd triplet note
        groove.offsets.Add(480);              // 3rd triplet note
        
        // Set velocity variations for shuffle feel
        groove.velocities.Add(1.0); // Strong
        groove.velocities.Add(0.6); // Weak
        groove.velocities.Add(0.8); // Medium
    } else {
        // Default straight groove
        groove.swing = 0.0;
        groove.offsets.Add(0);        // On time
        groove.offsets.Add(0);        // On time
        groove.offsets.Add(0);        // On time
        groove.velocities.Add(0.8);
        groove.velocities.Add(0.8);
        groove.velocities.Add(0.8);
    }
    
    return groove;
}

bool GrooveExtractor::LoadGrooveFromFile(const String& filePath, GroovePattern& groove) {
    // In a real implementation, this would load a groove from file
    // For now, return false to indicate not implemented
    return false;
}

bool GrooveExtractor::SaveGrooveToFile(const GroovePattern& groove, const String& filePath) {
    // In a real implementation, this would save a groove to file
    // For now, return false to indicate not implemented
    return false;
}

void GrooveExtractor::NormalizeGroove(GroovePattern& groove) {
    // Normalize groove values to reasonable ranges
    for (int i = 0; i < groove.velocities.GetCount(); i++) {
        groove.velocities[i] = max(0.1, min(1.0, groove.velocities[i]));
    }
}

double GrooveExtractor::CalculateAverageTiming(const Vector<int>& offsets) {
    if (offsets.GetCount() == 0) return 0.0;
    
    double sum = 0.0;
    for (int offset : offsets) {
        sum += abs(offset);
    }
    
    return sum / offsets.GetCount();
}

// PhraseDatabase implementation
PhraseDatabase::PhraseDatabase() {
    // Initialize
}

void PhraseDatabase::AddPhrase(const MusicalPhrase& phrase) {
    phrases.Add(pick(const_cast<MusicalPhrase&>(phrase)));  // Use pick to move instead of copy
    phraseLookup.GetAdd(phrase.id) = phrases.GetCount() - 1;
}

bool PhraseDatabase::RemovePhrase(const String& id) {
    int idx = phraseLookup.Get(id, -1);
    if (idx >= 0 && idx < phrases.GetCount()) {
        phrases.Remove(idx);
        phraseLookup.RemoveKey(id);
        
        // Update lookup table indices
        phraseLookup.Clear();
        for (int i = 0; i < phrases.GetCount(); i++) {
            phraseLookup.GetAdd(phrases[i].id) = i;
        }
        
        return true;
    }
    return false;
}

Vector<MusicalPhrase> PhraseDatabase::FindByCategory(const String& category) const {
    Vector<MusicalPhrase> results;
    
    for (const auto& phrase : phrases) {
        if (phrase.category == category) {
            results.Add(phrase);
        }
    }
    
    return results;
}

Vector<MusicalPhrase> PhraseDatabase::FindByKey(const String& key) const {
    Vector<MusicalPhrase> results;
    
    for (const auto& phrase : phrases) {
        if (phrase.key == key) {
            results.Add(phrase);
        }
    }
    
    return results;
}

Vector<MusicalPhrase> PhraseDatabase::FindByTags(const Vector<String>& tags) const {
    Vector<MusicalPhrase> results;
    
    for (const auto& phrase : phrases) {
        bool matches = false;
        for (const auto& tag : tags) {
            if (phrase.tags.Find(tag) >= 0) {
                matches = true;
                break;
            }
        }
        if (matches) {
            results.Add(phrase);
        }
    }
    
    return results;
}

Vector<MusicalPhrase> PhraseDatabase::FindByStyle(const String& style) const {
    Vector<MusicalPhrase> results;
    
    for (const auto& phrase : phrases) {
        if (phrase.style == style) {
            results.Add(phrase);
        }
    }
    
    return results;
}

Vector<MusicalPhrase> PhraseDatabase::Search(const String& query, const String& category, 
                                            const String& key, const String& style) const {
    Vector<MusicalPhrase> results;
    
    for (const auto& phrase : phrases) {
        if (MatchesSearchCriteria(phrase, query, category, key, style)) {
            results.Add(phrase);
        }
    }
    
    return results;
}

const MusicalPhrase* PhraseDatabase::GetPhraseById(const String& id) const {
    int idx = phraseLookup.Get(id, -1);
    if (idx >= 0 && idx < phrases.GetCount()) {
        return &phrases[idx];
    }
    return nullptr;
}

bool PhraseDatabase::LoadFromFile(const String& filePath) {
    // In a real implementation, this would load phrases from a file
    // For now, return false to indicate not implemented
    return false;
}

bool PhraseDatabase::SaveToFile(const String& filePath) const {
    // In a real implementation, this would save phrases to a file
    // For now, return false to indicate not implemented
    return false;
}

void PhraseDatabase::Clear() {
    phrases.Clear();
    phraseLookup.Clear();
}

bool PhraseDatabase::UpdatePhrase(const MusicalPhrase& phrase) {
    int idx = phraseLookup.Get(phrase.id, -1);
    if (idx >= 0 && idx < phrases.GetCount()) {
        // Create a new phrase with the same content as the original
        MusicalPhrase newPhrase;
        newPhrase.id = phrase.id;
        newPhrase.name = phrase.name;
        newPhrase.category = phrase.category;
        newPhrase.key = phrase.key;
        newPhrase.tempo = phrase.tempo;
        newPhrase.timeSignatureNumerator = phrase.timeSignatureNumerator;
        newPhrase.timeSignatureDenominator = phrase.timeSignatureDenominator;
        
        // Copy vectors element by element
        newPhrase.notes = phrase.notes;
        newPhrase.velocities = phrase.velocities;
        newPhrase.positions = phrase.positions;
        newPhrase.durations = phrase.durations;
        
        newPhrase.tags = phrase.tags;
        newPhrase.style = phrase.style;
        
        phrases[idx] = pick(newPhrase);
        return true;
    }
    return false;
}

bool PhraseDatabase::MatchesSearchCriteria(const MusicalPhrase& phrase, const String& query, 
                                          const String& category, const String& key, const String& style) const {
    // Check category if specified
    if (!category.IsEmpty() && phrase.category != category) {
        return false;
    }
    
    // Check key if specified
    if (!key.IsEmpty() && phrase.key != key) {
        return false;
    }
    
    // Check style if specified
    if (!style.IsEmpty() && phrase.style != style) {
        return false;
    }
    
    // Check query in name, tags, or other fields if specified
    if (!query.IsEmpty()) {
        if (phrase.name.Find(query) < 0 && phrase.tags.Find(query) < 0) {
            return false;
        }
    }
    
    return true;
}

} // namespace Midi