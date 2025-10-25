#ifndef _MediaPool_Convert_h_
#define _MediaPool_Convert_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Convert {
public:
	Convert();
	bool ConvertMedia(const String& sourcePath, const String& destPath);
	void SetTargetFormat(const String& format);
	String GetTargetFormat() const { return target_format; }
	
private:
	String target_format;
};

}

#endif