#ifndef _DSP_AIRecommender_h_
#define _DSP_AIRecommender_h_

#include <Core/Core.h>
#include <MIDI/MIDI.h>  // For MIDI data structures
#include <AudioCore/AudioCore.h>
#include <AudioEditing/AudioEditing.h>  // For MidiEvent

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
    int next_recommendation_id = 0;  // For generating unique recommendation IDs
    
    // Internal AI model data
    ValueMap ai_model_weights;
    Vector<ValueMap> learned_patterns;
    
    // Helper functions
    int GetTrainingSampleCount() const { return learned_patterns.GetCount(); }
    
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

#endif