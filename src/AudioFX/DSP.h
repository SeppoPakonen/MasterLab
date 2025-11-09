#ifndef _AudioFX_DSP_h_
#define _AudioFX_DSP_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h>  // For audio processing types
using am::AudioBuffer; // Make AudioCore's AudioBuffer available

using namespace Upp;

// DSP namespace for Digital Signal Processing infrastructure
namespace DSP {

// Forward declarations
class SignalBus;
class ParameterSet;
class ModMatrix;
class LatencyBuffer;
class Analyzer;
class PresetManager;

// Type definitions for audio processing
using Sample = double;
using AudioBuffer = Vector<Sample>;
using ParameterId = String;
using ParameterValue = double;

// Enum for parameter value types
enum class ParameterType {
    kFloat,
    kInt,
    kBool,
    kString
};

// Enum for modulation sources
enum class ModSource {
    kLFO1,
    kLFO2,
    kEnvelope1,
    kEnvelope2,
    kVelocity,
    kKeyTrack,
    kMIDI_CC1,
    kMIDI_CC2,
    kMIDI_CC3,
    kMIDI_CC4,
    kModWheel,
    kAftertouch,
    kBend,
    kRandom,
    kUser1,
    kUser2
};

// Enum for modulation destinations
enum class ModDestination {
    kOsc1Pitch,
    kOsc2Pitch,
    kOsc1Volume,
    kOsc2Volume,
    kFilterCutoff,
    kFilterResonance,
    kAmpGain,
    kPan,
    kLFO1Rate,
    kLFO2Rate
};

// Simple structure for modulation mapping
struct ModulationMapping {
    ModSource source;
    ModDestination destination;
    ParameterValue amount;
    
    ModulationMapping(ModSource s, ModDestination d, ParameterValue a = 1.0) 
        : source(s), destination(d), amount(a) {}
    
    // Support for U++ container operations
    void  operator<<=(const ModulationMapping& s) {
        source = s.source; destination = s.destination; amount = s.amount;
    }
    bool  operator==(const ModulationMapping& b) const {
        return source == b.source && destination == b.destination && amount == b.amount;
    }
    int   Compare(const ModulationMapping& b) const { 
        if (source != b.source) return (int)source - (int)b.source;
        if (destination != b.destination) return (int)destination - (int)b.destination;
        return amount < b.amount ? -1 : (amount > b.amount ? 1 : 0);
    }

    // U++ guest requirement
    void  Guest() const {}

    // Support for U++ deep copy
    void  Move(ModulationMapping& s) { *this = pick(s); }
    
    // JSON serialization for guest type compatibility
    void Jsonize(JsonIO& jio) {
        int src = (int)source;
        int dest = (int)destination;
        jio("source", src)("destination", dest)("amount", amount);
        source = (ModSource)src;
        destination = (ModDestination)dest;
    }
};

// Enum for signal bus types
enum class BusType {
    kAudio,
    kControl,
    kMIDI,
    kSidechain
};

// Signal bus for audio data transport
class SignalBus {
public:
    SignalBus();
    SignalBus(int channels, int maxFrames);
    
    void Resize(int channels, int frames);
    void Clear();
    
    // Access for reading/writing audio data
    Sample* GetChannel(int channel);
    const Sample* GetChannel(int channel) const;
    
    // Get/set number of channels and frames
    int GetChannelCount() const { return channelCount; }
    int GetFrameCount() const { return frameCount; }
    void SetFrameCount(int frames) { frameCount = min(frames, maxFrames); }
    
    // Process audio through this bus
    void ProcessAudio();
    
private:
    int channelCount;
    int frameCount;
    int maxFrames;
    Vector<AudioBuffer> buffers;  // One buffer per channel
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
    struct ParameterInfo {
        ParameterValue value;
        ParameterValue initial;
        ParameterValue min;
        ParameterValue max;
        ParameterType type;
        String name;

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
};

// Modulation matrix for routing modulation sources to destinations
class ModMatrix {
public:
    ModMatrix();
    
    // Add a modulation mapping
    void AddMapping(ModSource source, ModDestination destination, ParameterValue amount = 1.0);
    
    // Remove a modulation mapping
    void RemoveMapping(ModSource source, ModDestination destination);
    
    // Update the modulation matrix with current parameter values
    void Process();
    
    // Get the modulation amount for a specific source/destination pair
    ParameterValue GetModulationAmount(ModSource source, ModDestination destination) const;
    
