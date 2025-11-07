#ifndef _DSP_RackInfrastructure_h_
#define _DSP_RackInfrastructure_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <AudioFX/SpatialDSP.h>  // For some of the components

namespace DSP {

// RackHost - manages a collection of DSP modules in a rack-like structure
class RackHost {
public:
    typedef RackHost CLASSNAME;
    
    RackHost();
    virtual ~RackHost();
    
    // Define a RackSlot for hosting DSP modules
    struct RackSlot : public Upp::Moveable<RackSlot> {
        Upp::String id;
        Upp::String name;
        Upp::String module_type;  // "effect", "synth", "utility", etc.
        bool is_active;
        double position_x;
        double position_y;
        bool bypassed;
        double gain;
        double pan;
        
        RackSlot() : is_active(true), position_x(0.0), position_y(0.0), 
                     bypassed(false), gain(1.0), pan(0.0) {}
    };
    
    // Add a slot to the rack
    void AddSlot(const Upp::String& slot_id, const Upp::String& module_type = "generic");
    
    // Remove a slot from the rack
    bool RemoveSlot(const Upp::String& slot_id);
    
    // Activate/deactivate a slot
    void ActivateSlot(const Upp::String& slot_id, bool active = true);
    void BypassSlot(const Upp::String& slot_id, bool bypass = true);
    
    // Get/set slot parameters
    void SetSlotPosition(const Upp::String& slot_id, double x, double y);
    void SetSlotGain(const Upp::String& slot_id, double gain_db);
    void SetSlotPan(const Upp::String& slot_id, double pan);  // -1.0 to 1.0
    
    // Get rack slots
    const Upp::Vector<RackSlot>& GetSlots() const { return slots; }
    RackSlot* GetSlot(const Upp::String& slot_id);
    
    // Connect slots in the rack
    bool ConnectSlots(const Upp::String& source_slot, const Upp::String& dest_slot, double gain = 1.0);
    bool DisconnectSlots(const Upp::String& source_slot, const Upp::String& dest_slot);
    
    // Process audio through the rack
    void Process(const Upp::Vector<double>& input, Upp::Vector<double>& output, double sample_rate);
    
    // Session management
    void SaveRack(const Upp::String& filename);
    bool LoadRack(const Upp::String& filename);
    
    // Event callbacks
    virtual void OnSlotAdded(const String& slot_id) {}
    virtual void OnSlotRemoved(const String& slot_id) {}
    virtual void OnSlotConnected(const String& source, const String& dest) {}
    virtual void OnSlotDisconnected(const String& source, const String& dest) {}
    
private:
    Upp::Vector<RackSlot> slots;
    Upp::VectorMap<Upp::String, int> slot_ids;  // Maps slot IDs to indices
    
    struct Connection : public Upp::Moveable<Connection> {
        Upp::String source_slot;
        Upp::String dest_slot;
        double gain;
        
        Connection(const Upp::String& src, const Upp::String& dst, double g = 1.0) 
            : source_slot(src), dest_slot(dst), gain(g) {}
    };
    Upp::Vector<Connection> connections;
};

// ChainNode - represents a node in an audio processing chain
class ChainNode {
public:
    typedef ChainNode CLASSNAME;
    
    ChainNode();
    virtual ~ChainNode();
    
    enum NodeType {
        INPUT_NODE,
        PROCESSOR_NODE,
        OUTPUT_NODE,
        MIXER_NODE,
        ROUTER_NODE
    };
    
    struct NodeInfo : public Upp::Moveable<NodeInfo> {
        Upp::String id;
        Upp::String name;
        NodeType type;
        Upp::String plugin_id;  // For processor nodes
        int input_channels;
        int output_channels;
        bool is_active;
        bool is_muted;
        double gain_db;    // Gain in dB
        double pan;        // Pan position (-1.0 to 1.0)
        
        NodeInfo() : type(PROCESSOR_NODE), input_channels(2), output_channels(2),
                     is_active(true), is_muted(false), gain_db(0.0), pan(0.0) {}
    };
    
    // Initialize the node
    void Initialize(const NodeInfo& info);
    
    // Process audio through the node
    virtual void Process(const Upp::Vector<double*>& inputs, int input_count,
                        Upp::Vector<double*>& outputs, int output_count,
                        int sample_count, double sample_rate);
    
    // Get node information
    const NodeInfo& GetInfo() const { return info; }
    Upp::String GetId() const { return info.id; }
    NodeType GetType() const { return info.type; }
    
    // Node state control
    void SetActive(bool active) { info.is_active = active; }
    void SetMuted(bool muted) { info.is_muted = muted; }
    void SetGain(double gain_db) { info.gain_db = gain_db; }
    void SetPan(double pan) { info.pan = pan; }
    
