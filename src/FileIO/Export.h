#ifndef _FileIO_Export_h_
#define _FileIO_Export_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Exporter {
public:
	// Export various file types
	bool ExportMIDI(const Upp::String& path);
	bool ExportAudioMixdown(const Upp::String& path);
	bool ExportSelections(const Upp::String& path);
	bool ExportMusicXML(const Upp::String& path);
	bool ExportOMF(const Upp::String& path);
	bool ExportTempoTrack(const Upp::String& path);
	bool ExportScores(const Upp::String& path);
	
	// Generic export method
	bool Export(const Upp::String& path);
	
private:
	// Helper methods
	bool ValidateExportPath(const Upp::String& path);
};

}

#endif