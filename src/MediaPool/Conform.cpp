#include "MediaPool.h"
namespace am {

Conform::Conform() {
	// Initialize with default format
	target_format = "WAV";
}

bool Conform::ConformMedia(const Upp::String& sourcePath, const Upp::String& destPath) {
	LOG("Conforming media from: " + sourcePath + " to: " + destPath + " with format: " + target_format);
	// Stub - implement actual conform logic
	return true;
}

void Conform::SetTargetFormat(const Upp::String& format) {
	target_format = format;
}

}