#ifndef _ProjectWindow_CuteTrackTime_h_
#define _ProjectWindow_CuteTrackTime_h_

class CuteTrackTime {
public:
    CuteTrackTime();

    void SetFrame(int64 frame);
    int64 GetFrame() const;
    void SetTick(int64 tick);
    int64 GetTick() const;
    void SetBar(int bar);
    int GetBar() const;
    void SetBeat(int beat);
    int GetBeat() const;
    String AsText() const;

private:
    int64 frame = 0;
    int64 tick = 0;
    int bar = 0;
    int beat = 0;
};

#endif
