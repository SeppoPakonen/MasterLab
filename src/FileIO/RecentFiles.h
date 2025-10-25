#ifndef _FileIO_RecentFiles_h_
#define _FileIO_RecentFiles_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class RecentFiles {
public:
	void AddRecent(const String& path);
	void RemoveRecent(const String& path);
	void Clear();
	Vector<String> ListRecent() const;
	int GetMaxRecentFiles() const { return max_recent_files; }
	void SetMaxRecentFiles(int count) { max_recent_files = count; }
	
private:
	Vector<String> recent_files;
	int max_recent_files = 10;  // Default to 10 recent files
};

}

#endif