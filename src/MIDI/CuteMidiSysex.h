#ifndef _MIDI_CuteMidiSysex_h_
#define _MIDI_CuteMidiSysex_h_

class CuteMidiSysex {
public:
    CuteMidiSysex();
    void SetName(const String& name);
    const String& GetName() const;
    void SetData(const String& data);
    const String& GetData() const;
private:
    String name;
    String data;
};

class CuteMidiSysexList {
public:
    CuteMidiSysex& Add();
    int GetCount() const;
    CuteMidiSysex& operator[](int i);
private:
    Array<CuteMidiSysex> items;
};

#endif
