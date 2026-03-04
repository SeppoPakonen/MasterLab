#ifndef _AudioEditing_CuteClipForm_h_
#define _AudioEditing_CuteClipForm_h_

class CuteClip;
class CuteClipForm : public TopWindow {
public:
    typedef CuteClipForm CLASSNAME;
    CuteClipForm();
    void SetClip(CuteClip* clip);
    CuteClip* GetClip() const;
    bool IsClipNew() const;
    bool IsDirty() const;
    void Accept();
    void Reject();
    void BrowseFile();
    void StabilizeForm();

private:
    CuteClip* clip = nullptr;
    bool clip_new = false;
    int dirty_count = 0;
    int dirty_setup = 0;
};

#endif
