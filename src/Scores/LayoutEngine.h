#ifndef _Scores_LayoutEngine_h_
#define _Scores_LayoutEngine_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class LayoutEngine {
public:
	LayoutEngine();
	void Layout();
	void SetPageSize(int width, int height);
	void SetMargins(double left, double right, double top, double bottom);
	
private:
	int page_width;
	int page_height;
	double margin_left;
	double margin_right;
	double margin_top;
	double margin_bottom;
};

}

#endif