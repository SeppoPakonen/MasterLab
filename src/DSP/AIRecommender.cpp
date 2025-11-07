#include "AIRecommender.h"
#include <Math/FFT.h>

namespace DSP {

AIRecommender::AIRecommender() : learning_enabled(true) {
    // Initialize the AI recommender system
    // For a basic implementation, we'll initialize some default preferences
    user_preferences.Set("preferred_genres", Value(Vector<String>()));
    user_preferences.Set("preferred_effects", Value(Vector<String>()));
    user_preferences.Set("preferred_complexity", 0.5);
    user_preferences.Set("learning_rate", 0.1);
}

AIRecommender::~AIRecommender() {
    // Clean up resources
}

Vector<AIRecommender::Recommendation> AIRecommender::GenerateAudioRecommendations(
    const Vector<double>& audio_buffer, const String& context) {
    Vector<Recommendation> recommendations;
    
    // Analyze audio features
    ValueMap features = ExtractAudioFeatures(audio_buffer);
    
    // Generate recommendations based on features and context
    Recommendation rec;
    rec.id = "rec_" + Upp::AsString(++next_recommendation_id);
    rec.type = EFFECT_SUGGESTION;
    rec.confidence = 0.8;
    rec.name = "EQ Enhancement";
    rec.description = "Suggested EQ settings to enhance the audio";
    rec.attributes.Set("effect_type", "EQ");
    rec.attributes.Set("frequency", features.Get("dominant_frequency", 1000.0));
    double dynamic_range = features.Get("dynamic_range", 6.0);
    rec.attributes.Set("boost_amount", dynamic_range / 10.0);
    
    recommendations.Add(rec);
    
    // Add more recommendations based on other features
    double spectral_centroid = features.Get("spectral_centroid", 1000.0);
    if (spectral_centroid > 2000.0) {
        rec.id = "rec_" + Upp::AsString(++next_recommendation_id);
        rec.name = "High-End Compression";
        rec.description = "Recommended compressor settings for bright audio";
        rec.type = EFFECT_SUGGESTION;
        rec.attributes.Set("effect_type", "Compressor");
        rec.attributes.Set("ratio", 3.0);
        rec.attributes.Set("threshold", -12.0);
        rec.attributes.Set("attack", 5.0);
        rec.attributes.Set("release", 80.0);
        recommendations.Add(rec);
    }
    
    return recommendations;
}

Vector<AIRecommender::Recommendation> AIRecommender::GenerateMidiRecommendations(
    const Vector<MidiEvent>& midi_events, const String& context) {
    Vector<Recommendation> recommendations;
    
    // Analyze MIDI features
    ValueMap features = ExtractMidiFeatures(midi_events);
    
    // Generate recommendations based on MIDI features
    Recommendation rec;
    rec.id = "rec_" + Upp::AsString(++next_recommendation_id);
    rec.type = INSTRUMENT_MATCH;
    rec.confidence = 0.9;
    rec.name = "Instrument Suggestion";
    rec.description = "Best matching instrument for this melodic pattern";
    
    String suggested_instr = "Grand Piano";
    double avg_note_density = features.Get("avg_note_density", 2.0);
    if (avg_note_density > 4.0) {
        suggested_instr = "Electric Piano";
    }
    double avg_velocity = features.Get("avg_velocity", 64.0);
    if (avg_velocity > 100.0) {
        suggested_instr = "Overdriven Guitar";
    }
    
    rec.attributes.Set("instrument_type", suggested_instr);
    rec.related_items_str = "velocity_curve_optimized";
    recommendations.Add(rec);
    
    return recommendations;
}

Vector<AIRecommender::Recommendation> AIRecommender::GenerateContextualRecommendations(
    const ValueMap& project_context) {
    Vector<Recommendation> recommendations;
    
    // Analyze the project context to generate recommendations
    String current_genre = const_cast<ValueMap&>(project_context).Get("genre", String("undefined"));
    String current_key = const_cast<ValueMap&>(project_context).Get("key", String("C"));
    double current_tempo = (double)const_cast<ValueMap&>(project_context).Get("tempo", 120.0);
    
    Recommendation rec;
    rec.id = "rec_" + Upp::AsString(++next_recommendation_id);
    rec.type = GENRE_STYLE;
    rec.confidence = 0.85;
    rec.name = "Genre-Based Effects";
    rec.description = "Effects chain suggested for " + current_genre + " music";
    
    if (current_genre == "Rock") {
        Vector<String> effects_chain1;
        effects_chain1.Add("Compressor");
        effects_chain1.Add("Distortion");
        effects_chain1.Add("Delay");
        effects_chain1.Add("Reverb");
        rec.attributes.Set("effects_chain", Upp::AsString(effects_chain1));
    } else if (current_genre == "Electronic") {
        Vector<String> effects_chain2;
        effects_chain2.Add("Sidechain Compressor");
        effects_chain2.Add("Filter");
        effects_chain2.Add("Delay");
        effects_chain2.Add("Reverb");
        rec.attributes.Set("effects_chain", Upp::AsString(effects_chain2));
    } else if (current_genre == "Classical") {
        Vector<String> effects_chain3;
        effects_chain3.Add("Subtle Reverb");
        effects_chain3.Add("EQ");
        rec.attributes.Set("effects_chain", Upp::AsString(effects_chain3));
    }
    
    recommendations.Add(rec);
    
    return recommendations;
}

void AIRecommender::TrainModel(const Vector<ValueMap>& training_data) {
    // For a basic implementation, we'll just store the training data
    // In a real implementation, this would update neural network weights
    for (const auto& data : training_data) {
        learned_patterns.Add(data);
    }
    
    // Update internal model weights based on training data
    // Simplified implementation
    ai_model_weights.Set("training_samples", GetTrainingSampleCount() + training_data.GetCount());
}

void AIRecommender::SetUserPreferences(const ValueMap& preferences) {
    // Merge new preferences with existing ones
    for(int i = 0; i < preferences.GetCount(); i++) {
        this->user_preferences.Set(preferences.GetKey(i), preferences[i]);
    }
}

void AIRecommender::LearnFromFeedback(const String& rec_id, bool accepted) {
    if (!learning_enabled) return;
    
    // Find the recommendation in history
    for (int i = 0; i < recommendation_history.GetCount(); i++) {
        if (recommendation_history[i].id == rec_id) {
            // Update our model based on the feedback
            double learning_rate = user_preferences.Get("learning_rate", 0.1);
            
            if (accepted) {
                // Increase the weight of similar recommendations
                recommendation_history[i].confidence = min(1.0, recommendation_history[i].confidence + learning_rate * 0.1);
            } else {
                // Decrease the weight of similar recommendations
                recommendation_history[i].confidence = max(0.0, recommendation_history[i].confidence - learning_rate * 0.15);
            }
            break;
        }
    }
}

ValueMap AIRecommender::ExtractAudioFeatures(const Vector<double>& audio_buffer) {
    ValueMap features;
    
    // Calculate basic audio features
    double sum = 0.0;
    double sum_sq = 0.0;
    double max_val = 0.0;
    int sample_count = audio_buffer.GetCount();
    
    for (double sample : audio_buffer) {
        double abs_val = abs(sample);
        sum += abs_val;
        sum_sq += sample * sample;
        max_val = max(max_val, abs_val);
    }
    
    double rms = sample_count > 0 ? sqrt(sum_sq / sample_count) : 0.0;
    double peak = max_val;
    double dynamic_range = peak > 0 ? 20 * log10(rms / max_val) : 0.0; // Inverted for positive values
    
    features.Set("rms_level", rms);
    features.Set("peak_level", peak);
    features.Set("dynamic_range", abs(dynamic_range));
    
    // Calculate spectral features using a simple approach
    int fft_size = 1024;
    if (sample_count >= fft_size) {
        // Copy first 1024 samples for FFT
        Vector<Complex> fft_input(fft_size);
        for (int i = 0; i < fft_size; i++) {
            fft_input[i] = Complex(audio_buffer[i], 0.0);
        }
        
        // Perform FFT
        FFT(fft_input);
        
        // Calculate spectral centroid
        double spectrum_sum = 0.0;
        double weighted_sum = 0.0;
        for (int i = 0; i < fft_size/2; i++) {
            double mag = abs(fft_input[i]);
            spectrum_sum += mag;
            weighted_sum += mag * i;
        }
        
        double spectral_centroid = spectrum_sum > 0 ? weighted_sum / spectrum_sum : 0.0;
        features.Set("spectral_centroid", spectral_centroid);
        
        // Find dominant frequency (peak in spectrum)
        double max_mag = 0.0;
        int peak_bin = 0;
        for (int i = 0; i < fft_size/2; i++) {
            double mag = abs(fft_input[i]);
            if (mag > max_mag) {
                max_mag = mag;
                peak_bin = i;
            }
        }
        
        features.Set("dominant_frequency", peak_bin * 44100.0 / fft_size); // Assuming 44100Hz sample rate
    } else {
        features.Set("spectral_centroid", 0.0);
        features.Set("dominant_frequency", 0.0);
    }
    
    return features;
}

ValueMap AIRecommender::ExtractMidiFeatures(const Vector<MidiEvent>& midi_events) {
    ValueMap features;
    
    if (midi_events.IsEmpty()) {
        features.Set("avg_note_density", 0.0);
        features.Set("avg_velocity", 0.0);
        features.Set("note_range", 0);
        return features;
    }
    
    Vector<int> note_numbers;
    Vector<int> velocities;
    Vector<double> times;
    
    for (const auto& evt : midi_events) {
        if ((evt.type & 0xF0) == 0x90) {  // MIDI Note On events have type 0x90-0x9F
            note_numbers.Add(evt.note);
            velocities.Add(evt.velocity);
            times.Add(evt.time);
        }
    }
    
    if (!note_numbers.IsEmpty()) {
        int min_note = note_numbers[0], max_note = note_numbers[0];
        for (int note : note_numbers) {
            min_note = min(min_note, note);
            max_note = max(max_note, note);
        }
        
        double avg_velocity = 0.0;
        for (int vel : velocities) {
            avg_velocity += vel;
        }
        avg_velocity /= velocities.GetCount();
        
        double avg_density = 0.0; // Average notes per beat (simplified)
        if (!times.IsEmpty() && times[0] != times[times.GetCount()-1]) {
            avg_density = (double)note_numbers.GetCount() / (times[times.GetCount()-1] - times[0]) * 100.0; // Arbitrary scaling
        }
        
        features.Set("note_range", max_note - min_note);
        features.Set("avg_velocity", avg_velocity);
        features.Set("avg_note_density", avg_density);
    } else {
        features.Set("note_range", 0);
        features.Set("avg_velocity", 0.0);
        features.Set("avg_note_density", 0.0);
    }
    
    return features;
}

Vector<AIRecommender::Recommendation> AIRecommender::MatchPatterns(const ValueMap& features, RecommendationType type) {
    Vector<Recommendation> matches;
    
    // In a real implementation, this would match against learned patterns
    // For now, we'll generate some simple recommendations based on features
    
    if (type == EFFECT_SUGGESTION) {
        Recommendation rec;
        rec.type = EFFECT_SUGGESTION;
        rec.confidence = 0.7;
        
        if ((double)const_cast<ValueMap&>(features).Get("dynamic_range", 0.0) > 10.0) {
            rec.name = "Compression Needed";
            rec.description = "Dynamic range suggests compression would be beneficial";
            rec.attributes.Set("effect_type", "Compressor");
            rec.attributes.Set("suggested_ratio", 4.0);
            rec.attributes.Set("suggested_threshold", -18.0);
        } else {
            rec.name = "Good Dynamic Balance";
            rec.description = "Audio has good natural dynamic balance";
            rec.attributes.Set("effect_type", "None needed");
        }
        
        matches.Add(rec);
    }
    
    return matches;
}

Vector<AIRecommender::Recommendation> AIRecommender::GenerateGenreStyleRecommendations(const ValueMap& context) {
    Vector<Recommendation> recommendations;
    // Implementation for genre-specific recommendations
    return recommendations;
}

Vector<AIRecommender::Recommendation> AIRecommender::GenerateTechniqueRecommendations(const ValueMap& context) {
    Vector<Recommendation> recommendations;
    // Implementation for technique recommendations
    return recommendations;
}

void AIRecommender::UpdateEngine() {
    // Update the recommendation engine based on learned patterns
    // In a real implementation, this would update the internal AI models
}

} // namespace DSP