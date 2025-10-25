#include "Theme.h"
namespace am {

MeterTheme::MeterTheme() {
	SetupDefaultMarkers();
}

void MeterTheme::AddMarker(const MeterMarker& marker) {
	markers.Add(marker);
}

void MeterTheme::RemoveMarker(int index) {
	if (index >= 0 && index < markers.GetCount()) {
		markers.Remove(index);
	}
}

void MeterTheme::ClearMarkers() {
	markers.Clear();
}

void MeterTheme::SetupDefaultMarkers() {
	// Set up default markers: 100% red, 75% yellow, 30% green, 0% blue
	MeterMarker m1 = { 1.0, Color(200, 50, 50) };      // 100% - Wine red
	MeterMarker m2 = { 0.75, Color(255, 255, 100) };   // 75% - Light yellow
	MeterMarker m3 = { 0.3, Color(100, 255, 100) };    // 30% - Light green
	MeterMarker m4 = { 0.0, Color(100, 150, 255) };    // 0% - Light blue

	markers.Clear();
	markers.Add(m1);
	markers.Add(m2);
	markers.Add(m3);
	markers.Add(m4);
}

Color MeterTheme::GetColorForLevel(double level) const {
	if (markers.IsEmpty()) {
		return White();
	}
	
	// If level is below first marker, return color of first marker
	if (level <= markers[0].db) {
		return markers[0].color;
	}
	
	// If level is above last marker, return color of last marker
	if (level >= markers.Top().db) {
		return markers.Top().color;
	}
	
	// Find the two markers to interpolate between
	for (int i = 0; i < markers.GetCount() - 1; i++) {
		if (level >= markers[i].db && level <= markers[i+1].db) {
			// Interpolate between markers[i] and markers[i+1]
			double range = markers[i+1].db - markers[i].db;
			double pos = (level - markers[i].db) / range;
			
			Color c1 = markers[i].color;
			Color c2 = markers[i+1].color;
			
			int r = (int)(c1.GetR() + pos * (c2.GetR() - c1.GetR()));
			int g = (int)(c1.GetG() + pos * (c2.GetG() - c1.GetG()));
			int b = (int)(c1.GetB() + pos * (c2.GetB() - c1.GetB()));
			
			return Color(r, g, b);
		}
	}
	
	return White(); // Fallback
}

}