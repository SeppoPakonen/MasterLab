#include "AudioMaster.h"

AudioMasterApp::AudioMasterApp() {
	mainWindow.SetRect(0, 0, 1024, 768);
	AddFrame(mainWindow);
}

GUI_APP_MAIN {
	AudioMasterApp app;
	app.Run();
}