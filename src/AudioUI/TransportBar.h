#ifndef _AudioUI_TransportBar_h_
#define _AudioUI_TransportBar_h_

#include <CtrlLib/CtrlLib.h>
#include <AudioCore/Transport.h>

namespace am {
namespace UI {

using namespace Upp;

class TransportBar : public ParentCtrl {
public:
	typedef TransportBar CLASSNAME;
	TransportBar();

	void SetTransport(am::Transport& t) { transport = &t; Sync(); }
	
	virtual void Paint(Draw& w) override;
	virtual void Layout() override;

	Event<> WhenTogglePlay;
	Event<> WhenStop;

private:
	void Sync();
	void OnPlay();
	void OnStop();

	Button playBtn;
	Button stopBtn;
	Label timeDisplay;
	
	am::Transport* transport = nullptr;
};

} // namespace UI
} // namespace am

#endif
