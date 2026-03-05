#ifndef _AudioCore_CuteMonitor_h_
#define _AudioCore_CuteMonitor_h_

// Forward declarations if needed by non-GUI parts of CuteMonitor
// (none seem necessary for a purely audio monitoring class)

class CuteMonitor {
public:
    CuteMonitor(float gain = 1.0f, float panning = 0.0f);
    virtual ~CuteMonitor();

    // Purely audio related setters/getters
    void SetGain(float gain);
    float GetGain() const;
    float GetPrevGain() const;

    void SetPanning(float panning);
    float GetPanning() const;
    float GetPrevPanning() const;

    virtual void Update() = 0; // Still abstract, implementation will be in CuteMonitor.cpp

protected:
    float gain = 1.0f;
    float panning = 0.0f;
    float prev_gain = 1.0f; // Track previous gain for smooth updates
    float prev_panning = 0.0f; // Track previous panning for smooth updates
};

#endif
