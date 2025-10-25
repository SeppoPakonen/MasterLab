#include "FileIO.h"
namespace am {

Vector<String> Templates::List() const {
	// Stub implementation
	LOG("Listing templates");
	return Vector<String>(); // Stub - implement actual template listing
}

bool Templates::Instantiate(const String& name, const String& destPath) {
	// Stub implementation
	LOG("Instantiating template: " + name + " to: " + destPath);
	return true; // Stub - implement actual template instantiation
}

bool Templates::SaveTemplate(const String& projectPath, const String& templateName) {
	// Stub implementation
	LOG("Saving template from: " + projectPath + " as: " + templateName);
	return true; // Stub - implement actual template saving
}

String Templates::GetTemplatesDirectory() const {
	// Return the default templates directory
	return ConfigFile("templates");
}

}