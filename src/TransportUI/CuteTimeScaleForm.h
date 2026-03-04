#ifndef _TransportUI_CuteTimeScaleForm_h_
#define _TransportUI_CuteTimeScaleForm_h_

class CuteTimeScaleForm : public TopWindow {
public:
    typedef CuteTimeScaleForm CLASSNAME;

    enum DirtyFlags {
        AddNode = 1 << 0,
        UpdateNode = 1 << 1,
        RemoveNode = 1 << 2,
        AddMarker = 1 << 3,
        UpdateMarker = 1 << 4,
        RemoveMarker = 1 << 5,
        AddKeySignature = 1 << 6,
        UpdateKeySignature = 1 << 7,
    };

    CuteTimeScaleForm();

    void SetTimeScale(CuteTimeScale* time_scale);
    CuteTimeScale* GetTimeScale() const;
    void SetFrame(int64 frame);
    int64 GetFrame() const;
    int GetBar() const;
    bool IsDirty() const;

private:
    CuteTimeScale* time_scale = nullptr;
    int64 frame = 0;
    int dirty_flags = 0;
};

#endif
