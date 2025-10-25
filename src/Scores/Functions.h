#ifndef _Scores_Functions_h_
#define _Scores_Functions_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Functions {
public:
	Functions();
	void Transpose(int semitones);
	void Quantize();
	void Validate();
	
private:
	// Function implementations
};

}

#endif