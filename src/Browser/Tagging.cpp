#include "Browser.h"
namespace am {

Tagging::Tagging() {
	// Initialize tagging system
}

void Tagging::AddTag(const String& filePath, const Tag& tag) {
	Vector<Tag>& tags = file_tags.GetAdd(filePath);
	for(int i = 0; i < tags.GetCount(); i++) {
		if(tags[i] == tag) {
			return; // Tag already exists
		}
	}
	tags.Add(tag);
}

void Tagging::RemoveTag(const String& filePath, const Tag& tag) {
	if (file_tags.Find(filePath) >= 0) {
		Vector<Tag>& tags = file_tags.Get(filePath);
		for(int i = 0; i < tags.GetCount(); i++) {
			if(tags[i] == tag) {
				tags.Remove(i);
				return;
			}
		}
	}
}

const Vector<Tag>& Tagging::GetTags(const String& filePath) const {
	if (file_tags.Find(filePath) >= 0) {
		return file_tags.Get(filePath);
	}
	static Vector<Tag> empty;
	empty.Clear();
	return empty;
}

void Tagging::SetTaggingEnabled(bool enabled) {
	tagging_enabled = enabled;
}

}