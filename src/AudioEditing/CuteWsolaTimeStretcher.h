#ifndef _AudioEditing_CuteWsolaTimeStretcher_h_
#define _AudioEditing_CuteWsolaTimeStretcher_h_

class CuteWsolaTimeStretcher {
public:
    CuteWsolaTimeStretcher();

    void SetRatio(double ratio);
    double GetRatio() const;
    int Process(const Vector<float>& input, Vector<float>& output);
    void Reset();

private:
    double ratio = 1.0;
};

#endif
