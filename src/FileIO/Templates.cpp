#include "FileIO.h"
namespace am {

Upp::Vector<Upp::String> Templates::List() const {
	// Stub implementation
	LOG("Listing templates");
	return Upp::Vector<Upp::String>(); // Stub - implement actual template listing
}

bool Templates::Instantiate(const Upp::String& name, const Upp::String& destPath) {
	// Stub implementation
	LOG("Instantiating template: " + name + " to: " + destPath);
	return true; // Stub - implement actual template instantiation
}

bool Templates::SaveTemplate(const Upp::String& projectPath, const Upp::String& templateName) {
	// Stub implementation
	LOG("Saving template from: " + projectPath + " as: " + templateName);
	return true; // Stub - implement actual template saving
}

Upp::String Templates::GetTemplatesDirectory() const {
	// Return the default templates directory
	return ConfigFile("templates");
}

}