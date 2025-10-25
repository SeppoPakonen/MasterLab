#ifndef _Theme_MeterTheme_h_
#define _Theme_MeterTheme_h_

#include <Draw/Draw.h>
using namespace Upp;

namespace am {

struct MeterMarker {
	double db;      // Decibel level (0.0 = 0dB, 1.0 = full scale)
	Color color;    // Color for this marker level
};

class MeterTheme {
public:
	MeterTheme();
	
	// Marker management
	void AddMarker(const MeterMarker& marker);
	void RemoveMarker(int index);
	void ClearMarkers();
	Vector<MeterMarker> GetMarkers() const { return markers; }
	void SetMarkers(const Vector<MeterMarker>& new_markers) { markers = new_markers; }
	
	// Default markers setup
	void SetupDefaultMarkers();
	
	// Find color for a given level
	Color GetColorForLevel(double level) const;  // level is 0.0 to 1.0
	
private:
	Vector<MeterMarker> markers;
};

}

#endif