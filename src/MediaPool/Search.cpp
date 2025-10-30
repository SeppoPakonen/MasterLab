#include "MediaPool.h"
namespace am {

Search::Search() {
	// Initialize with default search path
	search_path = ConfigFile("MediaSearch");
}

Upp::Vector<SearchResult> Search::SearchMedia(const Upp::String& query) {
	LOG("Searching for media: " + query + " in: " + search_path);
	// Stub - implement actual search logic
	return Upp::Vector<SearchResult>();
}

void Search::SetSearchPath(const Upp::String& path) {
	search_path = path;
}

}