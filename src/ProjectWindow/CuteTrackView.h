#ifndef _ProjectWindow_CuteTrackView_h_
#define _ProjectWindow_CuteTrackView_h_

class CuteTrackView : public ParentCtrl {
public:
    typedef CuteTrackView CLASSNAME;

    CuteTrackView();

    void SetTrackList(CuteTrackList* track_list);
    CuteTrackList* GetTrackList() const;
    void RefreshTracks();
    void SetCurrentTrack(int index);
    int GetCurrentTrack() const;

private:
    CuteTrackList* track_list = nullptr;
    int current_track = -1;
    ArrayCtrl track_table;
};

#endif
