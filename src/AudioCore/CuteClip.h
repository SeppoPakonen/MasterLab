#ifndef _AudioCore_CuteClip_h_
#define _AudioCore_CuteClip_h_

class CuteTrack;
class CuteClip {
public:
    enum FadeMode { FadeIn = 0, FadeOut = 1 };

    CuteClip();
    virtual ~CuteClip();
    void SetTrack(CuteTrack* track);
    CuteTrack* GetTrack() const;
    void SetName(const String& name);
    const String& GetName() const;
    void SetClipStart(unsigned long clip_start);
    unsigned long GetClipStart() const;
    void SetClipLength(unsigned long clip_length);
    unsigned long GetClipLength() const;
    void SetClipSelected(bool clip_selected);
    bool IsClipSelected() const;

private:
    CuteTrack* track = nullptr;
    String name;
    unsigned long clip_start = 0;
    unsigned long clip_length = 0;
    bool clip_selected = false;
};

#endif
