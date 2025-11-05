#ifndef _MIDI_Groove_h_
#define _MIDI_Groove_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <MIDI/MIDI.h>  // Include the main MIDI package
#include <AudioCore/AudioCore.h>

using namespace Upp;

namespace Midi {

// Structure to represent a groove pattern
struct GroovePattern : public Moveable<GroovePattern> {
    String name;
    String genre;
    Vector<int> offsets;        // Timing offsets in ticks
    Vector<double> velocities;  // Velocity variations
    Vector<double> lengths;     // Note length variations
    int resolution;             // Ticks per beat
    double swing;               // Swing amount (0.0 to 1.0)
    
    GroovePattern() : resolution(480), swing(0.0) {}
};

// Structure to represent a musical phrase
struct MusicalPhrase : public Moveable<MusicalPhrase> {
    String id;
    String name;
    String category;            // "bass", "melody", "chord", "drum", etc.
    String key;                 // Musical key
    double tempo;               // Tempo when recorded
    int timeSignatureNumerator; // Time signature numerator (e.g., 4 in 4/4)
    int timeSignatureDenominator; // Time signature denominator (e.g., 4 in 4/4)
    Vector<int> notes;          // MIDI note numbers
    Vector<int> velocities;     // Note velocities
    Vector<int> positions;      // Note positions in ticks
    Vector<int> durations;      // Note durations in ticks
    String tags;                // Comma-separated tags for search
    String style;               // Style descriptor
    
    MusicalPhrase() : tempo(120.0), timeSignatureNumerator(4), timeSignatureDenominator(4) {}
    
    // Define copy constructor and assignment to make the struct copyable by copying each field
    MusicalPhrase(const MusicalPhrase& other) 
        : id(other.id), name(other.name), category(other.category), key(other.key),
          tempo(other.tempo), timeSignatureNumerator(other.timeSignatureNumerator),
          timeSignatureDenominator(other.timeSignatureDenominator),
          tags(other.tags), style(other.style) {
        // Copy vector contents element by element
        for(int i = 0; i < other.notes.GetCount(); i++) {
            notes.Add(other.notes[i]);
        }
        for(int i = 0; i < other.velocities.GetCount(); i++) {
            velocities.Add(other.velocities[i]);
        }
        for(int i = 0; i < other.positions.GetCount(); i++) {
            positions.Add(other.positions[i]);
        }
        for(int i = 0; i < other.durations.GetCount(); i++) {
            durations.Add(other.durations[i]);
        }
    }
    
    MusicalPhrase& operator=(const MusicalPhrase& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            category = other.category;
            key = other.key;
            tempo = other.tempo;
            timeSignatureNumerator = other.timeSignatureNumerator;
            timeSignatureDenominator = other.timeSignatureDenominator;
            tags = other.tags;
            style = other.style;
            
            // Clear and copy vector contents
            notes.Clear();
            for(int i = 0; i < other.notes.GetCount(); i++) {
                notes.Add(other.notes[i]);
            }
            
            velocities.Clear();
            for(int i = 0; i < other.velocities.GetCount(); i++) {
                velocities.Add(other.velocities[i]);
            }
            
            positions.Clear();
            for(int i = 0; i < other.positions.GetCount(); i++) {
                positions.Add(other.positions[i]);
            }
            
            durations.Clear();
            for(int i = 0; i < other.durations.GetCount(); i++) {
                durations.Add(other.durations[i]);
            }
        }
        return *this;
    }
};

// Groove extractor for analyzing MIDI performance patterns
class GrooveExtractor {
public:
    GrooveExtractor();
    
    // Extract groove from MIDI events
    GroovePattern ExtractGroove(const VectorMap<int, int>& midiEvents, int ticksPerBeat = 480);
    
    // Extract groove from a sequence of note events
    GroovePattern ExtractGrooveFromSequence(const Vector<ValueMap>& noteSequence);
    
    // Apply extracted groove to a sequence
    Vector<ValueMap> ApplyGroove(const Vector<ValueMap>& sequence, const GroovePattern& groove);
    
    // Calculate timing variations from a sequence
    Vector<int> CalculateTimingVariations(const Vector<ValueMap>& sequence);
    
    // Calculate velocity variations from a sequence
    Vector<double> CalculateVelocityVariations(const Vector<ValueMap>& sequence);
    
    // Create a standard groove pattern
    GroovePattern CreateStandardGroove(const String& style);
    
    // Load groove from file
    bool LoadGrooveFromFile(const String& filePath, GroovePattern& groove);
    
    // Save groove to file
    bool SaveGrooveToFile(const GroovePattern& groove, const String& filePath);
    
private:
    // Internal methods
    void NormalizeGroove(GroovePattern& groove);
    double CalculateAverageTiming(const Vector<int>& offsets);
};

// Phrase database for storing and retrieving musical phrases
class PhraseDatabase {
public:
    PhraseDatabase();
    
    // Add a phrase to the database
    void AddPhrase(const MusicalPhrase& phrase);
    
    // Remove a phrase by ID
    bool RemovePhrase(const String& id);
    
    // Find phrases by category
    Vector<MusicalPhrase> FindByCategory(const String& category) const;
    
    // Find phrases by key
    Vector<MusicalPhrase> FindByKey(const String& key) const;
    
    // Find phrases by tags
    Vector<MusicalPhrase> FindByTags(const Vector<String>& tags) const;
    
    // Find phrases by style
    Vector<MusicalPhrase> FindByStyle(const String& style) const;
    
    // Search phrases by multiple criteria
    Vector<MusicalPhrase> Search(const String& query, const String& category = "", 
                                const String& key = "", const String& style = "") const;
    
    // Get all phrases
    const Vector<MusicalPhrase>& GetAllPhrases() const { return phrases; }
    
    // Get phrase by ID
    const MusicalPhrase* GetPhraseById(const String& id) const;
    
    // Load phrases from file
    bool LoadFromFile(const String& filePath);
    
    // Save phrases to file
    bool SaveToFile(const String& filePath) const;
    
    // Get phrase count
    int GetPhraseCount() const { return phrases.GetCount(); }
    
    // Clear all phrases
    void Clear();
    
    // Update an existing phrase
    bool UpdatePhrase(const MusicalPhrase& phrase);
    
private:
    Vector<MusicalPhrase> phrases;
    VectorMap<String, int> phraseLookup;  // ID to index mapping
    
    // Helper method for searching
    bool MatchesSearchCriteria(const MusicalPhrase& phrase, const String& query, 
                              const String& category, const String& key, const String& style) const;
};

} // namespace Midi

#endif