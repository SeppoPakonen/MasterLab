#ifndef _AudioEditing_CuteTakeRangeForm_h_
#define _AudioEditing_CuteTakeRangeForm_h_

class CuteTakeRangeForm : public TopWindow {
public:
    typedef CuteTakeRangeForm CLASSNAME;

    CuteTakeRangeForm();

    void SetClip(CuteAudioClip* clip);
    CuteAudioClip* GetClip() const;
    int64 GetTakeStart() const;
    int64 GetTakeEnd() const;
    int GetCurrentTake() const;

private:
    CuteAudioClip* clip = nullptr;
    int64 take_start = 0;
    int64 take_end = 0;
    int current_take = 0;
};

#endif
