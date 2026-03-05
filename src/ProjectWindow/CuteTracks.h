#ifndef _ProjectWindow_CuteTracks_h_
#define _ProjectWindow_CuteTracks_h_

class CuteTracks {
public:
    CuteTracks();

    void SetTrackList(CuteTrackList* track_list);
    CuteTrackList* GetTrackList() const;
    void SetCurrentTrack(int index);
    int GetCurrentTrack() const;
    void SelectAll();
    void ClearSelection();

private:
    CuteTrackList* track_list = nullptr;
    int current_track = -1;
    Index<int> selected_tracks;
};

#endif
