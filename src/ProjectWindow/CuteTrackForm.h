#ifndef _ProjectWindow_CuteTrackForm_h_
#define _ProjectWindow_CuteTrackForm_h_

class CuteTrackForm : public TopWindow {
public:
    typedef CuteTrackForm CLASSNAME;

    CuteTrackForm();

    void SetTrack(CuteTrack* track);
    CuteTrack* GetTrack() const;
    String GetTrackName() const;
    int GetInputBusIndex() const;
    int GetOutputBusIndex() const;

private:
    CuteTrack* track = nullptr;
    EditString track_name;
    DropList input_bus;
    DropList output_bus;
};

#endif
