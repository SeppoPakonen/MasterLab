#ifndef _AudioCore_CuteEngine_h_
#define _AudioCore_CuteEngine_h_

class CuteBus;
class CuteCurveFile;
class CutePluginList;
class CuteSessionCursor;

class CuteEngine {
public:
    CuteEngine();
    virtual ~CuteEngine();

    void SetName(const String& name);
    const String& GetName() const;

    void SetActivated(bool activated);
    bool IsActivated() const;

    void SetRunning(bool running);
    bool IsRunning() const;

    void SetBufferSize(int buffer_size);
    int GetBufferSize() const;

    void SetSampleRate(int sample_rate);
    int GetSampleRate() const;

    void Open();
    void Close();
    void Start();
    void Stop();
    void Reset();

private:
    String name;
    bool activated = false;
    bool running = false;
    int buffer_size = 0;
    int sample_rate = 0;
};

class CuteBus {
public:
    enum BusMode { None = 0, Input = 1, Output = 2, Duplex = 3, Ex = 4 };

    CuteBus();
    virtual ~CuteBus();

    void SetName(const String& name);
    const String& GetName() const;

    void SetMode(BusMode mode);
    BusMode GetMode() const;

    void SetMonitor(bool monitor);
    bool IsMonitor() const;

    void SetGain(double gain);
    double GetGain() const;

    void SetPanning(double panning);
    double GetPanning() const;

private:
    String name;
    BusMode mode = None;
    bool monitor = false;
    double gain = 1.0;
    double panning = 0.0;
};

#endif
