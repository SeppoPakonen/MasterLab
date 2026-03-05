#ifndef _ProjectWindow_CuteTrackList_h_
#define _ProjectWindow_CuteTrackList_h_

class CuteTrackList {
public:
    CuteTrackList();

    int GetCount() const;
    void AddTrack(const CuteTrack& track);
    void InsertTrack(int index, const CuteTrack& track);
    void RemoveTrack(int index);
    void MoveTrack(int from, int to);
    CuteTrack* GetTrack(int index);
    const CuteTrack* GetTrack(int index) const;

private:
    Array<CuteTrack> tracks;
};

#endif
