#ifndef _FileIO_Backup_h_
#define _FileIO_Backup_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Backup {
public:
	bool CreateProjectBackup();
	bool CreateBackup(const String& projectPath, const String& backupPath);
	void Rotate(int limit);  // Remove old backups to keep only 'limit' number
	
private:
	String GenerateBackupPath(const String& originalPath);
};

}

#endif