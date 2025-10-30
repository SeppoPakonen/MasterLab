#ifndef _MediaPool_Conform_h_
#define _MediaPool_Conform_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Conform {
public:
	Conform();
	bool ConformMedia(const Upp::String& sourcePath, const Upp::String& destPath);
	void SetTargetFormat(const Upp::String& format);
	Upp::String GetTargetFormat() const { return target_format; }
	
private:
	Upp::String target_format;
};

}

#endif