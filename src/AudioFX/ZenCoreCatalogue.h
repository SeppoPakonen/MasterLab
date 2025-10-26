#ifndef _AudioFX_ZenCoreCatalogue_h_
#define _AudioFX_ZenCoreCatalogue_h_

// Note: Requires AudioFX/AudioFX.h for Upp types.

namespace am {
namespace DSP {

struct ZenCoreAlgorithm {
	String id;
	String name;
	String category;
	bool combination = false;
};

class ZenCoreMFXCatalogue {
public:
	static const Vector<ZenCoreAlgorithm>& List();
	static const ZenCoreAlgorithm* FindById(const String& id);
	static const ZenCoreAlgorithm* FindByIndex(int index);
};

} // namespace DSP
} // namespace am

#endif
