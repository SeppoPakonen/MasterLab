#ifndef _DSP_PhaseVocoder_h_
#define _DSP_PhaseVocoder_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <Math/FFT.h>

namespace DSP {

using namespace Upp;
using namespace am;

class PhaseVocoder {
public:
	PhaseVocoder();
	
	void Process(AudioBuffer& buffer, const Vector<double>& pitchShiftRatios);

private:
	void STFT(const Vector<float>& input, Vector<Vector<Complex>>& frames);
	void ISTFT(const Vector<Vector<Complex>>& frames, Vector<float>& output);
	
	int windowSize = 2048;
	int hopSize = 512;
	Vector<float> window;
};

}

#endif
