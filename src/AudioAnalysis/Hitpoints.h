#ifndef _AudioAnalysis_Hitpoints_h_
#define _AudioAnalysis_Hitpoints_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Hitpoint {
	double time;
	double strength;
};

class Hitpoints {
public:
	Hitpoints();
	const Upp::Vector<Hitpoint>& Calculate(const double* samples, int count, int sampleRate);
	const Upp::Vector<Hitpoint>& GetHitpoints() const { return hitpoints; }
	void CreateSlices();
	void CreateGroove();
	void CreateMarkers();
	void Divide();
	void Remove();
	
private:
	Upp::Vector<Hitpoint> hitpoints;
};

}

#endif