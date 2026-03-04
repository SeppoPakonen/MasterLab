#ifndef _MIDI_CuteMidiListView_h_
#define _MIDI_CuteMidiListView_h_

class CuteMidiFile;

class CuteMidiFileItem {
public:
    CuteMidiFileItem(const String& name = String());
    String name;
};

class CuteMidiChannelItem {
public:
    CuteMidiChannelItem(int channel = 0);
    int channel = 0;
};

class CuteMidiListView : public ParentCtrl {
public:
    typedef CuteMidiListView CLASSNAME;
    enum ItemColumn { Name = 0, Channel, Events, Duration };

    CuteMidiListView();
    void SetMidiFile(CuteMidiFile* midi_file);
    CuteMidiFile* GetMidiFile() const;

private:
    CuteMidiFile* midi_file = nullptr;
    ArrayCtrl list;
};

#endif
