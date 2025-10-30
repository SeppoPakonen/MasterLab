#include "FileIO.h"
namespace am {

void RecentFiles::AddRecent(const Upp::String& path) {
	// Remove the path if it's already in the list
	int pos = -1;
	for(int i = 0; i < recent_files.GetCount(); i++) {
		if(recent_files[i] == path) {
			pos = i;
			break;
		}
	}
	if (pos >= 0) {
		recent_files.Remove(pos);
	}
	
	// Add to the beginning of the list
	recent_files.Insert(0, path);
	
	// Keep only the most recent files up to max count
	while (recent_files.GetCount() > max_recent_files) {
		recent_files.Drop();
	}
}

void RecentFiles::RemoveRecent(const Upp::String& path) {
	int pos = -1;
	for(int i = 0; i < recent_files.GetCount(); i++) {
		if(recent_files[i] == path) {
			pos = i;
			break;
		}
	}
	if (pos >= 0) {
		recent_files.Remove(pos);
	}
}

void RecentFiles::Clear() {
	recent_files.Clear();
}

Upp::Vector<Upp::String> RecentFiles::ListRecent() const {
	// Use operator<<= for deep copy of the vector
	Upp::Vector<Upp::String> result;
	result <<= recent_files;
	return result;
}

}