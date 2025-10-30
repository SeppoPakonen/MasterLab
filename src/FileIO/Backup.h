#ifndef _FileIO_Backup_h_
#define _FileIO_Backup_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Backup {
public:
	bool CreateProjectBackup();
	bool CreateBackup(const Upp::String& projectPath, const Upp::String& backupPath);
	void Rotate(int limit);  // Remove old backups to keep only 'limit' number
	
private:
	Upp::String GenerateBackupPath(const Upp::String& originalPath);
};

}

#endif