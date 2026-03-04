#ifndef _AudioCore_CuteSessionCursor_h_
#define _AudioCore_CuteSessionCursor_h_

class CuteSessionCursor {
public:
    CuteSessionCursor(CuteSession* session = nullptr, int64 frame = 0);

    CuteSession* GetSession() const;
    void Seek(int64 frame, bool sync = false);
    int64 GetFrame() const;
    int64 GetFrameTime() const;
    int64 GetFrameTimeEx() const;
    void SetSyncType(int sync_type);
    int GetSyncType() const;
    void AddTrack(const String& track_name);
    void UpdateTrack(int index, const String& track_name);
    void RemoveTrack(int index);

private:
    CuteSession* session = nullptr;
    int64 frame = 0;
    int sync_type = 0;
    Vector<String> cursor_tracks;
};

#endif
