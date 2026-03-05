#ifndef _TransportUI_CuteTimeScale_h_
#define _TransportUI_CuteTimeScale_h_

class CuteTimeScale {
public:
    enum DisplayFormat {
        Frames = 0,
        Time,
        BBT,
    };

    enum {
        MinAccidentals = -9,
        MaxAccidentals = 9,
    };

    class Node : Moveable<Node> {
    public:
        Node();
        Node(int64 frame, double tempo, int beats_per_bar, int beat_divisor);

        void Update();
        void Reset();
        void SetTempoEx(double tempo);
        double GetTempoEx() const;
        int64 TickSnap(int64 tick) const;

        int64 frame = 0;
        int bar = 0;
        int beat = 0;
        int64 tick = 0;
        int pixel = 0;
        double tempo = 120.0;
        int beat_type = 4;
        int beats_per_bar = 4;
        int beat_divisor = 4;
        int ticks_per_beat = 960;
    };

    class Cursor {
    public:
        Cursor(CuteTimeScale* time_scale = nullptr);

        CuteTimeScale* GetTimeScale() const;
        void Reset();
        void SeekFrame(int64 frame);
        void SeekBar(int bar);
        void SeekBeat(int beat);
        void SeekTick(int64 tick);
        void SeekPixel(int pixel);
        int64 GetFrame() const;

    private:
        CuteTimeScale* time_scale = nullptr;
        int64 frame = 0;
    };

    class Marker : Moveable<Marker> {
    public:
        Marker();
        Marker(int64 frame, int bar, const String& text, Color color);
        Marker(int64 frame, int bar, int accidentals, int mode);

        int64 frame = 0;
        int bar = 0;
        String text;
        Color color;
        int accidentals = 0;
        int mode = 0;
    };

    class MarkerCursor {
    public:
        MarkerCursor(CuteTimeScale* time_scale = nullptr);

        void Reset();
        void SeekFrame(int64 frame);
        int GetPosition() const;
        bool IsFirst() const;
        bool IsLast() const;

    private:
        CuteTimeScale* time_scale = nullptr;
        int position = -1;
    };

    CuteTimeScale();

    void Reset();
    void Clear();
    void Sync();
    void Copy(const CuteTimeScale& time_scale);
    void SetSampleRate(int sample_rate);
    int GetSampleRate() const;
    void SetTicksPerBeat(int ticks_per_beat);
    int GetTicksPerBeat() const;
    void SetPixelsPerBeat(int pixels_per_beat);
    int GetPixelsPerBeat() const;
    void SetSnapPerBeat(int snap_per_beat);
    int GetSnapPerBeat() const;
    void SetDisplayFormat(DisplayFormat display_format);
    DisplayFormat GetDisplayFormat() const;
    void AddNode(const Node& node);
    void UpdateNode(int index, const Node& node);
    void RemoveNode(int index);
    int GetNodeCount() const;
    const Node& GetNode(int index) const;
    void AddMarker(const Marker& marker);
    void AddKeySignature(const Marker& marker);
    void UpdateMarker(int index, const Marker& marker);
    void RemoveMarker(int index);
    int GetMarkerCount() const;
    const Marker& GetMarker(int index) const;
    String GetTextFromFrame(int64 frame) const;
    int64 GetFrameFromText(const String& text) const;
    int64 GetTickFromFrame(int64 frame) const;
    int64 GetFrameFromTick(int64 tick) const;

private:
    int sample_rate = 48000;
    int ticks_per_beat = 960;
    int pixels_per_beat = 120;
    int snap_per_beat = 4;
    DisplayFormat display_format = Time;
    Vector<Node> nodes;
    Vector<Marker> markers;
};

class CuteTempoCursor {
public:
    CuteTempoCursor();

    void Clear();
    void Seek(CuteTimeScale* time_scale, int64 frame);
    double GetTempo() const;

private:
    double tempo = 120.0;
};

#endif
