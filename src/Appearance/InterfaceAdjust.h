#ifndef _Appearance_InterfaceAdjust_h_
#define _Appearance_InterfaceAdjust_h_

#include <Core/Core.h>
#include <Draw/Draw.h>
using namespace Upp;

namespace am {

struct InterfaceAdjust {
	int saturation = 50;        // 0-100
	int brightness = 50;        // 0-100
	int buttonBrightness = 50;  // 0-100
};

class InterfaceAdjustManager {
public:
	InterfaceAdjustManager();
	
	const InterfaceAdjust& GetAdjust() const { return adjust; }
	void SetAdjust(const InterfaceAdjust& newAdjust);
	
	// Apply adjustments to the interface
	void ApplyToInterface();
	
private:
	InterfaceAdjust adjust;
};

}

#endif