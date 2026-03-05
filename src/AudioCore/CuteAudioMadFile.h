#ifndef _AudioCore_CuteAudioMadFile_h_
#define _AudioCore_CuteAudioMadFile_h_

class CuteAudioMadFile : public CuteAudioFile {
public:
    CuteAudioMadFile();
    ~CuteAudioMadFile();
    bool Open(const String& file_name, int mode = ReadMode);
    void Close();
    int Read(float** frames, unsigned int frame_count);
    int Write(float** frames, unsigned int frame_count);
    bool Seek(unsigned long offset);
    int GetMode() const;
    unsigned short GetChannels() const;
    unsigned long GetFrames() const;
    unsigned int GetSampleRate() const;
    String GetDescription() const;

private:
    String file_name;
    int mode = 0;
    unsigned short channels = 2;
    unsigned long frames = 0;
    unsigned int sample_rate = 44100;
};

#endif
