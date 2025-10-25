#ifndef _MediaPool_Conform_h_
#define _MediaPool_Conform_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Conform {
public:
	Conform();
	bool ConformMedia(const String& sourcePath, const String& destPath);
	void SetTargetFormat(const String& format);
	String GetTargetFormat() const { return target_format; }
	
private:
	String target_format;
};

}

#endif