    // Get all active mappings
    Vector<ModulationMapping> GetMappings() const;
    
    // Clear all mappings
    void Clear();
    
private:
    Vector<ModulationMapping> mappings;
};

// Latency buffer for handling processing delays
class LatencyBuffer {
public:
    LatencyBuffer();
    explicit LatencyBuffer(int maxDelaySamples);
    
    // Set the delay amount in samples
    void SetDelay(int samples);
    
    // Get the current delay amount
    int GetDelay() const { return delaySamples; }
    
    // Process a sample with the specified delay
    Sample Process(Sample input);
    
    // Process an audio buffer
    void ProcessBuffer(const AudioBuffer& input, AudioBuffer& output);
    
    // Get latency in samples
    int GetLatency() const { return delaySamples; }
    
private:
    int maxDelay;
    int delaySamples;
    Vector<Sample> delayLine;
    int writeIndex;
};

// Analyzer for processing and analyzing audio signals
class Analyzer {
public:
    Analyzer();
    
    // Analyze an audio buffer, returns analysis results
    ValueMap Analyze(const AudioBuffer& buffer);
    
    // Get real-time analysis results
    ValueMap GetRealTimeAnalysis();
    
    // Reset analysis state
    void Reset();
    
private:
    // Analysis data and state
    double rmsValue;
    double peakValue;
    double currentFrequency;
    Vector<Sample> spectrum;
};

// Preset manager for handling parameter presets
class PresetManager {
public:
    PresetManager();
    
    // Add a preset with current parameters
    void AddPreset(const ParameterSet& params, const String& name);
    
    // Load a preset by name
    bool LoadPreset(const String& name, ParameterSet& params);
    
    // Save current parameters as a preset
    void SavePreset(const ParameterSet& params, const String& name);
    
    // Delete a preset
    void DeletePreset(const String& name);
    
    // Get list of available presets
    Vector<String> GetPresetNames() const;
    
    // Get preset by index
    String GetPresetName(int index) const;
    
    // Get number of presets
    int GetPresetCount() const;
    
    // Rename a preset
    void RenamePreset(const String& oldName, const String& newName);
    
private:
    struct Preset {
        String name;
        ValueMap parameters;

        // Support for U++ container operations
        void  operator<<=(const Preset& s) {
            name = s.name; parameters = s.parameters;
        }
        bool  operator==(const Preset& b) const {
            return name == b.name && parameters == b.parameters;
        }
        int   Compare(const Preset& b) const { return name.Compare(b.name); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Preset& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("name", name)("parameters", parameters);
        }
    };
    
    Vector<Preset> presets;
};

// FIR filter designer
class FIRDesigner {
public:
    FIRDesigner();
    
    // Design FIR filter based on specifications
    Vector<double> DesignLowPass(int order, double cutoffFreq, double sampleRate);
    Vector<double> DesignHighPass(int order, double cutoffFreq, double sampleRate);
    Vector<double> DesignBandPass(int order, double lowFreq, double highFreq, double sampleRate);
    Vector<double> DesignBandStop(int order, double lowFreq, double highFreq, double sampleRate);
    
    // Apply windowing to filter coefficients
    void ApplyWindow(Vector<double>& coefficients, int windowType = 0); // 0=Rectangular, 1=Hamming, 2=Hann, 3=Blackman
    
private:
    // Internal design methods
    Vector<double> GenerateSinc(double cutoff, int length);
    void ApplyWindowHamming(Vector<double>& coefficients);
    void ApplyWindowHann(Vector<double>& coefficients);
    void ApplyWindowBlackman(Vector<double>& coefficients);
};

// IIR filter designer
class IIRDesigner {
public:
    IIRDesigner();
    
    // Design IIR filter based on specifications
    void DesignLowPass(double freq, double q, double sampleRate);
    void DesignHighPass(double freq, double q, double sampleRate);
    void DesignBandPass(double freq, double q, double sampleRate);
    void DesignBandStop(double freq, double q, double sampleRate);
    void DesignPeakingEQ(double freq, double q, double gain, double sampleRate);
    void DesignLowShelf(double freq, double slope, double gain, double sampleRate);
    void DesignHighShelf(double freq, double slope, double gain, double sampleRate);
    
    // Get the filter coefficients
    ValueMap GetCoefficients() const;
    
    // Process a single sample
    double ProcessSample(double input);
    
private:
    // Biquad filter coefficients
    double b0, b1, b2;  // Numerator coefficients
    double a1, a2;      // Denominator coefficients (a0 is always normalized to 1)
    
