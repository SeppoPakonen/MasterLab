#ifndef _AudioMaster_CuteThumbView_h_
#define _AudioMaster_CuteThumbView_h_

class CuteThumbView : public ParentCtrl {
public:
    typedef CuteThumbView CLASSNAME;

    CuteThumbView();

    void UpdatePlayHead();
    void UpdateContents();
    void UpdateThumb(int dx = 0);

private:
    enum DragState {
        DragNone = 0,
        DragStart,
        DragMove,
        DragClick,
    };

    DragState drag_state = DragNone;
    int play_head_x = 0;
    Rect thumb_rect;
};

#endif
