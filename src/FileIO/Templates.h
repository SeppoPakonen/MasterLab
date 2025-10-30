#ifndef _FileIO_Templates_h_
#define _FileIO_Templates_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Templates {
public:
	Upp::Vector<Upp::String> List() const;
	bool Instantiate(const Upp::String& name, const Upp::String& destPath);
	bool SaveTemplate(const Upp::String& projectPath, const Upp::String& templateName);
	
private:
	Upp::Vector<Upp::String> template_names;
	Upp::String GetTemplatesDirectory() const;
};

}

#endif