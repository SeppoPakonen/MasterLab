#ifndef _FileIO_Templates_h_
#define _FileIO_Templates_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Templates {
public:
	Vector<String> List() const;
	bool Instantiate(const String& name, const String& destPath);
	bool SaveTemplate(const String& projectPath, const String& templateName);
	
private:
	Vector<String> template_names;
	String GetTemplatesDirectory() const;
};

}

#endif