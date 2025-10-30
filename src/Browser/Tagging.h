#ifndef _Browser_Tagging_h_
#define _Browser_Tagging_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Tag : public Moveable<Tag> {
	Upp::String name;
	Upp::String category;
	
	bool operator==(const Tag& other) const {
		return name == other.name && category == other.category;
	}
};

class Tagging {
public:
	Tagging();
	void AddTag(const Upp::String& filePath, const Tag& tag);
	void RemoveTag(const Upp::String& filePath, const Tag& tag);
	const Upp::Vector<Tag>& GetTags(const Upp::String& filePath) const;
	void SetTaggingEnabled(bool enabled);
	bool IsTaggingEnabled() const { return tagging_enabled; }
	
private:
	VectorMap<Upp::String, Upp::Vector<Tag>> file_tags;
	bool tagging_enabled = true;
};

}

#endif