    // Filter state
    double x1, x2;      // Input delay line
    double y1, y2;      // Output delay line
    
    // Helper method to normalize coefficients
    void NormalizeCoefficients();
};

// Ambisonics encoder for spatial audio
class AmbisonicsEncoder {
public:
    AmbisonicsEncoder();
    
    enum AmbisonicOrder {
        kFirstOrder = 1,
        kSecondOrder = 2,
        kThirdOrder = 3
    };
    
    // Set the ambisonic order
    void SetOrder(AmbisonicOrder order);
    
    // Encode a signal from a specific direction
    void EncodeSignal(const AudioBuffer& input, Vector<AudioBuffer>& output, 
                      double azimuth, double elevation);
    
    // Get the number of output channels for current order
    int GetOutputChannelCount() const;
    
    // Set normalization type (SN3D, N3D, FuMa)
    void SetNormalizationType(int type); // 0=SN3D, 1=N3D, 2=FuMa
    
private:
    AmbisonicOrder order;
    int normalizationType; // 0=SN3D, 1=N3D, 2=FuMa
};

// Binaural renderer for HRTF-based spatialization
class BinauralRenderer {
public:
    BinauralRenderer();
    
    // Load HRTF data
    bool LoadHRTF(const String& filePath);
    
    // Process audio with binaural rendering
    void Process(const AudioBuffer& input, AudioBuffer& leftOutput, AudioBuffer& rightOutput,
                 double azimuth, double elevation);
    
    // Set interaural time difference
    void SetITD(bool enabled);
    
    // Set HRTF interpolation method
    void SetInterpolationMethod(int method); // 0=Nearest, 1=Bilinear, 2=Cubic
    
private:
    // HRTF data storage
    // In a real implementation, this would store impulse responses for different angles
    bool hrtfLoaded;
    bool useITD;
    int interpolationMethod;
};

// Surround meter bridge for multi-channel metering
class SurroundMeterBridge {
public:
    SurroundMeterBridge();
    
    // Set the channel configuration (e.g., "5.1", "7.1", "Dolby Atmos 7.1.4")
    void SetChannelConfig(const String& config);
    
    // Process audio and get meter values for each channel
    ValueMap ProcessWithMetering(const Vector<AudioBuffer>& input);
    
    // Get meter value for a specific channel
    double GetChannelLevel(int channelIndex) const;
    
    // Set meter integration time (for RMS calculation)
    void SetIntegrationTime(double ms);
    
private:
    String channelConfig;
    Vector<double> channelLevels;
    double integrationTime;
};

// Rack host for managing effect racks
class RackHost {
public:
    RackHost();
    
    // Define a rack module
    struct Module {
        String id;
        String name;
        String type;  // "effect", "instrument", "utility"
        ValueMap parameters;
        Vector<Module> children;  // For nested racks

        // Support for U++ container operations
        void  operator<<=(const Module& s) {
            id = s.id; name = s.name; type = s.type; parameters = s.parameters; children <<= s.children;
        }
        bool  operator==(const Module& b) const {
            return id == b.id && name == b.name && type == b.type && 
                   parameters == b.parameters && children == b.children;
        }
        int   Compare(const Module& b) const { return id.Compare(b.id); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Module& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("id", id)("name", name)("type", type)("parameters", parameters)("children", children);
        }
    };
    
    // Add a module to the rack
    void AddModule(const Module& module);
    
    // Remove a module by ID
    bool RemoveModule(const String& id);
    
    // Get module by ID
    Module* GetModule(const String& id);
    
    // Process audio through the rack
    void Process(const AudioBuffer& input, AudioBuffer& output);
    
    // Get the module tree
    const Vector<Module>& GetModules() const { return modules; }
    
    // Set bypass state for a module
    bool SetBypass(const String& id, bool bypassed);
    
    // Serialize the rack configuration
    String Serialize() const;
    
    // Deserialize the rack configuration
    bool Deserialize(const String& config);
    
private:
    Vector<Module> modules;
    ValueMap bypassStates;
};

// Chain node for linking processing modules
class ChainNode {
public:
    ChainNode();
    
    // Define node types
    enum NodeType {
        kInputNode,
        kOutputNode,
        kEffectNode,
        kInstrumentNode,
        kMixerNode,
        kRouterNode
    };
    
    // Initialize the node
    void Initialize(NodeType type, const String& name);
    