    bool IsActive() const { return info.is_active; }
    bool IsMuted() const { return info.is_muted; }
    double GetGain() const { return info.gain_db; }
    double GetPan() const { return info.pan; }
    
    // Specialized processor methods (to be overridden by derived classes)
    virtual void SetParameter(const Upp::String& param_id, double value);
    virtual double GetParameter(const Upp::String& param_id) const;
    
protected:
    NodeInfo info;
};

// MacroMapper - maps multiple parameters to a single macro control
class MacroMapper {
public:
    typedef MacroMapper CLASSNAME;
    
    MacroMapper();
    virtual ~MacroMapper();
    
    // Define a mapping
    struct ParameterMapping : public Upp::Moveable<ParameterMapping> {
        Upp::String parameter_id;      // ID of parameter to map
        Upp::String parameter_name;    // Human-readable name
        Upp::String module_id;         // Which module contains the parameter
        double min_value;         // Min value after mapping
        double max_value;         // Max value after mapping
        double mapped_value;      // Current mapped value
        
        ParameterMapping() : min_value(0.0), max_value(1.0), mapped_value(0.0) {}
    };
    
    // Add a parameter to the macro
    void AddParameter(const Upp::String& macro_name, const ParameterMapping& mapping);
    
    // Remove a parameter from the macro
    bool RemoveParameter(const Upp::String& macro_name, const Upp::String& param_id);
    
    // Set macro value (0.0 to 1.0), which updates all mapped parameters
    void SetMacroValue(const Upp::String& macro_name, double value);
    
    // Get current value of a mapped parameter
    double GetMappedValue(const Upp::String& macro_name, const Upp::String& param_id) const;
    
    // Get all mappings for a macro
    const Upp::Vector<ParameterMapping>& GetMappings(const Upp::String& macro_name) const;
    
    // Get all macro names
    Upp::Vector<Upp::String> GetMacroNames() const;
    
    // Update all mapped parameters (typically called during audio processing)
    void UpdateMappings(const Upp::String& macro_name);
    
private:
    Upp::VectorMap<Upp::String, Upp::Vector<ParameterMapping>> macros;
    Upp::VectorMap<Upp::String, double> macro_values;
};

// PresetBrowser - browse and manage presets for rack modules
class PresetBrowser {
public:
    typedef PresetBrowser CLASSNAME;
    
    PresetBrowser();
    virtual ~PresetBrowser();
    
    // Preset information
    struct PresetInfo : public Upp::Moveable<PresetInfo> {
        Upp::String id;
        Upp::String name;
        Upp::String category;
        Upp::String author;
        Upp::String description;
        Upp::String module_type;  // What type of module this preset is for
        Upp::String file_path;
        Upp::Time creation_time;
        Upp::Time modification_time;
        
        PresetInfo() {}
    };
    
    // Add a preset to the browser
    void AddPreset(const PresetInfo& preset);
    
    // Remove a preset
    bool RemovePreset(const Upp::String& preset_id);
    
    // Browse presets
    Upp::Vector<PresetInfo> GetPresetsByCategory(const Upp::String& category) const;
    Upp::Vector<PresetInfo> GetPresetsByAuthor(const Upp::String& author) const;
    Upp::Vector<PresetInfo> GetPresetsByModuleType(const Upp::String& module_type) const;
    Upp::Vector<PresetInfo> GetAllPresets() const;
    
    // Search presets
    Upp::Vector<PresetInfo> SearchPresets(const Upp::String& query) const;
    
    // Load preset into a rack module
    bool ApplyPreset(const Upp::String& preset_id, RackHost& rack, const Upp::String& slot_id);
    bool ApplyPreset(const Upp::String& preset_id, ChainNode& node);
    
    // Save current module state as preset
    bool SavePreset(const Upp::String& preset_id, const Upp::String& preset_name, 
                   const RackHost& rack, const Upp::String& slot_id);
    bool SavePreset(const Upp::String& preset_id, const Upp::String& preset_name, 
                   const ChainNode& node);
    
    // Load preset library from a file
    bool LoadPresetLibrary(const Upp::String& filepath);
    
    // Save preset library to a file
    void SavePresetLibrary(const Upp::String& filepath) const;
    
    // Get preset by ID
    const PresetInfo* GetPreset(const Upp::String& preset_id) const;
    
private:
    Upp::Vector<PresetInfo> presets;
    Upp::VectorMap<Upp::String, int> preset_lookup;  // Maps preset IDs to indices
};

// LatencyManager - manages latency compensation across the rack
class LatencyManager {
public:
    typedef LatencyManager CLASSNAME;
    
    LatencyManager();
    virtual ~LatencyManager();
    
    // Register a module with its latency
    void RegisterModule(const String& module_id, int latency_samples);
    
