#ifndef _MIDI_CuteMidiEditorForm_h_
#define _MIDI_CuteMidiEditorForm_h_

class CuteMidiEditor;
class CuteMidiClip;
class CuteMidiSequence;
class CuteTimeScale;
class CuteMidiEventList;
class CuteMidiControlTypeGroup;
class CuteInstrumentMenu;

class CuteMidiEditorForm : public TopWindow {
public:
    typedef CuteMidiEditorForm CLASSNAME;

    CuteMidiEditorForm();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;

private:
    CuteMidiEditor* editor = nullptr;
    MenuBar menu_bar;
    ToolBar tool_bar;
    StatusBar status_bar;
    Splitter split;
    ParentCtrl workspace;
};

#endif
