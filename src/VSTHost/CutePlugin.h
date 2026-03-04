#ifndef _VSTHost_CutePlugin_h_
#define _VSTHost_CutePlugin_h_

class CutePluginList;
class CutePluginType;
class CutePluginForm;
class CutePluginListView;

class CutePluginFile {
public:
    CutePluginFile();
    CutePluginFile(const String& filename);

    void SetFilename(const String& filename);
    const String& GetFilename() const;
    bool Open();
    void Close();
    bool IsOpen() const;
    void SetAutoUnload(bool auto_unload);
    bool IsAutoUnload() const;
    void AddRef();
    void RemoveRef();
    int GetRefCount() const;

    static CutePluginFile& AddFile(const String& filename);
    static void RemoveFile(const String& filename);
    static void ClearFiles();

private:
    String filename;
    bool is_open = false;
    bool auto_unload = true;
    int ref_count = 0;
};

class CutePluginType {
public:
    enum Hint {
        Any = 0,
        Ladspa,
        Dssi,
        Vst2,
        Vst3,
        Clap,
        Lv2,
        Insert,
        AuxSend,
        Control,
    };

    CutePluginType();

    void SetFile(CutePluginFile* file);
    CutePluginFile* GetFile() const;
    void SetIndex(int index);
    int GetIndex() const;
    void SetTypeHint(Hint type_hint);
    Hint GetTypeHint() const;
    void SetName(const String& name);
    const String& GetName() const;
    void SetLabel(const String& label);
    const String& GetLabel() const;
    void SetUniqueId(uint32 unique_id);
    uint32 GetUniqueId() const;
    void SetPortCounts(int audio_in_count, int audio_out_count, int midi_in_count, int midi_out_count, int control_in_count, int control_out_count);
    int GetAudioInputCount() const;
    int GetAudioOutputCount() const;
    int GetMidiInputCount() const;
    int GetMidiOutputCount() const;
    int GetControlInputCount() const;
    int GetControlOutputCount() const;
    int GetInstances() const;
    String GetAboutText() const;

    static String GetHintText(Hint type_hint);

private:
    CutePluginFile* file = nullptr;
    int index = -1;
    Hint type_hint = Any;
    String name;
    String label;
    uint32 unique_id = 0;
    int audio_input_count = 0;
    int audio_output_count = 0;
    int midi_input_count = 0;
    int midi_output_count = 0;
    int control_input_count = 0;
    int control_output_count = 0;
    int instances = 0;
};

class CutePlugin {
public:
    struct Program {
        int bank = 0;
        int program = 0;
        String name;
    };

    struct NoteName {
        int bank = 0;
        int program = 0;
        int note = 0;
        String name;
    };

    class Param {
    public:
        Param();

        void SetIndex(int index);
        int GetIndex() const;
        void SetName(const String& name);
        const String& GetName() const;
        void SetMinValue(double min_value);
        double GetMinValue() const;
        void SetMaxValue(double max_value);
        double GetMaxValue() const;
        void SetDefaultValue(double default_value);
        double GetDefaultValue() const;
        void SetValue(double value);
        double GetValue() const;
        void SetPreviousValue(double previous_value);
        double GetPreviousValue() const;
        void SetDecimalCount(int decimal_count);
        int GetDecimalCount() const;
        void SetFlags(bool bounded_below, bool bounded_above, bool integer_value, bool toggled, bool display_value);
        bool IsBoundedBelow() const;
        bool IsBoundedAbove() const;
        bool IsInteger() const;
        bool IsToggled() const;
        bool IsDisplay() const;
        String GetDisplayText() const;
        void Reset();

    private:
        int index = -1;
        String name;
        double min_value = 0.0;
        double max_value = 1.0;
        double default_value = 0.0;
        double value = 0.0;
        double previous_value = 0.0;
        int decimal_count = 2;
        bool bounded_below = false;
        bool bounded_above = false;
        bool integer_value = false;
        bool toggled = false;
        bool display_value = false;
    };

    class Property {
    public:
        Property();

        void SetKey(const String& key);
        const String& GetKey() const;
        void SetKeyIndex(int key_index);
        int GetKeyIndex() const;
        void SetValue(const Value& value);
        const Value& GetValue() const;
        void SetString(bool string_value);
        bool IsString() const;
        void SetPath(bool path_value);
        bool IsPath() const;
        void SetAutomatable(bool automatable);
        bool IsAutomatable() const;

