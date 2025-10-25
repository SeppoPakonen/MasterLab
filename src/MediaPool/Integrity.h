#ifndef _MediaPool_Integrity_h_
#define _MediaPool_Integrity_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct IntegrityCheckResult {
	String path;
	bool exists;
	bool valid;
	String error_message;
};

class Integrity {
public:
	Integrity();
	Vector<IntegrityCheckResult> CheckIntegrity();
	void SetPoolPath(const String& path);
	String GetPoolPath() const { return pool_path; }
	
private:
	String pool_path;
};

}

#endif