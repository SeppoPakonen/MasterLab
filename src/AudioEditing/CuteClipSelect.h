#ifndef _AudioEditing_CuteClipSelect_h_
#define _AudioEditing_CuteClipSelect_h_

class CuteClip;
class CuteTrack;

class CuteClipSelect {
public:
    struct Item {
        Rect rect;
        unsigned long offset = 0;
    };

    CuteClipSelect();
    ~CuteClipSelect();
    void SelectItem(CuteClip* clip, const Rect& rect, bool select);
    void Clear();
    bool IsTrackSingle() const;
    CuteTrack* GetTrackSingle() const;
    const Rect& GetRect() const;

private:
    VectorMap<void*, Item> items;
    bool track_single = false;
    CuteTrack* track_single_ptr = nullptr;
    Rect rect;
};

#endif
