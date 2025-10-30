#ifndef _MediaPool_Integrity_h_
#define _MediaPool_Integrity_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct IntegrityCheckResult {
	Upp::String path;
	bool exists;
	bool valid;
	Upp::String error_message;
};

class Integrity {
public:
	Integrity();
	Upp::Vector<IntegrityCheckResult> CheckIntegrity();
	void SetPoolPath(const Upp::String& path);
	Upp::String GetPoolPath() const { return pool_path; }
	
private:
	Upp::String pool_path;
};

}

#endif