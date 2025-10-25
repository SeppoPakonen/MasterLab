#ifndef _TransportUI_CycleRange_h_
#define _TransportUI_CycleRange_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Range {
	double start = 0.0;
	double end = 0.0;
	
	bool IsValid() const { return end > start; }
	double GetLength() const { return IsValid() ? end - start : 0.0; }
};

class CycleRange {
public:
	void SetRange(const Range& range);
	Range GetRange() const { return range; }
	void Enable(bool enable);
	bool IsEnabled() const { return enabled; }
	void SetLoop(bool loop);
	bool IsLoop() const { return loop; }
	
private:
	Range range;
	bool enabled = false;
	bool loop = false;
};

}

#endif