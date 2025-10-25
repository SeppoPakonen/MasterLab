#include "MediaPool.h"
namespace am {

Conform::Conform() {
	// Initialize with default format
	target_format = "WAV";
}

bool Conform::ConformMedia(const String& sourcePath, const String& destPath) {
	LOG("Conforming media from: " + sourcePath + " to: " + destPath + " with format: " + target_format);
	// Stub - implement actual conform logic
	return true;
}

void Conform::SetTargetFormat(const String& format) {
	target_format = format;
}

}