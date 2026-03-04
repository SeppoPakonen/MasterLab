#ifndef _MIDI_CuteInstrument_h_
#define _MIDI_CuteInstrument_h_

class CuteInstrumentData {
public:
    void SetValue(int key, const String& value);
    String GetValue(int key) const;
    void Clear();
private:
    VectorMap<int, String> data;
};

class CuteInstrumentDataList : public Moveable<CuteInstrumentDataList> { };
class CuteInstrumentPatches : public Moveable<CuteInstrumentPatches> { };
class CuteInstrumentNotes : public Moveable<CuteInstrumentNotes> { };
class CuteInstrumentKeys : public Moveable<CuteInstrumentKeys> { };
class CuteInstrumentDrumFlags : public Moveable<CuteInstrumentDrumFlags> { };
class CuteInstrumentDrums : public Moveable<CuteInstrumentDrums> { };

class CuteInstrument {
public:
    CuteInstrument();

    void SetName(const String& name);
    const String& GetName() const;

    void SetBank(int bank);
    int GetBank() const;

    void SetProgram(int program);
    int GetProgram() const;

private:
    String name;
    int bank = 0;
    int program = 0;
};

class CuteInstrumentList {
public:
    CuteInstrument& GetAdd(const String& key);
    const VectorMap<String, CuteInstrument>& GetItems() const;
private:
    VectorMap<String, CuteInstrument> items;
};

#endif
