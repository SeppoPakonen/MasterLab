#ifndef _FileIO_Export_h_
#define _FileIO_Export_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Exporter {
public:
	// Export various file types
	bool ExportMIDI(const String& path);
	bool ExportAudioMixdown(const String& path);
	bool ExportSelections(const String& path);
	bool ExportMusicXML(const String& path);
	bool ExportOMF(const String& path);
	bool ExportTempoTrack(const String& path);
	bool ExportScores(const String& path);
	
	// Generic export method
	bool Export(const String& path);
	
private:
	// Helper methods
	bool ValidateExportPath(const String& path);
};

}

#endif