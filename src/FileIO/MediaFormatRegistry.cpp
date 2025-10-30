#include "FileIO.h"
namespace am {

void MediaFormatRegistry::RegisterFormat(const MediaFormatInfo& format) {
	formats.Add(format);
}

Upp::Vector<MediaFormatInfo> MediaFormatRegistry::GetSupportedFormats() const {
	Upp::Vector<MediaFormatInfo> result;
	result <<= formats;
	return result;
}

Upp::Vector<MediaFormatInfo> MediaFormatRegistry::GetImportableFormats() const {
	Upp::Vector<MediaFormatInfo> result;
	for (const auto& format : formats) {
		if (format.can_import) {
			result.Add(format);
		}
	}
	return result;
}

Upp::Vector<MediaFormatInfo> MediaFormatRegistry::GetExportableFormats() const {
	Upp::Vector<MediaFormatInfo> result;
	for (const auto& format : formats) {
		if (format.can_export) {
			result.Add(format);
		}
	}
	return result;
}

}