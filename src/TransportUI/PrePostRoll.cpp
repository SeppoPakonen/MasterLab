#include "TransportUI.h"
namespace am {

void PrePostRoll::SetPreRoll(double seconds) {
	pre_roll_seconds = Max(0.0, seconds);
}

void PrePostRoll::SetPostRoll(double seconds) {
	post_roll_seconds = Max(0.0, seconds);
}

void PrePostRoll::EnablePreRoll(bool enable) {
	pre_roll_enabled = enable;
}

void PrePostRoll::EnablePostRoll(bool enable) {
	post_roll_enabled = enable;
}

}