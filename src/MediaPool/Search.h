#ifndef _MediaPool_Search_h_
#define _MediaPool_Search_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct SearchResult {
	String path;
	String name;
	String type;
	int64 size;
	Time modification_time;
};

class Search {
public:
	Search();
	Vector<SearchResult> SearchMedia(const String& query);
	void SetSearchPath(const String& path);
	String GetSearchPath() const { return search_path; }
	
private:
	String search_path;
};

}

#endif