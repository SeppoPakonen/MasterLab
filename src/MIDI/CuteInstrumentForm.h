#ifndef _MIDI_CuteInstrumentForm_h_
#define _MIDI_CuteInstrumentForm_h_

class CuteInstrumentForm : public TopWindow {
public:
    typedef CuteInstrumentForm CLASSNAME;

    CuteInstrumentForm();

    void SetInstrumentName(const String& instrument_name);
    String GetInstrumentName() const;

private:
    EditString instrument_name;
    EditInt bank;
    EditInt program;
    Button ok_button;
    Button cancel_button;
};

#endif
