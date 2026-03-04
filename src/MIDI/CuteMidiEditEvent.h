#ifndef _MIDI_CuteMidiEditEvent_h_
#define _MIDI_CuteMidiEditEvent_h_

class CuteMidiEditor;
class CuteMidiSequence;

class CuteMidiEditEventScale : public ParentCtrl {
public:
    typedef CuteMidiEditEventScale CLASSNAME;

    CuteMidiEditEventScale();
    void SetZoom(int zoom);
    int GetZoom() const;

private:
    int zoom = 100;
};

class CuteMidiEditEvent : public ParentCtrl {
public:
    typedef CuteMidiEditEvent CLASSNAME;

    CuteMidiEditEvent();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;
    void RefreshView();

private:
    CuteMidiEditor* editor = nullptr;
};

#endif
