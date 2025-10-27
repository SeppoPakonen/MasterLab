#ifndef _Browser_Tagging_h_
#define _Browser_Tagging_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Tag : public Moveable<Tag> {
	String name;
	String category;
	
	bool operator==(const Tag& other) const {
		return name == other.name && category == other.category;
	}
};

class Tagging {
public:
	Tagging();
	void AddTag(const String& filePath, const Tag& tag);
	void RemoveTag(const String& filePath, const Tag& tag);
	const Vector<Tag>& GetTags(const String& filePath) const;
	void SetTaggingEnabled(bool enabled);
	bool IsTaggingEnabled() const { return tagging_enabled; }
	
private:
	VectorMap<String, Vector<Tag>> file_tags;
	bool tagging_enabled = true;
};

}

#endif