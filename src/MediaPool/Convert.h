#ifndef _MediaPool_Convert_h_
#define _MediaPool_Convert_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Convert {
public:
	Convert();
	bool ConvertMedia(const Upp::String& sourcePath, const Upp::String& destPath);
	void SetTargetFormat(const Upp::String& format);
	Upp::String GetTargetFormat() const { return target_format; }
	
private:
	Upp::String target_format;
};

}

#endif