#ifndef _FileIO_RecentFiles_h_
#define _FileIO_RecentFiles_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class RecentFiles {
public:
	void AddRecent(const Upp::String& path);
	void RemoveRecent(const Upp::String& path);
	void Clear();
	Upp::Vector<Upp::String> ListRecent() const;
	int GetMaxRecentFiles() const { return max_recent_files; }
	void SetMaxRecentFiles(int count) { max_recent_files = count; }
	
private:
	Upp::Vector<Upp::String> recent_files;
	int max_recent_files = 10;  // Default to 10 recent files
};

}

#endif