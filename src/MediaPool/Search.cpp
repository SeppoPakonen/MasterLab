#include "MediaPool.h"
namespace am {

Search::Search() {
	// Initialize with default search path
	search_path = GetSystemFolder(SYS_DATA);
}

Vector<SearchResult> Search::SearchMedia(const String& query) {
	LOG("Searching for media: " + query + " in: " + search_path);
	// Stub - implement actual search logic
	return Vector<SearchResult>();
}

void Search::SetSearchPath(const String& path) {
	search_path = path;
}

}