    // Connect this node's output to another node's input
    bool Connect(ChainNode* nextNode);
    
    // Disconnect from a specific node
    void Disconnect(ChainNode* node);
    
    // Process audio through this node
    virtual void Process(const AudioBuffer& input, AudioBuffer& output);
    
    // Get node type
    NodeType GetType() const { return type; }
    
    // Get node name
    const String& GetName() const { return name; }
    
    // Get connected nodes
    const Vector<ChainNode*>& GetOutputs() const { return outputs; }
    ChainNode* GetInput() const { return input; }
    
    // Set processing parameters
    virtual void SetParameter(const String& id, double value);
    virtual double GetParameter(const String& id) const;
    
private:
    NodeType type;
    String name;
    Vector<ChainNode*> outputs;
    ChainNode* input;
    ValueMap parameters;
};

// Macro mapper for linking UI controls to parameters
class MacroMapper {
public:
    MacroMapper();
    
    // Map a UI control to parameters
    void MapControl(const String& controlId, const String& paramId, 
                   double min, double max, double defaultValue = 0.0);
    
    // Map a UI control to multiple parameters with weights
    void MapControlToMultiple(const String& controlId, 
                             const Vector< Tuple<String, double> >& paramMap);
    
    // Update parameter values based on UI control value
    void UpdateParameter(const String& controlId, double controlValue);
    
    // Update UI control based on parameter value
    double GetControlValue(const String& controlId) const;
    
    // Get mapped parameter value
    double GetParameterValue(const String& paramId) const;
    
    // Clear mapping
    void ClearMapping(const String& controlId);
    
private:
    struct Mapping {
        String paramId;
        double min, max;
        double defaultValue;

        // Support for U++ container operations
        void  operator<<=(const Mapping& s) {
            paramId = s.paramId; min = s.min; max = s.max; defaultValue = s.defaultValue;
        }
        bool  operator==(const Mapping& b) const {
            return paramId == b.paramId && min == b.min && max == b.max && defaultValue == b.defaultValue;
        }
        int   Compare(const Mapping& b) const { return paramId.Compare(b.paramId); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Mapping& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("paramId", paramId)("min", min)("max", max)("defaultValue", defaultValue);
        }
    };
    
    struct MultiMapping {
        Vector< Tuple<String, double> > paramMap; // paramId, weight

        // Support for U++ container operations
        void  operator<<=(const MultiMapping& s) {
            paramMap <<= s.paramMap;
        }
        bool  operator==(const MultiMapping& b) const {
            return paramMap == b.paramMap;
        }
        int   Compare(const MultiMapping& b) const { 
            if (paramMap.GetCount() < b.paramMap.GetCount()) return -1;
            if (paramMap.GetCount() > b.paramMap.GetCount()) return 1;
            for (int i = 0; i < paramMap.GetCount(); i++) {
                if (paramMap[i].a != b.paramMap[i].a) return paramMap[i].a.Compare(b.paramMap[i].a);
                if (paramMap[i].b < b.paramMap[i].b) return -1;
                if (paramMap[i].b > b.paramMap[i].b) return 1;
            }
            return 0;
        }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(MultiMapping& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("paramMap", paramMap);
        }
    };
    
    Upp::VectorMap<String, Mapping> singleMappings;
    Upp::VectorMap<String, MultiMapping> multiMappings;
    ValueMap currentValues;
};

// Preset browser for managing and selecting presets
class PresetBrowser {
public:
    PresetBrowser();
    
    // Define preset categories
    struct PresetCategory {
        String name;
        Vector<String> presetNames;
    };
    
    // Add a preset to a category
    void AddPreset(const String& category, const String& name, const ValueMap& parameters);
    
    // Load a preset by name
    ValueMap LoadPreset(const String& category, const String& name) const;
    
    // Get available categories
    Vector<String> GetCategories() const;
    
    // Get presets in a category
    Vector<String> GetPresetsInCategory(const String& category) const;
    
    // Save preset to file
    bool SavePresetToFile(const String& category, const String& name, const String& filePath) const;
    
    // Load preset from file
    bool LoadPresetFromFile(const String& filePath, String& category, String& name, ValueMap& params);
    
    // Delete a preset
    bool DeletePreset(const String& category, const String& name);
    
    // Get preset count in category
    int GetPresetCount(const String& category) const;
    
private:
    struct Preset {
        String name;
        ValueMap parameters;

