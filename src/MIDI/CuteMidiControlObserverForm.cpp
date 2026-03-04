#include "MIDI.h"

CuteMidiControlObserverForm::CuteMidiControlObserverForm() {
    Title("Cute MIDI Control Observer");
    Add(control_type.TopPos(8, 24).LeftPos(8, 140));
    Add(channel.TopPos(8, 24).LeftPos(156, 60));
    Add(parameter.TopPos(40, 24).LeftPos(8, 120));
    Add(map_button.SetLabel("Map").BottomPos(8, 24).RightPos(80, 64));
    Add(unmap_button.SetLabel("Unmap").BottomPos(8, 24).RightPos(8, 64));
    SetRect(0, 0, 340, 140);
}
void CuteMidiControlObserverForm::SetObserver(CuteMidiControlObserver* observer) { this->observer = observer; }
CuteMidiControlObserver* CuteMidiControlObserverForm::GetObserver() const { return observer; }
