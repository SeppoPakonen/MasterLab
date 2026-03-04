#ifndef _MIDI_CuteMmcEvent_h_
#define _MIDI_CuteMmcEvent_h_

class CuteMmcEvent {
public:
    enum Command { Stop = 0x01, Play = 0x02, DeferredPlay = 0x03, FastForward = 0x04, Rewind = 0x05, RecordStrobe = 0x06, RecordExit = 0x07, RecordPause = 0x08, Pause = 0x09, Eject = 0x0a, Chase = 0x0b, CommandErrorReset = 0x0c, MmcReset = 0x0d };
    enum SubCommand { MaskedWrite = 0x40, Update = 0x41 };

    CuteMmcEvent(Command command = Stop);
    void SetCommand(Command command);
    Command GetCommand() const;
private:
    Command command = Stop;
};

#endif