        // Support for U++ container operations
        void  operator<<=(const Preset& s) {
            name = s.name; parameters = s.parameters;
        }
        bool  operator==(const Preset& b) const {
            return name == b.name && parameters == b.parameters;
        }
        int   Compare(const Preset& b) const { return name.Compare(b.name); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Preset& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("name", name)("parameters", parameters);
        }
    };
    
    struct Category {
        String name;
        Vector<Preset> presets;

        // Support for U++ container operations
        void  operator<<=(const Category& s) {
            name = s.name; presets <<= s.presets;
        }
        bool  operator==(const Category& b) const {
            return name == b.name && presets == b.presets;
        }
        int   Compare(const Category& b) const { return name.Compare(b.name); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Category& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("name", name)("presets", presets);
        }
    };
    
    Vector<Category> categories;
};

// Latency manager for handling processing delays
class LatencyManager {
public:
    LatencyManager();
    
    // Register a component with its latency
    void RegisterComponent(const String& id, int latencySamples);
    
    // Remove a component from management
    void UnregisterComponent(const String& id);
    
    // Get total system latency
    int GetTotalLatency() const;
    
    // Get latency for a specific component
    int GetComponentLatency(const String& id) const;
    
    // Compensate for latency by applying delay
    void ApplyLatencyCompensation(AudioBuffer& buffer, int delaySamples);
    
    // Get the compensation delay for the system
    int GetCompensationDelay() const;
    
    // Reset the latency calculations
    void Reset();
    
private:
    VectorMap<String, int> componentLatencies;
    int totalLatency;
};

// Session manager for StudioRack/StudioVerse workflows
class SessionManager {
public:
    SessionManager();
    
    // Session data structure
    struct SessionData {
        String name;
        String description;
        ValueMap rackStates;      // Rack configurations
        ValueMap parameterSets;   // Parameter snapshots
        ValueMap automationData;  // Automation curves
        ValueMap macroStates;     // Macro controller states
    };
    
    // Create a new session
    void CreateSession(const String& name);
    
    // Load a session
    bool LoadSession(const String& name);
    
    // Save current session
    bool SaveSession(const String& name);
    
    // Save current session with description
    bool SaveSessionWithDescription(const String& name, const String& description);
    
    // Get list of available sessions
    Vector<String> GetAvailableSessions() const;
    
    // Apply session data to the system
    void ApplySession(const SessionData& session);
    
    // Get current session data
    SessionData GetCurrentSession() const;
    
    // Close current session
    void CloseSession();
    
    // Get session directory
    String GetSessionDirectory() const;
    
    // Set session directory
    void SetSessionDirectory(const String& dir);
    
private:
    SessionData currentSession;
    String sessionDirectory;
    Vector<String> sessionList;
    
    // Helper methods
    String GetSessionFilePath(const String& name) const;
    bool SaveSessionToFile(const SessionData& session, const String& filePath) const;
    SessionData LoadSessionFromFile(const String& filePath) const;
};

} // namespace DSP

// AI Recommender for suggesting musical content
class AIRecommender {
public:
    AIRecommender();
    
    // Recommendation types
    enum RecommendationType {
        kChordProgression,
        kMelody,
        kBassline,
        kDrumPattern,
        kArrangement,
        kParameterSetting
    };
    
    // Context for making recommendations
    struct Context {
        String genre;
        String mood;
        double tempo;
        String key;
        Vector<String> currentChords;  // Current chord progression
        Vector<String> currentMelody;  // Current melody notes
        ValueMap stylePreferences;
        
        Context() : tempo(120.0) {}
        
        // Support for U++ container operations
        void  operator<<=(const Context& s) {
            genre = s.genre; mood = s.mood; tempo = s.tempo; key = s.key;
            currentChords <<= s.currentChords; currentMelody <<= s.currentMelody;
            stylePreferences <<= s.stylePreferences;
        }
        bool  operator==(const Context& b) const {
            return genre == b.genre && mood == b.mood && tempo == b.tempo && key == b.key &&
                   currentChords == b.currentChords && currentMelody == b.currentMelody && stylePreferences == b.stylePreferences;
        }
        int   Compare(const Context& b) const { return genre.Compare(b.genre); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Context& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(JsonIO& jio) {
            jio("genre", genre)("mood", mood)("tempo", tempo)("key", key)
                ("currentChords", currentChords)("currentMelody", currentMelody)("stylePreferences", stylePreferences);
        }
    };
    
