#ifndef _ProjectWindow_CuteTrackButton_h_
#define _ProjectWindow_CuteTrackButton_h_

class CuteTrackButton : public Button {
public:
    typedef CuteTrackButton CLASSNAME;

    CuteTrackButton();

    void SetTrack(CuteTrack* track);
    CuteTrack* GetTrack() const;
    void SetButtonColor(Color color);
    Color GetButtonColor() const;

private:
    CuteTrack* track = nullptr;
    Color button_color = SColorFace();
};

#endif
