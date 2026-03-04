#ifndef _FileIO_CuteFiles_h_
#define _FileIO_CuteFiles_h_

class CuteFiles : public TopWindow {
public:
    typedef CuteFiles CLASSNAME;

    enum PageIndex { Audio = 0, Midi = 1 };

    CuteFiles();

    CuteFileListView& GetAudioListView();
    CuteFileListView& GetMidiListView();
    void SetCurrentPage(PageIndex page);
    PageIndex GetCurrentPage() const;

private:
    TabCtrl tabs;
    CuteFileListView audio_list_view;
    CuteFileListView midi_list_view;
    PageIndex current_page = Audio;
};

#endif
