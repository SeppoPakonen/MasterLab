#ifndef _TransportUI_PrePostRoll_h_
#define _TransportUI_PrePostRoll_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class PrePostRoll {
public:
	void SetPreRoll(double seconds);
	double GetPreRoll() const { return pre_roll_seconds; }
	void SetPostRoll(double seconds);
	double GetPostRoll() const { return post_roll_seconds; }
	void EnablePreRoll(bool enable);
	bool IsPreRollEnabled() const { return pre_roll_enabled; }
	void EnablePostRoll(bool enable);
	bool IsPostRollEnabled() const { return post_roll_enabled; }
	
private:
	double pre_roll_seconds = 0.0;
	double post_roll_seconds = 0.0;
	bool pre_roll_enabled = false;
	bool post_roll_enabled = false;
};

}

#endif