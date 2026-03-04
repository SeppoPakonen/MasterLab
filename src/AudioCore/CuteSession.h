#ifndef _AudioCore_CuteSession_h_
#define _AudioCore_CuteSession_h_

class CuteFiles;
class CuteSessionCursor;
class CuteTimeScale;
class CuteTrack;

class CuteSession {
public:
    struct Properties {
        Properties();

        void Clear();
        Properties& Copy(const Properties& properties);

        String session_dir;
        String session_name;
        String description;
        int sample_rate = 48000;
    };

    class Document {
    public:
        Document(CuteSession* session = nullptr, CuteFiles* files = nullptr);

        CuteSession* GetSession() const;
        CuteFiles* GetFiles() const;

    private:
        CuteSession* session = nullptr;
        CuteFiles* files = nullptr;
    };

    CuteSession();

    bool Init();
    bool Open();
    void Close();
    void Clear();
    void SetSessionDir(const String& session_dir);
    const String& GetSessionDir() const;
    void SetSessionName(const String& session_name);
    const String& GetSessionName() const;
    Properties& GetProperties();
    const Properties& GetProperties() const;
    void AddTrack(const String& track_name);
    void InsertTrack(int index, const String& track_name);
    void MoveTrack(int from, int to);
    void UnlinkTrack(int index);
    int GetTrackCount() const;
    const String& GetTrackName(int index) const;
    CuteSessionCursor* CreateSessionCursor(int64 frame = 0);

private:
    Properties properties;
    Vector<String> track_names;
};

#endif
