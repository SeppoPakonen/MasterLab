#ifndef _AudioMaster_AudioMaster_h_
#define _AudioMaster_AudioMaster_h_

#include <CtrlLib/CtrlLib.h>
#include "MainWindow.h"

using namespace Upp;

class AudioMasterApp : public TopWindow {
public:
	AudioMasterApp();
	
private:
	MainWindow mainWindow;
};

#endif