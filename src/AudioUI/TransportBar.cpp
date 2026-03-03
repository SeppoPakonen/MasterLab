#include "TransportBar.h"

namespace am {
namespace UI {

TransportBar::TransportBar()
{
	Add(playBtn.LeftPos(5, 60).VSizePos(5, 5));
	Add(stopBtn.LeftPos(70, 60).VSizePos(5, 5));
	Add(timeDisplay.LeftPos(140, 100).VSizePos(5, 5));
	
	playBtn.SetLabel("Play");
	stopBtn.SetLabel("Stop");
	timeDisplay.SetAlign(ALIGN_CENTER);
	timeDisplay.SetFont(Arial(14).Bold());
	
	playBtn << [=] { OnPlay(); };
	stopBtn << [=] { OnStop(); };
	
	SetTimeCallback(-100, [=] { Sync(); });
}

void TransportBar::OnPlay()
{
	if(transport) {
		if(transport->playing) transport->Stop();
		else transport->Play();
		WhenTogglePlay();
	}
	Sync();
}

void TransportBar::OnStop()
{
	if(transport) {
		transport->Stop();
		transport->playhead = 0;
		WhenStop();
	}
	Sync();
}

void TransportBar::Sync()
{
	if(transport) {
		playBtn.SetLabel(transport->playing ? "Pause" : "Play");
		double seconds = (double)transport->playhead / 48000.0; // Mock rate for display
		int mins = (int)(seconds / 60);
		int secs = (int)fmod(seconds, 60);
		int ms = (int)(fmod(seconds, 1.0) * 100);
		timeDisplay.SetLabel(Format("%02d:%02d.%02d", mins, secs, ms));
	}
}

void TransportBar::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorFace());
}

void TransportBar::Layout()
{
}

} // namespace UI
} // namespace am