    private:
        String key;
        int key_index = -1;
        Value value;
        bool string_value = false;
        bool path_value = false;
        bool automatable = false;
    };

    CutePlugin();
    virtual ~CutePlugin();

    void SetList(CutePluginList* list);
    CutePluginList* GetList() const;
    void SetType(CutePluginType* type);
    CutePluginType* GetType() const;
    void SetUniqueId(uint32 unique_id);
    uint32 GetUniqueId() const;
    void SetLabel(const String& label);
    const String& GetLabel() const;
    void SetAlias(const String& alias);
    const String& GetAlias() const;
    void SetActivated(bool activated);
    bool IsActivated() const;
    void SetChannelCount(int channel_count);
    int GetChannelCount() const;
    void AddParam(const Param& param);
    Vector<Param>& GetParams();
    const Vector<Param>& GetParams() const;
    void AddProperty(const Property& property);
    Vector<Property>& GetProperties();
    const Vector<Property>& GetProperties() const;
    void SetProgramList(const Vector<Program>& program_list);
    const Vector<Program>& GetProgramList() const;
    void SetNoteNameList(const Vector<NoteName>& note_name_list);
    const Vector<NoteName>& GetNoteNameList() const;
    void SetDirectAccessParamIndex(int direct_access_param_index);
    int GetDirectAccessParamIndex() const;
    void Reset();
    virtual bool Activate();
    virtual void Deactivate();
    virtual void Process();
    virtual bool OpenEditor();
    virtual void CloseEditor();
    bool IsEditorVisible() const;
    virtual bool OpenForm();
    virtual void CloseForm();
    bool IsFormVisible() const;
    virtual void UpdateListViews();

private:
    CutePluginList* list = nullptr;
    CutePluginType* type = nullptr;
    uint32 unique_id = 0;
    String label;
    String alias;
    bool activated = false;
    int channel_count = 0;
    Vector<Param> params;
    Vector<Property> properties;
    Vector<Program> program_list;
    Vector<NoteName> note_name_list;
    int direct_access_param_index = -1;
    bool editor_visible = false;
    bool form_visible = false;
};

class CutePluginList {
public:
    enum Flags {
        Audio = 1 << 0,
        Midi = 1 << 1,
        Track = 1 << 2,
        Bus = 1 << 3,
        Out = 1 << 4,
        In = 1 << 5,
        AudioTrack = Audio | Track,
        AudioBus = Audio | Bus,
        AudioInBus = Audio | Bus | In,
        AudioOutBus = Audio | Bus | Out,
        MidiTrack = Midi | Track,
        MidiBus = Midi | Bus,
        MidiInBus = Midi | Bus | In,
        MidiOutBus = Midi | Bus | Out,
    };

    class MidiProgramSubject {
    public:
        MidiProgramSubject();
        MidiProgramSubject(int bank, int program);

        void SetProgram(int bank, int program);
        int GetBank() const;
        int GetProgram() const;

    private:
        int bank = 0;
        int program = 0;
    };

    CutePluginList();

    void SetName(const String& name);
    const String& GetName() const;
    void SetFlags(int flags);
    int GetFlags() const;
    bool IsMidi() const;
    bool IsMidiBus() const;
    void SetChannelCount(int channel_count);
    int GetChannelCount() const;
    void AddPlugin(CutePlugin& plugin);
    void InsertPlugin(int index, CutePlugin& plugin);
    void MovePlugin(int from, int to);
    void RemovePlugin(int index);
    int GetPluginCount() const;
    CutePlugin* GetPlugin(int index);
    const CutePlugin* GetPlugin(int index) const;
    void AddView(CutePluginListView* view);
    void RemoveView(CutePluginListView* view);
    void SetMidiBank(int midi_bank);
    int GetMidiBank() const;
    void SetMidiProgram(int midi_program);
    int GetMidiProgram() const;
    void SetAudioOutputBusName(const String& audio_output_bus_name);
    const String& GetAudioOutputBusName() const;
    MidiProgramSubject& GetMidiProgramSubject();
    uint32 CreateUniqueId() const;

private:
    String name;
    int flags = 0;
    int channel_count = 0;
    Array<CutePlugin> plugin_list;
    Vector<CutePluginListView*> views;
    int midi_bank = 0;
    int midi_program = 0;
    String audio_output_bus_name;
    MidiProgramSubject midi_program_subject;
};

#endif
