#include "Appearance.h"
namespace am {

InterfaceAdjustManager::InterfaceAdjustManager() {
	// Initialize with default interface adjustments
	adjust.saturation = 50;
	adjust.brightness = 50;
	adjust.buttonBrightness = 50;
}

void InterfaceAdjustManager::SetAdjust(const InterfaceAdjust& newAdjust) {
	adjust = newAdjust;
}

void InterfaceAdjustManager::ApplyToInterface() {
	LOG("Applying interface adjustments");
	LOG("Saturation: " + IntStr(adjust.saturation));
	LOG("Brightness: " + IntStr(adjust.brightness));
	LOG("Button brightness: " + IntStr(adjust.buttonBrightness));
	
	// In a real implementation, this would adjust the interface colors
	// based on the saturation, brightness, and button brightness settings
}

}