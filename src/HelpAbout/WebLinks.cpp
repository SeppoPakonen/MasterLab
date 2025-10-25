#include "HelpAbout.h"
namespace am {

WebLinks::WebLinks() {
	// Initialize URLs
}

void WebLinks::OpenHelpSite() {
	LOG("Opening help site: " + help_url);
	// Stub - implement actual URL opening
}

void WebLinks::OpenSupportSite() {
	LOG("Opening support site: " + support_url);
	// Stub - implement actual URL opening
}

void WebLinks::OpenUpdatesSite() {
	LOG("Opening updates site: " + updates_url);
	// Stub - implement actual URL opening
}

void WebLinks::OpenForumSite() {
	LOG("Opening forum site: " + forum_url);
	// Stub - implement actual URL opening
}

}