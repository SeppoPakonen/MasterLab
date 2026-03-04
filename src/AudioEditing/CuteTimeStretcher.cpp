#include "AudioEditing.h"

CuteTimeStretcher::CuteTimeStretcher() {}
CuteTimeStretcher::~CuteTimeStretcher() {}
int CuteTimeStretcher::Process(const Vector<float>& input, Vector<float>& output) { output = input; staging = input; return output.GetCount(); }
int CuteTimeStretcher::Retrieve(Vector<float>& output) { output = staging; return output.GetCount(); }
int CuteTimeStretcher::Available() const { return staging.GetCount(); }
void CuteTimeStretcher::Flush() { staging.Clear(); }
void CuteTimeStretcher::Reset() { staging.Clear(); }
