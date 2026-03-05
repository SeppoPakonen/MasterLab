#include "ProjectWindow.h"

CuteTrackForm::CuteTrackForm() {
    Title("Track");
    Add(track_name.TopPosZ(8, 24).HSizePosZ(8, 8));
    Add(input_bus.TopPosZ(40, 24).HSizePosZ(8, 8));
    Add(output_bus.TopPosZ(72, 24).HSizePosZ(8, 8));
}
void CuteTrackForm::SetTrack(CuteTrack* track) { this->track = track; if (track) track_name.SetData(track->GetName()); }
CuteTrack* CuteTrackForm::GetTrack() const { return track; }
String CuteTrackForm::GetTrackName() const { return (String)track_name.GetData(); }
int CuteTrackForm::GetInputBusIndex() const { return input_bus.GetIndex(); }
int CuteTrackForm::GetOutputBusIndex() const { return output_bus.GetIndex(); }
