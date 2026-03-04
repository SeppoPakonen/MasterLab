#ifndef _AudioEditing_CuteTempoAdjustForm_h_
#define _AudioEditing_CuteTempoAdjustForm_h_

class CuteTempoAdjustForm : public TopWindow {
public:
    typedef CuteTempoAdjustForm CLASSNAME;

    class ClipWidget : public ParentCtrl {
    public:
        typedef ClipWidget CLASSNAME;
        ClipWidget();
    };

    CuteTempoAdjustForm();

    void SetClip(CuteAudioClip* clip);
    CuteAudioClip* GetClip() const;
    CuteAudioClip* GetAudioClip() const;
    void SetRangeStart(int64 range_start);
    int64 GetRangeStart() const;
    void SetRangeLength(int64 range_length);
    int64 GetRangeLength() const;
    void SetRangeBeats(int range_beats);
    int GetRangeBeats() const;
    double GetTempo() const;
    int GetBeatsPerBar() const;
    int GetBeatDivisor() const;
    CuteTimeScale* GetTimeScale() const;

private:
    CuteAudioClip* clip = nullptr;
    CuteTimeScale* time_scale = nullptr;
    int64 range_start = 0;
    int64 range_length = 0;
    int range_beats = 4;
    double tempo = 120.0;
    int beats_per_bar = 4;
    int beat_divisor = 4;
    ClipWidget clip_widget;
};

#endif
