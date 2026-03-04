#ifndef _AudioCore_CuteAudioSndFile_h_
#define _AudioCore_CuteAudioSndFile_h_

class CuteAudioSndFile {
public:
    CuteAudioSndFile();
    ~CuteAudioSndFile();
    bool Open(const String& file_name, int mode = 0);
    void Close();
    int Read(float** frames, unsigned int frame_count);
    int Write(float** frames, unsigned int frame_count);
    bool Seek(unsigned long offset);
    String GetDescription() const;

private:
    String file_name;
    int mode = 0;
};

#endif
