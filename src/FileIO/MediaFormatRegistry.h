#ifndef _FileIO_MediaFormatRegistry_h_
#define _FileIO_MediaFormatRegistry_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MediaFormatInfo {
	String name;
	String extension;
	String description;
	
	// Support flags
	bool can_import = false;
	bool can_export = false;
};

class MediaFormatRegistry {
public:
	void RegisterFormat(const MediaFormatInfo& format);
	Vector<MediaFormatInfo> GetSupportedFormats() const;
	Vector<MediaFormatInfo> GetImportableFormats() const;
	Vector<MediaFormatInfo> GetExportableFormats() const;
	
private:
	Vector<MediaFormatInfo> formats;
};

}

#endif