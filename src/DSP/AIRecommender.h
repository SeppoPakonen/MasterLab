#ifndef _DSP_AIRecommender_h_
#define _DSP_AIRecommender_h_

#include <Core/Core.h>
#include <MIDI/MIDI.h>  // For MIDI data structures
#include <AudioCore/AudioCore.h>

using namespace Upp;

namespace DSP {

// AIRecommender - provides AI-powered recommendations for audio processing
class AIRecommender {
public:
    typedef AIRecommender CLASSNAME;
    
    AIRecommender();
    virtual ~AIRecommender();
    
    // Recommendation types
    enum RecommendationType {
        EFFECT_SUGGESTION,     // Suggests which effects to use
        PARAMETER_ADVICE,      // Advises on parameter settings
        PATCH_COMBINATION,     // Suggests patch combinations
        INSTRUMENT_MATCH,      // Matches instruments to musical context
        GENRE_STYLE,          // Recommends genre-specific settings
        TECHNIQUE_SUGGESTION  // Suggests playing/recording techniques
    };
    
    // Structure for holding recommendations
    struct Recommendation : public Moveable<Recommendation> {
        String id;
        String name;
        RecommendationType type;
        double confidence;  // 0.0 to 1.0
        String description;
        ValueMap attributes;  // Specific attributes for the recommendation
        Vector<String> related_items;  // Related items that go with this recommendation
        
        Recommendation() : type(EFFECT_SUGGESTION), confidence(0.5) {}
    };
    
    // Generate recommendations based on input audio
    Vector<Recommendation> GenerateAudioRecommendations(const Vector<double>& audio_buffer, 
                                                       const String& context = "");
    
    // Generate recommendations based on MIDI data
    Vector<Recommendation> GenerateMidiRecommendations(const Vector<MidiEvent>& midi_events, 
                                                      const String& context = "");
    
    // Generate recommendations based on project context
    Vector<Recommendation> GenerateContextualRecommendations(const ValueMap& project_context);
    
    // Train the AI model (simplified for this implementation)
    void TrainModel(const Vector<ValueMap>& training_data);
    
    // Set user preferences to influence recommendations
    void SetUserPreferences(const ValueMap& preferences);
    
    // Get current user preferences
    const ValueMap& GetUserPreferences() const { return user_preferences; }
    
    // Enable/disable learning from user interactions
    void SetLearningEnabled(bool enabled) { learning_enabled = enabled; }
    bool IsLearningEnabled() const { return learning_enabled; }
    
    // Learn from user acceptance/rejection of recommendations
    void LearnFromFeedback(const String& rec_id, bool accepted);
    
    // Update recommendation engine based on learned patterns
    void UpdateEngine();
    
private:
    ValueMap user_preferences;
    Vector<Recommendation> recommendation_history;
    bool learning_enabled;
    
    // Internal AI model data
    ValueMap ai_model_weights;
    Vector<ValueMap> learned_patterns;
    
    // Process audio features for recommendation
    ValueMap ExtractAudioFeatures(const Vector<double>& audio_buffer);
    
    // Process MIDI features for recommendation
    ValueMap ExtractMidiFeatures(const Vector<MidiEvent>& midi_events);
    
    // Match features to known patterns
    Vector<Recommendation> MatchPatterns(const ValueMap& features, RecommendationType type);
    
    // Helper for contextual recommendations
    Vector<Recommendation> GenerateGenreStyleRecommendations(const ValueMap& context);
    Vector<Recommendation> GenerateTechniqueRecommendations(const ValueMap& context);
};

} // namespace DSP

// Midi namespace for groove and phrase services
namespace Midi {

// GrooveExtractor - extracts groove patterns from MIDI performances
class GrooveExtractor {
public:
    typedef GrooveExtractor CLASSNAME;
    
    GrooveExtractor();
    virtual ~GrooveExtractor();
    
    // Structure for representing a groove
    struct GrooveTemplate : public Moveable<GrooveTemplate> {
        String id;
        String name;
        String genre;
        String style;
        double tempo_reference;  // Reference tempo for this groove
        Vector<int> timing_offsets;   // Time offsets in ticks
        Vector<double> velocity_adjustments;  // Velocity adjustments
        Vector<double> humanization_factors;  // Amount of randomness to add
        int ticks_per_beat;        // PPQN (pulses per quarter note)
        
        GrooveTemplate() : tempo_reference(120.0), ticks_per_beat(480) {}
    };
    
    // Extract groove template from a MIDI sequence
    GrooveTemplate ExtractGroove(const Vector<MidiEvent>& sequence);
    
    // Apply a groove template to a MIDI sequence
    Vector<MidiEvent> ApplyGroove(const Vector<MidiEvent>& sequence, const GrooveTemplate& template);
    
    // Quantize a MIDI sequence to a groove template
    Vector<MidiEvent> QuantizeToGroove(const Vector<MidiEvent>& sequence, 
                                      const GrooveTemplate& template, 
                                      double strength = 1.0);
    
    // Create a standard groove (swing, shuffle, etc.)
    GrooveTemplate CreateStandardGroove(const String& style_name);
    
    // Get list of available groove templates
    Vector<String> GetAvailableGrooves() const;
    
