#ifndef _Video_Thumbnail_h_
#define _Video_Thumbnail_h_

#include <Core/Core.h>
#include <Draw/Draw.h>
using namespace Upp;

namespace am {

class Thumbnail {
public:
	Thumbnail();
	Image GenerateThumbnail(const Upp::String& videoPath, int width = 128, int height = 96);
	bool SaveThumbnail(const Image& thumbnail, const Upp::String& path);
	void SetThumbnailQuality(int quality);
	int GetThumbnailQuality() const { return thumbnail_quality; }
	
private:
	int thumbnail_quality = 80;  // JPEG quality percentage
};

}

#endif