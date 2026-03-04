#ifndef _MIDI_CuteMidiManager_h_
#define _MIDI_CuteMidiManager_h_

class CuteTimeScale;
class CutePluginList;
class CutePlugin;
class CuteAudioMonitor;
class CuteAudioOutputMonitor;
class CuteAudioBus;
class CuteMidiBus;
class CuteSubject;

class CuteMidiSyncItem {
public:
    virtual ~CuteMidiSyncItem() {}
    virtual void ProcessSync() {}
    void SetWaitSync(bool wait_sync) { this->wait_sync = wait_sync; }
    bool IsWaitSync() const { return wait_sync; }
private:
    bool wait_sync = false;
};

class CuteMidiInputBuffer : public CuteMidiBuffer {
public:
    CuteMidiInputBuffer(unsigned int buffer_size = MinBufferSize);
};

class CuteMidiOutputBuffer : public CuteMidiSyncItem {
public:
    CuteMidiOutputBuffer();
    void ProcessSync() override;
};

class CuteMidiManager : public CuteList<CuteMidiManager>::Link {
public:
    CuteMidiManager();
    ~CuteMidiManager();
    void Open();
    void Close();
    bool IsOpen() const;
    void ProcessSync();

private:
    bool opened = false;
};

#endif
