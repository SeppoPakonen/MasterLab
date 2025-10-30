#ifndef _FileIO_MediaFormatRegistry_h_
#define _FileIO_MediaFormatRegistry_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MediaFormatInfo : public Upp::Moveable<MediaFormatInfo> {
	Upp::String name;
	Upp::String extension;
	Upp::String description;
	
	// Support flags
	bool can_import = false;
	bool can_export = false;
	
	// Default constructor
	MediaFormatInfo() {}
	
	// Constructor with parameters
	MediaFormatInfo(const Upp::String& n, const Upp::String& ext, const Upp::String& desc, bool imp = false, bool exp = false)
		: name(n), extension(ext), description(desc), can_import(imp), can_export(exp) {}
	
	// Copy constructor
	MediaFormatInfo(const MediaFormatInfo& other) = default;
	
	// Move constructor
	MediaFormatInfo(MediaFormatInfo&& other) = default;
	
	// Assignment operators
	MediaFormatInfo& operator=(const MediaFormatInfo& other) = default;
	MediaFormatInfo& operator=(MediaFormatInfo&& other) = default;
};

class MediaFormatRegistry {
public:
	void RegisterFormat(const MediaFormatInfo& format);
	Upp::Vector<MediaFormatInfo> GetSupportedFormats() const;
	Upp::Vector<MediaFormatInfo> GetImportableFormats() const;
	Upp::Vector<MediaFormatInfo> GetExportableFormats() const;
	
private:
	Upp::Vector<MediaFormatInfo> formats;
};

}

#endif