#ifndef _Browser_CuteAudioListView_h_
#define _Browser_CuteAudioListView_h_

class CuteAudioFile;
class CuteFileListItem;

class CuteAudioFileItem {
public:
    CuteAudioFileItem(const String& path, CuteAudioFile* file);
    String ToolTip() const;

private:
    String path;
    int channels = 0;
    unsigned long frames = 0;
    unsigned int sample_rate = 0;
};

class CuteAudioListView : public ArrayCtrl {
public:
    typedef CuteAudioListView CLASSNAME;

    enum ItemColumn {
        Name = 0,
        Channels,
        Frames,
        Rate,
        Time,
        Path,
        LastColumn,
    };

    CuteAudioListView();
    int GetPathColumn() const;
    CuteAudioFileItem CreateFileItem(const String& path);
    Vector<String> GetOpenFileNames();
};

#endif
