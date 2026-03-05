#ifndef _ProjectWindow_CuteTrack_h_
#define _ProjectWindow_CuteTrack_h_

class CuteTrack {
public:
    enum TrackType {
        None = 0,
        Audio,
        Midi,
        Bus,
    };

    CuteTrack();

    void SetTrackId(int track_id);
    int GetTrackId() const;
    void SetTrackType(TrackType track_type);
    TrackType GetTrackType() const;
    void SetName(const String& name);
    const String& GetName() const;
    void SetColor(Color color);
    Color GetColor() const;
    void SetMuted(bool muted);
    bool IsMuted() const;
    void SetSolo(bool solo);
    bool IsSolo() const;
    void SetArmed(bool armed);
    bool IsArmed() const;

private:
    int track_id = -1;
    TrackType track_type = None;
    String name;
    Color color = Color(120, 120, 120);
    bool muted = false;
    bool solo = false;
    bool armed = false;
};

#endif
