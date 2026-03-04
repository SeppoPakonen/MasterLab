#ifndef _AudioCore_CuteAudioFile_h_
#define _AudioCore_CuteAudioFile_h_

class CuteAudioFile {
public:
    enum Mode { None = 0, ReadMode = 1, WriteMode = 2 };
    virtual ~CuteAudioFile() {}
    virtual bool Open(const String& file_name, int mode = ReadMode) = 0;
    virtual int Read(float** frames, unsigned int frame_count) = 0;
    virtual int Write(float** frames, unsigned int frame_count) = 0;
    virtual bool Seek(unsigned long offset) = 0;
    virtual void Close() = 0;
    virtual int GetMode() const = 0;
    virtual unsigned short GetChannels() const = 0;
    virtual unsigned long GetFrames() const = 0;
    virtual unsigned int GetSampleRate() const = 0;
};

class CuteAudioFileFactory {
public:
    enum FileType { SndFile, VorbisFile, MadFile };

    struct FileFormat {
        FileType type = SndFile;
        String name;
        String ext;
        int data = 0;
    };

    typedef Vector<FileFormat> FileFormats;
    typedef VectorMap<String, FileFormat> FileTypes;

    CuteAudioFileFactory();
    ~CuteAudioFileFactory();

    static CuteAudioFileFactory* GetInstance();
    static const FileFormats& GetFormats();
    static const FileTypes& GetTypes();
    static const Vector<String>& GetFilters();
    static const Vector<String>& GetExtensions();
    static void SetDefaultType(const String& ext, int type, int format = 0, int quality = 4);
    static String GetDefaultExt();
    static bool IsValidFormat(const FileFormat* format, int file_format);
    static CuteAudioFile* CreateAudioFile(const String& file_name, unsigned short channels = 0, unsigned int sample_rate = 0, unsigned int buffer_size = 0, int format = -1);

private:
    CuteAudioFile* NewAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format);
    static int GetDefaultFormat();
    static int GetDefaultQuality();

    FileFormats formats;
    FileTypes types;
    Vector<String> filters;
    Vector<String> extensions;
    int default_format = 0;
    int default_quality = 4;
    int default_type = 0;
    String default_ext;
    static CuteAudioFileFactory* instance;
};

#endif
