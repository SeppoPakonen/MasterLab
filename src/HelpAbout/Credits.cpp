#include "HelpAbout.h"
namespace am {

Credits::Credits() {
	credits = "AudioMaster\n"
		"Version 1.0\n"
		"\n"
		"Developed by MasterLab Team\n"
		"\n"
		"Special thanks to:\n"
		"- U++ Framework\n"
		"- contributors\n"
		"- users\n";
}

String Credits::GetCreditsText() const {
	return credits;
}

void Credits::ShowCredits() {
	String message = "Credits\n\n" + credits;
	PromptOK(message);
}

}