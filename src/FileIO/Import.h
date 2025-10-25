#ifndef _FileIO_Import_h_
#define _FileIO_Import_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Importer {
public:
	// Import various file types
	bool ImportAudio(const String& path);
	bool ImportMIDI(const String& path);
	bool ImportVideo(const String& path);
	bool ImportMusicXML(const String& path);
	bool ImportOMF(const String& path);
	bool ImportTempoTrack(const String& path);
	bool ImportTrackArchive(const String& path);
	
	// Generic import method
	bool Import(const String& path);
	
private:
	// Helper methods
	bool ValidateFilePath(const String& path);
};

}

#endif