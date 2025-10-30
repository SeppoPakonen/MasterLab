#ifndef _MediaPool_Search_h_
#define _MediaPool_Search_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct SearchResult {
	Upp::String path;
	Upp::String name;
	Upp::String type;
	int64 size;
	Time modification_time;
};

class Search {
public:
	Search();
	Upp::Vector<SearchResult> SearchMedia(const Upp::String& query);
	void SetSearchPath(const Upp::String& path);
	Upp::String GetSearchPath() const { return search_path; }
	
private:
	Upp::String search_path;
};

}

#endif