    // Add a custom groove template
    void AddCustomGroove(const GrooveTemplate& template);
    
    // Load groove from file
    bool LoadGrooveFromFile(const String& filepath);
    
    // Save groove to file
    bool SaveGrooveToFile(const GrooveTemplate& template, const String& filepath);
    
    // Get/set global groove settings
    void SetHumanizationAmount(double amount) { humanization_amount = max(0.0, min(1.0, amount)); }
    double GetHumanizationAmount() const { return humanization_amount; }
    
    // Analyze a sequence to determine its groove characteristics
    ValueMap AnalyzeGrooveCharacteristics(const Vector<MidiEvent>& sequence);
    
private:
    Vector<GrooveTemplate> groove_templates;
    double humanization_amount;  // How much of the groove to apply (0.0 to 1.0)
    
    // Internal helper methods
    double CalculateAverageTiming(const Vector<int>& offsets);
    Vector<double> CalculateVelocityDeviation(const Vector<MidiEvent>& events);
    void ApplyTimingToSequence(Vector<MidiEvent>& sequence, const Vector<int>& offsets);
    void ApplyVelocityToSequence(Vector<MidiEvent>& sequence, const Vector<double>& adjustments);
};

// PhraseDatabase - stores and retrieves musical phrases
class PhraseDatabase {
public:
    typedef PhraseDatabase CLASSNAME;
    
    PhraseDatabase();
    virtual ~PhraseDatabase();
    
    // Structure for representing a musical phrase
    struct MusicalPhrase : public Moveable<MusicalPhrase> {
        String id;
        String name;
        String category;      // "bass", "lead", "chords", "drums", etc.
        String genre;         // "rock", "jazz", "classical", etc.
        String key;           // Musical key (e.g. "Cmaj", "Amin")
        double tempo;         // Tempo when recorded
        int time_signature_numerator;    // Time signature (numerator)
        int time_signature_denominator;  // Time signature (denominator)
        Vector<MidiEvent> events;        // MIDI events in the phrase
        Vector<String> tags;             // Tags for search
        String style;         // Playing style (e.g. "legato", "staccato")
        String instrument;    // Recommended instrument
        double complexity;    // Complexity rating (0.0 to 1.0)
        Time creation_date;   // When phrase was added
        String author;        // Who created the phrase
        
        MusicalPhrase() : tempo(120.0), time_signature_numerator(4), time_signature_denominator(4), 
                         complexity(0.5) {}
    };
    
    // Add a phrase to the database
    void AddPhrase(const MusicalPhrase& phrase);
    
    // Remove a phrase from the database
    bool RemovePhrase(const String& id);
    
    // Retrieve a phrase by ID
    const MusicalPhrase* GetPhraseById(const String& id) const;
    
    // Search for phrases by criteria
    Vector<const MusicalPhrase*> SearchByCategory(const String& category) const;
    Vector<const MusicalPhrase*> SearchByGenre(const String& genre) const;
    Vector<const MusicalPhrase*> SearchByKey(const String& key) const;
    Vector<const MusicalPhrase*> SearchByTags(const Vector<String>& tags) const;
    Vector<const MusicalPhrase*> SearchByStyle(const String& style) const;
    Vector<const MusicalPhrase*> SearchByInstrument(const String& instrument) const;
    Vector<const MusicalPhrase*> SearchByText(const String& query) const;
    
    // Get all phrases in the database
    Vector<const MusicalPhrase*> GetAllPhrases() const;
    
    // Get phrases that match multiple criteria
    Vector<const MusicalPhrase*> AdvancedSearch(const ValueMap& criteria) const;
    
    // Load phrases from file
    bool LoadFromFile(const String& filepath);
    
    // Save phrases to file
    bool SaveToFile(const String& filepath) const;
    
    // Get statistics about the database
    int GetPhraseCount() const { return phrases.GetCount(); }
    Vector<String> GetCategories() const;
    Vector<String> GetGenres() const;
    Vector<String> GetKeys() const;
    Vector<String> GetStyles() const;
    Vector<String> GetInstruments() const;
    
    // Export/import individual phrases
    bool ExportPhrase(const String& id, const String& filepath) const;
    bool ImportPhrase(const String& filepath);
    
    // Merge another database into this one
    void MergeDatabase(const PhraseDatabase& other);
    
    // Clear the database
    void Clear();
    
private:
    Vector<MusicalPhrase> phrases;
    VectorMap<String, int> id_to_index;  // Fast lookup by ID
    
    // Helper for searching
    bool MatchesCriteria(const MusicalPhrase& phrase, const ValueMap& criteria) const;
    
    // Index for faster searching
    VectorMap<String, Vector<int>> category_index;
    VectorMap<String, Vector<int>> genre_index;
    VectorMap<String, Vector<int>> key_index;
    VectorMap<String, Vector<int>> tag_index;
    VectorMap<String, Vector<int>> style_index;
    VectorMap<String, Vector<int>> instrument_index;
    
    // Build indexes after adding/removing phrases
    void RebuildIndexes();
    void AddToIndex(const MusicalPhrase& phrase, int index);
    void RemoveFromIndex(const MusicalPhrase& phrase, int index);
};

} // namespace Midi

#endif