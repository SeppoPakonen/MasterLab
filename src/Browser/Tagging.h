#ifndef _Browser_Tagging_h_
#define _Browser_Tagging_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Tag {
	String name;
	String category;
};

class Tagging {
public:
	Tagging();
	void AddTag(const String& filePath, const Tag& tag);
	void RemoveTag(const String& filePath, const Tag& tag);
	Vector<Tag> GetTags(const String& filePath) const;
	void SetTaggingEnabled(bool enabled);
	bool IsTaggingEnabled() const { return tagging_enabled; }
	
private:
	HashMap<String, Vector<Tag>> file_tags;
	bool tagging_enabled = true;
};

}

#endif