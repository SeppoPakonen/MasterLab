#include "AudioEditing.h"

CuteWsolaTimeStretcher::CuteWsolaTimeStretcher() {}
void CuteWsolaTimeStretcher::SetRatio(double ratio) { this->ratio = max(0.1, ratio); }
double CuteWsolaTimeStretcher::GetRatio() const { return ratio; }
int CuteWsolaTimeStretcher::Process(const Vector<float>& input, Vector<float>& output) { output = input; return output.GetCount(); }
void CuteWsolaTimeStretcher::Reset() {}
