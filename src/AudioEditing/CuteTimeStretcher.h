#ifndef _AudioEditing_CuteTimeStretcher_h_
#define _AudioEditing_CuteTimeStretcher_h_

class CuteTimeStretcher {
public:
    enum Flags {
        None = 0,
        WsolaTimeStretch = 1 << 0,
        WsolaQuickSeek = 1 << 1,
        RubberBandFormant = 1 << 2,
        RubberBandFinerR3 = 1 << 3,
    };

    CuteTimeStretcher();
    ~CuteTimeStretcher();

    int Process(const Vector<float>& input, Vector<float>& output);
    int Retrieve(Vector<float>& output);
    int Available() const;
    void Flush();
    void Reset();

private:
    Vector<float> staging;
};

#endif
