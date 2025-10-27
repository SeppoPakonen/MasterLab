#ifndef _AudioAnalysis_Spectrum_h_
#define _AudioAnalysis_Spectrum_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Spectrum {
public:
	Spectrum();
	void Analyze(const double* samples, int count, int sampleRate);
	const Vector<double>& GetSpectrum() const { return spectrum_data; }
	void SetWindowSize(int size);
	int GetWindowSize() const { return window_size; }
	
private:
	Vector<double> spectrum_data;
	int window_size = 1024;
};

}

#endif