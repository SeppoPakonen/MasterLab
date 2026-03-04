#include "MIDI.h"

CuteInstrumentForm::CuteInstrumentForm() {
    Title("Cute Instrument");
    Add(instrument_name.TopPos(8, 24).HSizePos(8, 8));
    Add(bank.TopPos(40, 24).HSizePos(8, 8));
    Add(program.TopPos(72, 24).HSizePos(8, 8));
    Add(ok_button.SetLabel("OK").BottomPos(8, 24).RightPos(80, 64));
    Add(cancel_button.SetLabel("Cancel").BottomPos(8, 24).RightPos(8, 64));
    SetRect(0, 0, 320, 140);
}
void CuteInstrumentForm::SetInstrumentName(const String& instrument_name) { this->instrument_name <<= instrument_name; }
String CuteInstrumentForm::GetInstrumentName() const { String value; value = ~instrument_name; return value; }
