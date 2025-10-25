#ifndef _AudioAnalysis_Warp_h_
#define _AudioAnalysis_Warp_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Warp {
public:
	Warp();
	void WarpAudio(double* samples, int count, int sampleRate, double ratio);
	void SetWarpRatio(double ratio);
	double GetWarpRatio() const { return warp_ratio; }
	
private:
	double warp_ratio = 1.0;
};

}

#endif