#ifndef _MIDI_CuteMidiEditor_h_
#define _MIDI_CuteMidiEditor_h_

class CuteMidiEditList;
class CuteMidiEditTime;
class CuteMidiEditView;
class CuteMidiEditEventScale;
class CuteMidiEditEvent;
class CuteMidiThumbView;
class CuteMidiEditCommand;
class CuteMidiClip;
class CuteTimeScale;
class CuteTrack;

class CuteMidiEditor : public Splitter {
public:
    typedef CuteMidiEditor CLASSNAME;

    enum { ZoomMin = 10, ZoomBase = 100, ZoomMax = 1000, ZoomStep = 10 };
    enum Tool { Pointer = 0, Pencil, Eraser, Selection, Resize };

    CuteMidiEditor();
    void SetClip(CuteMidiClip* clip);
    CuteMidiClip* GetClip() const;
    void SetZoom(int zoom);
    int GetZoom() const;
    void SetTool(Tool tool);
    Tool GetTool() const;

private:
    CuteMidiClip* clip = nullptr;
    int zoom = ZoomBase;
    Tool tool = Pointer;
};

#endif
