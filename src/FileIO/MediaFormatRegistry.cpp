#include "FileIO.h"
namespace am {

void MediaFormatRegistry::RegisterFormat(const MediaFormatInfo& format) {
	formats.Add(format);
}

Vector<MediaFormatInfo> MediaFormatRegistry::GetSupportedFormats() const {
	return formats;
}

Vector<MediaFormatInfo> MediaFormatRegistry::GetImportableFormats() const {
	Vector<MediaFormatInfo> result;
	for (const auto& format : formats) {
		if (format.can_import) {
			result.Add(format);
		}
	}
	return result;
}

Vector<MediaFormatInfo> MediaFormatRegistry::GetExportableFormats() const {
	Vector<MediaFormatInfo> result;
	for (const auto& format : formats) {
		if (format.can_export) {
			result.Add(format);
		}
	}
	return result;
}

}