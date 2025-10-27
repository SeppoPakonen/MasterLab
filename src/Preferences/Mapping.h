#ifndef _Preferences_Mapping_h_
#define _Preferences_Mapping_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Mapping {
public:
	Mapping();
	void CreateMap();
	void ApplyMapping();
	void SaveMapping();
	void LoadMapping();
	
private:
	VectorMap<String, String> mapping;
};

}

#endif