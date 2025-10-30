#ifndef _FileIO_Import_h_
#define _FileIO_Import_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Importer {
public:
	// Import various file types
	bool ImportAudio(const Upp::String& path);
	bool ImportMIDI(const Upp::String& path);
	bool ImportVideo(const Upp::String& path);
	bool ImportMusicXML(const Upp::String& path);
	bool ImportOMF(const Upp::String& path);
	bool ImportTempoTrack(const Upp::String& path);
	bool ImportTrackArchive(const Upp::String& path);
	
	// Generic import method
	bool Import(const Upp::String& path);
	
private:
	// Helper methods
	bool ValidateFilePath(const Upp::String& path);
};

}

#endif