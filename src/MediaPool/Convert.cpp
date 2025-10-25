#include "MediaPool.h"
namespace am {

Convert::Convert() {
	// Initialize with default format
	target_format = "WAV";
}

bool Convert::ConvertMedia(const String& sourcePath, const String& destPath) {
	LOG("Converting media from: " + sourcePath + " to: " + destPath + " with format: " + target_format);
	// Stub - implement actual convert logic
	return true;
}

void Convert::SetTargetFormat(const String& format) {
	target_format = format;
}

}