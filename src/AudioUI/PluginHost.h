#ifndef _AudioUI_PluginHost_h_
#define _AudioUI_PluginHost_h_

#include <CtrlLib/CtrlLib.h>
#include <PluginSDK/PluginTypes.h> // Explicitly include PluginTypes.h
#include <PluginSDK/PluginSDK.h>

namespace am {
namespace UI {

using namespace Upp;
using namespace PluginSDK;

class PluginHost : public ParentCtrl {
public:
	typedef PluginHost CLASSNAME;
	PluginHost();

	void SetPlugin(PluginProcessor& p, PluginEditor& e);
	
	virtual void Paint(Draw& w) override;
	virtual void Layout() override;

private:
	PluginProcessor* processor = nullptr;
	PluginEditor* editor = nullptr;
	
	// Header components
	String pluginName;
	bool bypassed = false;
	
	// Placeholder for standardized controls
	// Button bypassBtn;
	// DropList presetSelector;
};

} // namespace UI
} // namespace am

#endif
