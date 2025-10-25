#include "Browser.h"
namespace am {

Tagging::Tagging() {
	// Initialize tagging system
}

void Tagging::AddTag(const String& filePath, const Tag& tag) {
	Vector<Tag>& tags = file_tags.GetAdd(filePath);
	if (tags.Find(tag) < 0) {
		tags.Add(tag);
	}
}

void Tagging::RemoveTag(const String& filePath, const Tag& tag) {
	if (file_tags.Find(filePath) >= 0) {
		Vector<Tag>& tags = file_tags.Get(filePath);
		int pos = tags.Find(tag);
		if (pos >= 0) {
			tags.Remove(pos);
		}
	}
}

Vector<Tag> Tagging::GetTags(const String& filePath) const {
	if (file_tags.Find(filePath) >= 0) {
		return file_tags.Get(filePath);
	}
	return Vector<Tag>();
}

void Tagging::SetTaggingEnabled(bool enabled) {
	tagging_enabled = enabled;
}

}