    // Unregister a module
    void UnregisterModule(const String& module_id);
    
    // Calculate total latency for a signal path
    int CalculatePathLatency(const Vector<String>& module_chain) const;
    
    // Compensate latency for a signal (adds delay to shorter paths)
    void CompensateLatency(const Vector<String>& module_ids, 
                          Vector<double>& signal, int sample_count, 
                          double sample_rate);
    
    // Get latency for a specific module
    int GetModuleLatency(const String& module_id) const;
    
    // Apply look-ahead compensation
    void ApplyLookaheadCompensation(Vector<double>& signal, int samples_ahead);
    
    // Synchronize latencies across parallel paths
    void SynchronizePathLatencies(const Vector<Vector<String>>& parallel_paths);
    
    // Get global latency compensation
    int GetGlobalCompensation() const { return global_compensation; }
    
    // Reset latency compensation
    void Reset();
    
private:
    VectorMap<String, int> module_latencies;
    int global_compensation;
    
    // Internal buffer for lookahead compensation
    Vector<double> lookahead_buffer;
    int buffer_position;
};

// SessionManager - manages StudioRack/StudioVerse sessions
class SessionManager {
public:
    typedef SessionManager CLASSNAME;
    
    SessionManager();
    virtual ~SessionManager();
    
    // Session information
    struct SessionInfo : public Upp::Moveable<SessionInfo> {
        Upp::String id;
        Upp::String name;
        Upp::String description;
        Upp::String project_file;
        Upp::String rack_template;
        Upp::Vector<Upp::String> active_presets;
        Upp::ValueMap global_settings;
        int sample_rate;
        int buffer_size;
        Upp::Time creation_time;
        Upp::Time modification_time;
        
        SessionInfo() : sample_rate(44100), buffer_size(512) {}
    };
    
    // Create a new session
    bool CreateNewSession(const String& session_id, const String& name, 
                         const String& description = "");
    
    // Load a saved session
    bool LoadSession(const String& filepath);
    
    // Save current session
    bool SaveSession(const String& filepath);
    
    // Close current session
    void CloseSession();
    
    // Get current session info
    const SessionInfo* GetCurrentSession() const { return current_session; }
    
    // Add/remove modules to/from session
    bool AddModuleToSession(const String& module_id, const String& module_type);
    bool RemoveModuleFromSession(const String& module_id);
    
    // Apply session settings to rack
    bool ApplyToRack(RackHost& rack_host) const;
    
    // Load from rack to session
    bool LoadFromRack(const RackHost& rack_host);
    
    // Session lifecycle events
    virtual void OnSessionCreated(const Upp::String& session_id) {}
    virtual void OnSessionLoaded(const Upp::String& filepath) {}
    virtual void OnSessionSaved(const Upp::String& filepath) {}
    virtual void OnSessionClosed() {}
    
    // Get session templates
    Upp::Vector<Upp::String> GetAvailableTemplates() const;
    
private:
    SessionInfo* current_session;  // Using raw pointer instead of std::unique_ptr to avoid <memory> include
    Upp::VectorMap<Upp::String, SessionInfo> session_templates;
};

}  // namespace DSP

// NET namespace for TransportLayer (network transport for distributed processing)
namespace NET {

class TransportLayer {
public:
    typedef TransportLayer CLASSNAME;
    
    TransportLayer();
    virtual ~TransportLayer();
    
    // Network protocols for DSP communication
    enum Protocol {
        OSC,        // Open Sound Control
        MIDI,       // Musical Instrument Digital Interface
        HTTP,       // Hypertext Transfer Protocol
        UDP_STREAM, // UDP audio streaming
        TCP_CTRL    // TCP control messaging
    };
    
    // Initialize the transport layer
    bool Initialize(Protocol protocol, const String& endpoint = "");
    
    // Send/receive data
    virtual bool SendData(const void* data, int size, const String& destination);
    virtual int ReceiveData(void* buffer, int max_size, String& source);
    
    // Send audio data
    virtual bool SendAudio(const Vector<double>& audio_data, const String& destination);
    
    // Receive audio data
    virtual int ReceiveAudio(Vector<double>& audio_data, const String& sender);
    
    // Check connection state
    bool IsConnected() const { return connected; }
    void SetConnected(bool state) { connected = state; }
    
    // Performance statistics
    double GetJitter() const;
    int GetLatency() const;
    double GetPacketLoss() const;
    
    // Close the transport layer
    void Close();
    
protected:
    Protocol protocol;
    String endpoint;
    bool connected;
    Upp::ValueMap settings;  // Protocol-specific settings
    
    // Performance monitoring
    Vector<Time> timestamps;
    Vector<int> latencies;
};

}  // namespace NET

#endif