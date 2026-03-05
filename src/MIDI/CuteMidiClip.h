#ifndef _MIDI_CuteMidiClip_h_
#define _MIDI_CuteMidiClip_h_

class CuteMidiEditorForm;
class CuteMidiEditCommand;
class CuteMidiSequence;
class CuteTrack;

class CuteMidiClip : public CuteClip {
public:
    struct Key : Moveable<Key> {
        String filename;
        unsigned long clip_offset = 0;
        unsigned long clip_length = 0;
        unsigned short track_channel = 0;
        unsigned short midi_channel = 0;
        bool operator==(const Key& other) const;
        unsigned GetHashValue() const;
    };

    struct FileKey : Moveable<FileKey> {
        String filename;
        unsigned short track_channel = 0;
        bool operator==(const FileKey& other) const;
        unsigned GetHashValue() const;
    };

    struct Data {
        int format = 0;
        unsigned short channel = 0;
        int bank_sel_method = 0;
        One<CuteMidiSequence> sequence;
    };

    CuteMidiClip(CuteTrack* track = nullptr);
    CuteMidiClip(const CuteMidiClip& clip);
    ~CuteMidiClip();

    void Open();
    bool CreateMidiFile(const String& filename, int track_channel = 0);
    bool OpenMidiFile(const String& filename, int track_channel = 0, int mode = 0);

    void SetTrackChannel(unsigned short track_channel);
    unsigned short GetTrackChannel() const;
    unsigned short GetFormat() const;
    void SetSessionFlag(bool session_flag);
    bool IsSessionFlag() const;
    void SetRevision(unsigned short revision);
    unsigned short GetRevision() const;
    String CreateFilePathRevision(bool force = false);
    CuteMidiSequence* GetSequence() const;

private:
    void SetFilename(const String& filename) { this->filename = filename; }
    const String& GetFilename() const { return filename; }

    CuteTrack* track = nullptr;
    String filename;
    One<Data> data;
    unsigned short track_channel = 0;
    bool session_flag = false;
    unsigned short revision = 0;
};

#endif