    // Get recommendations based on context
    Vector<String> GetChordRecommendations(const Context& context, int count = 4);
    Vector<String> GetMelodyRecommendations(const Context& context, int count = 4);
    Vector<String> GetBasslineRecommendations(const Context& context, int count = 4);
    Vector<String> GetDrumPatternRecommendations(const Context& context, int count = 4);
    
    // Learn from user feedback
    void ProvideFeedback(const String& recommendation, bool liked);
    
    // Load a music style model
    bool LoadStyleModel(const String& modelPath);
    
    // Get the confidence level of a recommendation
    double GetRecommendationConfidence(const String& recommendation) const;
    
    // Analyze current musical context
    ValueMap AnalyzeContext(const Context& context);
    
private:
    // Internal model data
    ValueMap styleModel;
    Vector< Tuple<String, bool> > feedbackHistory;  // recommendation, liked
};

// NET namespace for network transport
namespace NET {

class TransportLayer {
public:
    TransportLayer();
    
    // Connection types
    enum ConnectionType {
        kTCP,
        kUDP,
        kWebSocket,
        kOSC
    };
    
    // Initialize the transport layer
    bool Initialize(ConnectionType type, int port);
    
    // Send data
    bool Send(const String& data, const String& address = "");
    
    // Receive data
    String Receive();
    
    // Check if connected
    bool IsConnected() const;
    
    // Close connection
    void Close();
    
    // Get connection statistics
    ValueMap GetStats() const;
    
private:
    ConnectionType connType;
    int port;
    bool connected;
    ValueMap statistics;
};

} // namespace NET

#endif

// Calibration namespace for audio measurement and calibration
namespace Calibration {

// Measurement analyzer for audio system analysis
class MeasurementAnalyzer {
public:
    MeasurementAnalyzer();
    
    // Analyze an impulse response
    ValueMap AnalyzeImpulseResponse(const AudioBuffer& impulse);
    
    // Measure frequency response
    ValueMap AnalyzeFrequencyResponse(const AudioBuffer& stimulus, const AudioBuffer& response);
    
    // Measure THD+N (Total Harmonic Distortion + Noise)
    double MeasureTHDN(const AudioBuffer& signal, const AudioBuffer& fundamental);
    
    // Measure intermodulation distortion
    double MeasureIntermodulationDistortion(const AudioBuffer& signal);
    
    // Measure latency
    double MeasureLatency(const AudioBuffer& stimulus, const AudioBuffer& response, double sampleRate);
    
private:
    // Internal analysis methods
    AudioBuffer ComputeFFT(const AudioBuffer& signal);
    double ComputePower(const AudioBuffer& signal);
};

// Phase analyzer for phase relationship analysis
class PhaseAnalyzer {
public:
    PhaseAnalyzer();
    
    // Analyze phase relationship between two signals
    ValueMap AnalyzePhase(const AudioBuffer& signal1, const AudioBuffer& signal2);
    
    // Measure phase difference at a specific frequency
    double GetPhaseDifferenceAtFrequency(const AudioBuffer& signal1, const AudioBuffer& signal2, 
                                        double freq, double sampleRate);
    
    // Check for phase coherence
    bool IsPhaseCoherent(const AudioBuffer& signal1, const AudioBuffer& signal2, 
                        double coherenceThreshold = 0.7);
    
    // Generate phase correlation meter data
    ValueMap GetPhaseCorrelationData(const AudioBuffer& signal1, const AudioBuffer& signal2);
    
private:
    // Internal methods
    double CalculatePhaseAtBin(const Complex& fft1, const Complex& fft2, int bin);
};

// Delay solver for calculating optimal delay values
class DelaySolver {
public:
    DelaySolver();
    
    // Solve for delay between two signals
    double SolveDelay(const AudioBuffer& reference, const AudioBuffer& delayed, double sampleRate);
    
    // Solve multiple delays for multichannel systems
    Vector<double> SolveDelays(const Vector<AudioBuffer>& referenceSignals, 
                              const Vector<AudioBuffer>& delayedSignals, double sampleRate);
    
    // Calculate delay for distance (speed of sound = 343 m/s)
    double CalculateDelayForDistance(double distanceMeters);
    
    // Set the algorithm to use
    void SetAlgorithm(int algo); // 0=Cross-correlation, 1=Phase-based, 2=Least-squares
    
private:
    int algorithm; // 0=Cross-correlation, 1=Phase-based, 2=Least-squares
};

} // namespace Calibration

