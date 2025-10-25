#ifndef _AudioAnalysis_Statistics_h_
#define _AudioAnalysis_Statistics_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct AudioStats {
	double rms = 0.0;
	double peak = 0.0;
	double duration = 0.0;
	double sample_rate = 44100.0;
};

class Statistics {
public:
	Statistics();
	AudioStats Analyze(const double* samples, int count, int sampleRate);
	
private:
	AudioStats stats;
};

}

#endif