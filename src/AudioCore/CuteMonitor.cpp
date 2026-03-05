#include "AudioCore.h"

CuteMonitor::CuteMonitor(float gain, float panning)
	: gain(gain),
	  panning(panning),
	  prev_gain(gain),
	  prev_panning(panning) {}

CuteMonitor::~CuteMonitor() {}

void CuteMonitor::SetGain(float gain) {
	prev_gain = this->gain;
	this->gain = gain;
}

float CuteMonitor::GetGain() const {
	return gain;
}

float CuteMonitor::GetPrevGain() const {
	return prev_gain;
}

void CuteMonitor::SetPanning(float panning) {
	prev_panning = this->panning;
	this->panning = panning;
}

float CuteMonitor::GetPanning() const {
	return panning;
}

float CuteMonitor::GetPrevPanning() const {
	return prev_panning;
}
