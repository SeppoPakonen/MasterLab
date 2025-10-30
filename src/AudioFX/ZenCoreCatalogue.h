#ifndef _AudioFX_ZenCoreCatalogue_h_
#define _AudioFX_ZenCoreCatalogue_h_

// Note: Requires AudioFX/AudioFX.h for Upp types.

#include <Core/Core.h>

namespace am {
namespace DSP {

struct ZenCoreAlgorithm : public Upp::Moveable<ZenCoreAlgorithm> {
	Upp::String id;
	Upp::String name;
	Upp::String category;
	bool combination = false;
	
	// Default constructor
	ZenCoreAlgorithm() {}
	
	// Constructor with parameters
	ZenCoreAlgorithm(const Upp::String& id, const Upp::String& name, const Upp::String& category, bool combination = false)
		: id(id), name(name), category(category), combination(combination) {}
		
	// Copy constructor
	ZenCoreAlgorithm(const ZenCoreAlgorithm& other) = default;
	
	// Move constructor
	ZenCoreAlgorithm(ZenCoreAlgorithm&& other) = default;
	
	// Assignment operators
	ZenCoreAlgorithm& operator=(const ZenCoreAlgorithm& other) = default;
	ZenCoreAlgorithm& operator=(ZenCoreAlgorithm&& other) = default;
};

class ZenCoreMFXCatalogue {
public:
	static const Upp::Vector<ZenCoreAlgorithm>& List();
	static const ZenCoreAlgorithm* FindById(const Upp::String& id);
	static const ZenCoreAlgorithm* FindByIndex(int index);
};

} // namespace DSP
} // namespace am

#endif
