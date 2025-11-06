#include "AIRecommender.h"
#include <Math/FFT.h>

namespace DSP {

AIRecommender::AIRecommender() : learning_enabled(true) {
    // Initialize the AI recommender system
    // For a basic implementation, we'll initialize some default preferences
    user_preferences.Set("preferred_genres", Vector<String>());
    user_preferences.Set("preferred_effects", Vector<String>());
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
    rec.attributes.Set("boost_amount", features.Get("dynamic_range", 6.0)/10.0);
    
    recommendations.Add(rec);
    
    // Add more recommendations based on other features
    if (features.Get("spectral_centroid", 1000.0) > 2000.0) {
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
    if (features.Get("avg_note_density", 2.0) > 4.0) {
        suggested_instr = "Electric Piano";
    } else if (features.Get("avg_velocity", 64.0) > 100.0) {
        suggested_instr = "Overdriven Guitar";
    }
    
    rec.attributes.Set("instrument_type", suggested_instr);
    rec.related_items.Add("velocity_curve_optimized");
    recommendations.Add(rec);
    
    return recommendations;
}

Vector<AIRecommender::Recommendation> AIRecommender::GenerateContextualRecommendations(
    const ValueMap& project_context) {
    Vector<Recommendation> recommendations;
    
    // Analyze the project context to generate recommendations
    String current_genre = project_context.Get("genre", "undefined");
    String current_key = project_context.Get("key", "C");
    double current_tempo = project_context.Get("tempo", 120.0);
    
    Recommendation rec;
    rec.id = "rec_" + Upp::AsString(++next_recommendation_id);
    rec.type = GENRE_STYLE;
    rec.confidence = 0.85;
    rec.name = "Genre-Based Effects";
    rec.description = "Effects chain suggested for " + current_genre + " music";
    
    if (current_genre == "Rock") {
        rec.attributes.Set("effects_chain", Vector<String>({"Compressor", "Distortion", "Delay", "Reverb"}));
    } else if (current_genre == "Electronic") {
        rec.attributes.Set("effects_chain", Vector<String>({"Sidechain Compressor", "Filter", "Delay", "Reverb"}));
    } else if (current_genre == "Classical") {
        rec.attributes.Set("effects_chain", Vector<String>({"Subtle Reverb", "EQ"}));
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
        if (evt.GetType() == MidiEvent::NOTE_ON) {
            note_numbers.Add(evt.GetNote());
            velocities.Add(evt.GetVelocity());
            times.Add(evt.GetTime());
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
        
        if (features.Get("dynamic_range", 0.0) > 10.0) {
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


namespace Midi {

GrooveExtractor::GrooveExtractor() : humanization_amount(0.3) {
    // Initialize with some standard grooves
    GrooveTemplate swing;
    swing.id = "swing";
    swing.name = "Swing Feel";
    swing.genre = "Jazz";
    swing.style = "Swing";
    swing.tempo_reference = 120.0;
    // Add simple swing offsets
    for (int i = 0; i < 8; i++) { // 8th note grid
        if (i % 2 == 0) {
            swing.timing_offsets.Add(-10); // Early on even divisions (slightly)
        } else {
            swing.timing_offsets.Add(20);  // Late on odd divisions (more swing)
        }
    }
    // Add velocity adjustments for swing feel
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            swing.velocity_adjustments.Add(0.1); // Slightly louder on strong beats
        } else {
            swing.velocity_adjustments.Add(-0.05); // Slightly softer on weak beats
        }
    }
    groove_templates.Add(swing);
    
    // Add shuffle groove
    GrooveTemplate shuffle;
    shuffle.id = "shuffle";
    shuffle.name = "Shuffle Feel";
    shuffle.genre = "Blues";
    shuffle.style = "Shuffle";
    shuffle.tempo_reference = 120.0;
    for (int i = 0; i < 6; i++) { // Triplet feel
        if (i % 3 == 0) {
            shuffle.timing_offsets.Add(-5);   // Strong beat
        } else if (i % 3 == 1) {
            shuffle.timing_offsets.Add(15);  // Late on middle triplet
        } else {
            shuffle.timing_offsets.Add(-10); // Early on last triplet
        }
    }
    groove_templates.Add(shuffle);
}

GrooveExtractor::~GrooveExtractor() {
    // Clean up
}

GrooveExtractor::GrooveTemplate GrooveExtractor::ExtractGroove(const Vector<MidiEvent>& sequence) {
    GrooveTemplate extracted;
    extracted.id = "extracted_" + Upp::AsString(++extracted_count);
    extracted.tempo_reference = 120.0; // Will calculate from sequence
    
    // Calculate tempo from sequence
    if (!sequence.IsEmpty()) {
        // Find note events and calculate average tempo
        Vector<double> event_times;
        for (const auto& evt : sequence) {
            if (evt.GetType() == MidiEvent::NOTE_ON) {
                event_times.Add(evt.GetTime());
            }
        }
        
        if (event_times.GetCount() > 1) {
            // Calculate average time between events
            double total_time = 0.0;
            for (int i = 1; i < event_times.GetCount(); i++) {
                total_time += event_times[i] - event_times[i-1];
            }
            
            if (event_times.GetCount() > 1) {
                double avg_interval = total_time / (event_times.GetCount() - 1);
                // Convert to BPM assuming 4 beats per bar
                extracted.tempo_reference = 60.0 / (avg_interval * 4);
            }
        }
    }
    
    // Calculate timing offsets based on grid alignment
    const int GRID_SIZE = 16; // 16th notes
    Vector<double> grid_timings(GRID_SIZE, 0.0);
    Vector<int> grid_hits(GRID_SIZE, 0);
    
    // Map events to grid positions and calculate average offset
    for (const auto& evt : sequence) {
        if (evt.GetType() == MidiEvent::NOTE_ON) {
            // Simplified: snap time to nearest grid position
            double time_in_beats = evt.GetTime() * extracted.tempo_reference / 60.0;
            int grid_pos = (int)(time_in_beats * 4) % GRID_SIZE; // 4 16th notes per beat
            if (grid_pos < GRID_SIZE) {
                grid_timings[grid_pos] += (time_in_beats * 4 * 1000) - (grid_pos * 1000 / 4); // Deviation in ms
                grid_hits[grid_pos]++;
            }
        }
    }
    
    // Calculate average offset for each grid position
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid_hits[i] > 0) {
            extracted.timing_offsets.Add((int)(grid_timings[i] / grid_hits[i])); // Average offset
        } else {
            extracted.timing_offsets.Add(0); // No offset if no hits
        }
    }
    
    // Calculate velocity adjustments
    Vector<double> grid_velocities(GRID_SIZE, 64.0);
    Vector<int> grid_hits_for_velocity(GRID_SIZE, 0);
    
    for (const auto& evt : sequence) {
        if (evt.GetType() == MidiEvent::NOTE_ON) {
            double time_in_beats = evt.GetTime() * extracted.tempo_reference / 60.0;
            int grid_pos = (int)(time_in_beats * 4) % GRID_SIZE;
            if (grid_pos < GRID_SIZE) {
                grid_velocities[grid_pos] += evt.GetVelocity();
                grid_hits_for_velocity[grid_pos]++;
            }
        }
    }
    
    // Calculate average velocity for each grid position
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid_hits_for_velocity[i] > 0) {
            double avg_velocity = grid_velocities[i] / grid_hits_for_velocity[i];
            extracted.velocity_adjustments.Add(avg_velocity - 64.0); // Difference from median (64)
        } else {
            extracted.velocity_adjustments.Add(0.0);
        }
    }
    
    return extracted;
}

Vector<MidiEvent> GrooveExtractor::ApplyGroove(const Vector<MidiEvent>& sequence, const GrooveTemplate& groove_template) {
    Vector<MidiEvent> result = sequence;
    
    // Apply timing offsets from groove template
    for (auto& evt : result) {
        if (evt.GetType() == MidiEvent::NOTE_ON || evt.GetType() == MidiEvent::NOTE_OFF) {
            // Calculate position in grid based on tempo
            double time_in_beats = evt.GetTime() * groove_template.tempo_reference / 60.0;
            int grid_pos = (int)(time_in_beats * 4) % groove_template.timing_offsets.GetCount();
            
            if (grid_pos < groove_template.timing_offsets.GetCount()) {
                // Apply timing offset (convert from ticks to time)
                double offset_ticks = groove_template.timing_offsets[grid_pos];
                double offset_seconds = (offset_ticks * 60.0 / groove_template.tempo_reference) / 480.0; // Assuming 480 PPQN
                evt.SetTime(evt.GetTime() + offset_seconds * groove_template.humanization_factor * humanization_amount);
            }
            
            // Apply velocity adjustments
            if (evt.GetType() == MidiEvent::NOTE_ON) {
                int grid_pos = (int)(evt.GetTime() * groove_template.tempo_reference / 60.0 * 4) % 
                              groove_template.velocity_adjustments.GetCount();
                              
                if (grid_pos < groove_template.velocity_adjustments.GetCount()) {
                    int new_velocity = evt.GetVelocity() + (int)(groove_template.velocity_adjustments[grid_pos] * 127.0 * humanization_amount);
                    new_velocity = max(0, min(127, new_velocity));
                    evt.SetVelocity(new_velocity);
                }
            }
        }
    }
    
    return result;
}

Vector<MidiEvent> GrooveExtractor::QuantizeToGroove(const Vector<MidiEvent>& sequence, 
                                                    const GrooveTemplate& template, 
                                                    double strength) {
    // Implementation of groove quantization with strength control
    Vector<MidiEvent> quantized = sequence;
    
    for (auto& evt : quantized) {
        // Similar to ApplyGroove but with strength control
        if (evt.GetType() == MidiEvent::NOTE_ON || evt.GetType() == MidiEvent::NOTE_OFF) {
            double time_in_beats = evt.GetTime() * template.tempo_reference / 60.0;
            int grid_pos = (int)(time_in_beats * 4) % template.timing_offsets.GetCount();
            
            if (grid_pos < template.timing_offsets.GetCount()) {
                double offset_ticks = template.timing_offsets[grid_pos];
                double offset_seconds = (offset_ticks * 60.0 / template.tempo_reference) / 480.0;
                
                // Apply offset with strength control
                double adjusted_offset = offset_seconds * strength * template.humanization_factor * humanization_amount;
                evt.SetTime(evt.GetTime() + adjusted_offset);
            }
        }
    }
    
    return quantized;
}

GrooveExtractor::GrooveTemplate GrooveExtractor::CreateStandardGroove(const String& style_name) {
    for (const auto& template : groove_templates) {
        if (template.id == style_name) {
            return template;
        }
    }
    
    // If not found, return an empty template
    return GrooveTemplate();
}

bool GrooveExtractor::LoadGrooveFromFile(const String& filepath) {
    // Implementation to load groove from file
    // For now, we'll just return false to indicate not implemented
    return false;
}

bool GrooveExtractor::SaveGrooveToFile(const GrooveTemplate& template, const String& filepath) {
    // Implementation to save groove to file
    // For now, we'll just return false to indicate not implemented
    return false;
}

Vector<String> GrooveExtractor::GetAvailableGrooves() const {
    Vector<String> names;
    for (const auto& template : groove_templates) {
        names.Add(template.id);
    }
    return names;
}

void GrooveExtractor::AddCustomGroove(const GrooveTemplate& template) {
    groove_templates.Add(template);
}

ValueMap GrooveExtractor::AnalyzeGrooveCharacteristics(const Vector<MidiEvent>& sequence) {
    ValueMap analysis;
    
    // Calculate various groove metrics
    double avg_timing_deviation = 0.0;
    int timing_deviation_count = 0;
    
    // Calculate timing deviation from strict grid
    for (const auto& evt : sequence) {
        if (evt.GetType() == MidiEvent::NOTE_ON) {
            double time_in_beats = evt.GetTime() * 120.0 / 60.0; // Use reference tempo
            double nearest_grid = round(time_in_beats * 4.0) / 4.0; // Nearest 16th note
            double deviation = abs(time_in_beats - nearest_grid);
            avg_timing_deviation += deviation;
            timing_deviation_count++;
        }
    }
    
    if (timing_deviation_count > 0) {
        analysis.Set("average_timing_deviation", (avg_timing_deviation / timing_deviation_count) * 1000.0); // In milliseconds
    } else {
        analysis.Set("average_timing_deviation", 0.0);
    }
    
    // Calculate velocity variance
    Vector<int> velocities;
    for (const auto& evt : sequence) {
        if (evt.GetType() == MidiEvent::NOTE_ON) {
            velocities.Add(evt.GetVelocity());
        }
    }
    
    if (!velocities.IsEmpty()) {
        double avg_velocity = 0.0;
        for (int vel : velocities) {
            avg_velocity += vel;
        }
        avg_velocity /= velocities.GetCount();
        
        double vel_variance = 0.0;
        for (int vel : velocities) {
            vel_variance += (vel - avg_velocity) * (vel - avg_velocity);
        }
        vel_variance /= velocities.GetCount();
        
        analysis.Set("velocity_variance", sqrt(vel_variance));
        analysis.Set("average_velocity", avg_velocity);
    } else {
        analysis.Set("velocity_variance", 0.0);
        analysis.Set("average_velocity", 64.0);
    }
    
    return analysis;
}

// PhraseDatabase implementation
PhraseDatabase::PhraseDatabase() {
    // Initialize the phrase database
}

PhraseDatabase::~PhraseDatabase() {
    // Clean up
}

void PhraseDatabase::AddPhrase(const MusicalPhrase& phrase) {
    int index = phrases.GetCount();
    phrases.Add(phrase);
    id_to_index.GetAdd(phrase.id) = index;
    
    // Add to indexes for faster searching
    AddToIndex(phrase, index);
}

bool PhraseDatabase::RemovePhrase(const String& id) {
    int index = id_to_index.Get(id, -1);
    if (index == -1 || index >= phrases.GetCount()) {
        return false; // Phrase not found
    }
    
    // Remove from indexes
    RemoveFromIndex(phrases[index], index);
    
    // Remove from main list - we use swap-and-remove for efficiency
    if (index < phrases.GetCount() - 1) {
        // Swap with last element
        phrases[index] = pick(phrases[phrases.GetCount() - 1]);
        // Update the moved item's index in the lookup table
        id_to_index.GetAdd(phrases[index].id) = index;
    }
    phrases.RemoveLast();
    
    // Update the lookup table to remove the deleted item's entry
    // Remove the old entry by reconstructing the lookup
    VectorMap<String, int> new_lookup;
    for (int i = 0; i < phrases.GetCount(); i++) {
        new_lookup.GetAdd(phrases[i].id) = i;
    }
    id_to_index = new_lookup;
    
    return true;
}

const PhraseDatabase::MusicalPhrase* PhraseDatabase::GetPhraseById(const String& id) const {
    int index = id_to_index.Get(id, -1);
    if (index >= 0 && index < phrases.GetCount()) {
        return &phrases[index];
    }
    return nullptr;
}

Vector<const PhraseDatabase::MusicalPhrase*> PhraseDatabase::SearchByCategory(const String& category) const {
    Vector<const MusicalPhrase*> results;
    int cat_idx = category_index.Find(category);
    if (cat_idx >= 0) {
        const Vector<int>& indices = category_index[cat_idx];
        for (int idx : indices) {
            if (idx < phrases.GetCount()) {
                results.Add(&phrases[idx]);
            }
        }
    }
    return results;
}

Vector<const PhraseDatabase::MusicalPhrase*> PhraseDatabase::SearchByGenre(const String& genre) const {
    Vector<const MusicalPhrase*> results;
    int gen_idx = genre_index.Find(genre);
    if (gen_idx >= 0) {
        const Vector<int>& indices = genre_index[gen_idx];
        for (int idx : indices) {
            if (idx < phrases.GetCount()) {
                results.Add(&phrases[idx]);
            }
        }
    }
    return results;
}

Vector<const PhraseDatabase::MusicalPhrase*> PhraseDatabase::SearchByTags(const Vector<String>& tags) const {
    Vector<const MusicalPhrase*> results;
    
    // Start with all phrases
    Vector<bool> match_flags(phrases.GetCount(), true);
    
    for (const String& tag : tags) {
        int tag_idx = tag_index.Find(tag);
        if (tag_idx >= 0) {
            // Mark all non-matching phrases as false
            Vector<bool> tag_match_flags(phrases.GetCount(), false);
            const Vector<int>& indices = tag_index[tag_idx];
            for (int idx : indices) {
                if (idx < phrases.GetCount()) {
                    tag_match_flags[idx] = true;
                }
            }
            
            // Update overall match flags - AND operation
            for (int i = 0; i < match_flags.GetCount(); i++) {
                match_flags[i] = match_flags[i] && tag_match_flags[i];
            }
        } else {
            // If a tag doesn't exist, no results can match
            Vector<bool> empty_flags(phrases.GetCount(), false);
            match_flags = empty_flags;
            break;
        }
    }
    
    // Add matched phrases to results
    for (int i = 0; i < match_flags.GetCount(); i++) {
        if (match_flags[i]) {
            results.Add(&phrases[i]);
        }
    }
    
    return results;
}

Vector<const PhraseDatabase::MusicalPhrase*> PhraseDatabase::GetAllPhrases() const {
    Vector<const MusicalPhrase*> results;
    for (const auto& phrase : phrases) {
        results.Add(&phrase);
    }
    return results;
}

Vector<const PhraseDatabase::MusicalPhrase*> PhraseDatabase::AdvancedSearch(const ValueMap& criteria) const {
    Vector<const MusicalPhrase*> results;
    
    for (int i = 0; i < phrases.GetCount(); i++) {
        if (MatchesCriteria(phrases[i], criteria)) {
            results.Add(&phrases[i]);
        }
    }
    
    return results;
}

bool PhraseDatabase::LoadFromFile(const String& filepath) {
    // Implementation for loading phrases from file would go here
    // This would typically parse a file format containing phrase definitions
    return false; // Placeholder implementation
}

bool PhraseDatabase::SaveToFile(const String& filepath) const {
    // Implementation for saving phrases to file would go here
    // This would typically serialize the phrases to a file format
    return false; // Placeholder implementation
}

Vector<String> PhraseDatabase::GetCategories() const {
    Vector<String> cats;
    for (int i = 0; i < category_index.GetCount(); i++) {
        cats.Add(category_index.GetKey(i));
    }
    return cats;
}

Vector<String> PhraseDatabase::GetGenres() const {
    Vector<String> genres;
    for (int i = 0; i < genre_index.GetCount(); i++) {
        genres.Add(genre_index.GetKey(i));
    }
    return genres;
}

Vector<String> PhraseDatabase::GetKeys() const {
    Vector<String> keys;
    for (int i = 0; i < key_index.GetCount(); i++) {
        keys.Add(key_index.GetKey(i));
    }
    return keys;
}

Vector<String> PhraseDatabase::GetStyles() const {
    Vector<String> styles;
    for (int i = 0; i < style_index.GetCount(); i++) {
        styles.Add(style_index.GetKey(i));
    }
    return styles;
}

Vector<String> PhraseDatabase::GetInstruments() const {
    Vector<String> instruments;
    for (int i = 0; i < instrument_index.GetCount(); i++) {
        instruments.Add(instrument_index.GetKey(i));
    }
    return instruments;
}

bool PhraseDatabase::ExportPhrase(const String& id, const String& filepath) const {
    const MusicalPhrase* phrase = GetPhraseById(id);
    if (!phrase) {
        return false;
    }
    
    // Implementation to export a single phrase would go here
    return false; // Placeholder implementation
}

bool PhraseDatabase::ImportPhrase(const String& filepath) {
    // Implementation to import a single phrase would go here
    return false; // Placeholder implementation
}

void PhraseDatabase::MergeDatabase(const PhraseDatabase& other) {
    for (const auto& phrase : other.phrases) {
        // Check if this phrase ID already exists in this database
        if (id_to_index.Find(phrase.id) < 0) {
            AddPhrase(phrase);
        }
    }
}

void PhraseDatabase::Clear() {
    phrases.Clear();
    id_to_index.Clear();
    
    // Clear indexes
    category_index.Clear();
    genre_index.Clear();
    key_index.Clear();
    tag_index.Clear();
    style_index.Clear();
    instrument_index.Clear();
}

bool PhraseDatabase::MatchesCriteria(const MusicalPhrase& phrase, const ValueMap& criteria) const {
    for (int i = 0; i < criteria.GetCount(); i++) {
        String key = criteria.GetKey(i);
        Value value = criteria[i];
        
        if (key == "category" && phrase.category != value) {
            return false;
        } else if (key == "genre" && phrase.genre != value) {
            return false;
        } else if (key == "key" && phrase.key != value) {
            return false;
        } else if (key == "style" && phrase.style != value) {
            return false;
        } else if (key == "instrument" && phrase.instrument != value) {
            return false;
        }
        // Could add more criteria checks here
    }
    return true;
}

void PhraseDatabase::RebuildIndexes() {
    // Clear existing indexes
    category_index.Clear();
    genre_index.Clear();
    key_index.Clear();
    tag_index.Clear();
    style_index.Clear();
    instrument_index.Clear();
    
    // Re-add all phrases to indexes
    for (int i = 0; i < phrases.GetCount(); i++) {
        AddToIndex(phrases[i], i);
    }
}

void PhraseDatabase::AddToIndex(const MusicalPhrase& phrase, int index) {
    // Add to category index
    if (!phrase.category.IsEmpty()) {
        category_index.GetAdd(phrase.category).Add(index);
    }
    
    // Add to genre index
    if (!phrase.genre.IsEmpty()) {
        genre_index.GetAdd(phrase.genre).Add(index);
    }
    
    // Add to key index
    if (!phrase.key.IsEmpty()) {
        key_index.GetAdd(phrase.key).Add(index);
    }
    
    // Add to tag index
    for (const String& tag : phrase.tags) {
        if (!tag.IsEmpty()) {
            tag_index.GetAdd(tag).Add(index);
        }
    }
    
    // Add to style index
    if (!phrase.style.IsEmpty()) {
        style_index.GetAdd(phrase.style).Add(index);
    }
    
    // Add to instrument index
    if (!phrase.instrument.IsEmpty()) {
        instrument_index.GetAdd(phrase.instrument).Add(index);
    }
}

void PhraseDatabase::RemoveFromIndex(const MusicalPhrase& phrase, int index) {
    // Remove from all indexes
    if (!phrase.category.IsEmpty()) {
        Vector<int>& cat_indices = category_index.GetAdd(phrase.category);
        for (int i = 0; i < cat_indices.GetCount(); i++) {
            if (cat_indices[i] == index) {
                cat_indices.Remove(i);
                break;
            }
        }
        if (cat_indices.IsEmpty()) {
            category_index.RemoveKey(phrase.category);
        }
    }
    
    if (!phrase.genre.IsEmpty()) {
        Vector<int>& gen_indices = genre_index.GetAdd(phrase.genre);
        for (int i = 0; i < gen_indices.GetCount(); i++) {
            if (gen_indices[i] == index) {
                gen_indices.Remove(i);
                break;
            }
        }
        if (gen_indices.IsEmpty()) {
            genre_index.RemoveKey(phrase.genre);
        }
    }
    
    // Similar removal for other indexes...
    if (!phrase.key.IsEmpty()) {
        Vector<int>& key_indices = key_index.GetAdd(phrase.key);
        for (int i = 0; i < key_indices.GetCount(); i++) {
            if (key_indices[i] == index) {
                key_indices.Remove(i);
                break;
            }
        }
        if (key_indices.IsEmpty()) {
            key_index.RemoveKey(phrase.key);
        }
    }
    
    for (const String& tag : phrase.tags) {
        if (!tag.IsEmpty()) {
            Vector<int>& tag_indices = tag_index.GetAdd(tag);
            for (int i = 0; i < tag_indices.GetCount(); i++) {
                if (tag_indices[i] == index) {
                    tag_indices.Remove(i);
                    break;
                }
            }
            if (tag_indices.IsEmpty()) {
                tag_index.RemoveKey(tag);
            }
        }
    }
    
    if (!phrase.style.IsEmpty()) {
        Vector<int>& style_indices = style_index.GetAdd(phrase.style);
        for (int i = 0; i < style_indices.GetCount(); i++) {
            if (style_indices[i] == index) {
                style_indices.Remove(i);
                break;
            }
        }
        if (style_indices.IsEmpty()) {
            style_index.RemoveKey(phrase.style);
        }
    }
    
    if (!phrase.instrument.IsEmpty()) {
        Vector<int>& instr_indices = instrument_index.GetAdd(phrase.instrument);
        for (int i = 0; i < instr_indices.GetCount(); i++) {
            if (instr_indices[i] == index) {
                instr_indices.Remove(i);
                break;
            }
        }
        if (instr_indices.IsEmpty()) {
            instrument_index.RemoveKey(phrase.instrument);
        }
    }
}

} // namespace Midi