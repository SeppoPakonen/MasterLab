#ifndef _instruments_zenmodeljx8p_zenmodeljx8p_h_
#define _instruments_zenmodeljx8p_zenmodeljx8p_h_

#include <ZenCoreWorkstation/ZenCoreWorkstation.h>

namespace Instruments {

class ZenModelJX8P : public ZenCoreWorkstation {
public:
	typedef ZenModelJX8P CLASSNAME;
	ZenModelJX8P();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;

private:
	void InitialiseModelDefaults();
	void ApplyPerformanceCalibration();
	void SetParameterIfPresent(const char* id, double value);
};

} // namespace Instruments

#endif
