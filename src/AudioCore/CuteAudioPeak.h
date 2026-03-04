#ifndef _AudioCore_CuteAudioPeak_h_
#define _AudioCore_CuteAudioPeak_h_

class CuteAudioPeak {
public:
    CuteAudioPeak();
    ~CuteAudioPeak();
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
