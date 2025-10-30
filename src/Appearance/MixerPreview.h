#ifndef _Appearance_MixerPreview_h_
#define _Appearance_MixerPreview_h_

#include <Core/Core.h>
#include <Draw/Draw.h>
using namespace Upp;

namespace am {

class MixerPreview {
public:
	MixerPreview();
	
	// Set/get preview image
	void SetPreviewImage(const Image& img) { previewImage = img; }
	Image GetPreviewImage() const { return previewImage; }
	
	// Load/save preview settings
	void LoadPreviewSettings();
	void SavePreviewSettings();
	
	// Apply preview to mixer display
	void ApplyToMixerDisplay();
	
private:
	Image previewImage;
	Upp::String previewImagePath;
};

}

#endif