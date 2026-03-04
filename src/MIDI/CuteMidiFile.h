#ifndef _MIDI_CuteMidiFile_h_
#define _MIDI_CuteMidiFile_h_

class CuteTimeScale;
class CuteMidiSequence;

class CuteMidiFile {
public:
    enum { None = 0, Read = 1, Write = 2 };

    struct TrackInfo {
        unsigned int length = 0;
        unsigned long offset = 0;
    };

    CuteMidiFile();
    ~CuteMidiFile();

    bool Open(const String& filename, int mode = Read);
    void Close();
    const String& GetFilename() const;
    int GetMode() const;
    unsigned short GetFormat() const;
    unsigned short GetTracks() const;
    unsigned short GetTicksPerBeat() const;
    CuteMidiFileTempo* GetTempoMap() const;
    bool ReadTracks(Vector<CuteMidiSequence*>& seqs, unsigned short track_channel = 0);
    bool ReadTrack(CuteMidiSequence* seq, unsigned short track_channel);
    unsigned long ReadTrackDuration(unsigned short track_channel);
    bool WriteHeader(unsigned short format, unsigned short tracks, unsigned short ticks_per_beat);
    bool WriteTracks(const Vector<CuteMidiSequence*>& seqs);
    bool WriteTrack(CuteMidiSequence* seq);
    static bool SaveCopyFile(const String& new_filename, const String& old_filename, unsigned short track_channel, unsigned short format, CuteMidiSequence* seq, CuteTimeScale* time_scale = nullptr, unsigned long time_offset = 0);
    static String CreateFilePathRevision(const String& filename, int revision = 0);

private:
    String filename;
    int mode = None;
    unsigned long offset = 0;
    unsigned short format = 0;
    unsigned short tracks = 0;
    unsigned short ticks_per_beat = 960;
    Vector<TrackInfo> track_info;
    One<CuteMidiFileTempo> tempo_map;
};

#endif
