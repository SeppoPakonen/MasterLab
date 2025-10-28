#include "FileIO.h"
namespace am {

void RecentFiles::AddRecent(const String& path) {
	// Remove the path if it's already in the list
	int pos = recent_files.Find(path);
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

void RecentFiles::RemoveRecent(const String& path) {
	int pos = recent_files.Find(path);
	if (pos >= 0) {
		recent_files.Remove(pos);
	}
}

void RecentFiles::Clear() {
	recent_files.Clear();
}

Vector<String> RecentFiles::ListRecent() const {
	return recent_files;
}

}