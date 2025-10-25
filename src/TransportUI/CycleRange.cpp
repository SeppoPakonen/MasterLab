#include "TransportUI.h"
namespace am {

void CycleRange::SetRange(const Range& range) {
	this->range = range;
}

void CycleRange::Enable(bool enable) {
	enabled = enable;
}

void CycleRange::SetLoop(bool loop) {
	this->loop = loop;
}

}