#ifndef _AudioCore_CuteAudioEngine_h_
#define _AudioCore_CuteAudioEngine_h_

class CuteAudioBus;
class CuteAudioBuffer;
class CuteAudioMonitor;
class CuteAudioFile;
class CuteAudioExportBuffer;
class CutePluginList;
class CuteCurveList;
class CuteTrack;
class CuteDocument;
class CuteXmlElement;

class CuteAudioEngineProxy {
public:
    void NotifyShutEvent();
    void NotifyXrunEvent();
    void NotifyPortEvent();
    void NotifyBuffEvent(unsigned int buffer_size);
    void NotifySessEvent(void* session_arg);
    void NotifySyncEvent(unsigned long play_head, bool is_playing);
    void NotifyPropEvent();
    void NotifySelfEvent();
};

class CuteAudioEngine {
public:
    enum CountInMode { CountInNone = 0, CountInPlayback, CountInRecording };

    CuteAudioEngine();
    bool Init();
    const CuteAudioEngineProxy* GetProxy() const;
    int Process(unsigned int frame_count);
    void Timebase(unsigned long play_head, int is_new_pos);
    bool LoadElement(CuteDocument* document, CuteXmlElement* element);
    bool SaveElement(CuteDocument* document, CuteXmlElement* element) const;
    void SetSessionId(const String& session_id);
    const String& GetSessionId() const;
    unsigned int GetSampleRate() const;
    unsigned int GetBufferSize() const;
    unsigned int GetBufferSizeEx() const;
    unsigned int GetBufferOffset() const;
    unsigned int GetBlockSize() const;
    void SetMasterAutoConnect(bool master_auto_connect);
    bool IsMasterAutoConnect() const;
    void SetFreewheel(bool freewheel);
    bool IsFreewheel() const;
    void SetExporting(bool exporting);
    bool IsExporting() const;
    unsigned long GetExportStart() const;
    unsigned long GetExportOffset() const;
    unsigned long GetExportLength() const;
    bool FileExport(const String& export_path, unsigned long export_start, unsigned long export_end, int export_format = -1);
    void TrackMute(CuteTrack* track, bool mute);
    void SetMetronome(bool metronome);
    bool IsMetronome() const;
    void SetMetroEnabled(bool metro_enabled);
    bool IsMetroEnabled() const;
    void SetMetroBus(bool metro_bus);
    bool IsMetroBus() const;
    void ResetMetroBus();
    void SetMetroAutoConnect(bool metro_auto_connect);
    bool IsMetroAutoConnect() const;
    void SetMetroBarFileName(const String& file_name);
    const String& GetMetroBarFileName() const;
    void SetMetroBarGain(float gain);
    float GetMetroBarGain() const;
    void SetMetroBeatFileName(const String& file_name);
    const String& GetMetroBeatFileName() const;
    void SetMetroBeatGain(float gain);
    float GetMetroBeatGain() const;
    void SetMetroOffset(unsigned long metro_offset);
    unsigned long GetMetroOffset() const;
    void ResetMetro(bool count_in = false);
    void SetCountIn(bool count_in);
    bool IsCountIn() const;
    void SetCountInMode(CountInMode count_in_mode);
    CountInMode GetCountInMode() const;

private:
    CuteAudioEngineProxy proxy;
    String session_id;
    String metro_bar_file_name;
    String metro_beat_file_name;
    unsigned int sample_rate = 44100;
    unsigned int buffer_size = 1024;
    unsigned int block_size = 64;
    unsigned int buffer_offset = 0;
    bool master_auto_connect = true;
    bool freewheel = false;
    bool exporting = false;
    bool metronome = false;
    bool metro_enabled = true;
    bool metro_bus = false;
    bool metro_auto_connect = true;
    bool count_in = false;
    CountInMode count_in_mode = CountInNone;
    float metro_bar_gain = 1.0f;
    float metro_beat_gain = 1.0f;
    unsigned long export_start = 0;
    unsigned long export_offset = 0;
    unsigned long export_length = 0;
    unsigned long metro_offset = 0;
};

#endif
