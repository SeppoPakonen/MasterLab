#ifndef _instruments_zenmodeljuno106_zenmodeljuno106_h_
#define _instruments_zenmodeljuno106_zenmodeljuno106_h_

#include <ZenCoreWorkstation/ZenCoreWorkstation.h>

namespace Instruments {

class ZenModelJUNO106 : public ZenCoreWorkstation {
public:
	typedef ZenModelJUNO106 CLASSNAME;
	ZenModelJUNO106();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;

private:
	void InitialiseModelDefaults();
	void UpdateSampleRateScaling();
	void SetParameterIfPresent(const char* id, double value);
};

} // namespace Instruments

#endif
