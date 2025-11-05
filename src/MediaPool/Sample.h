#ifndef _MediaPool_Sample_h_
#define _MediaPool_Sample_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "MediaPool.h"

using namespace Upp;

namespace Sample {

// Forward declarations
class StreamEngine;
class RoundRobin;
class LoopPool;
class SliceEngine;
class TimeStretch;
class ArticulationEngine;
class MicMixer;
class PedalModel;
class VintageDAC;
class DFDStream;
class Zone;

// Type definitions
using SampleBuffer = Vector<double>;
using SampleRate = int;

// Stream engine for managing sample streaming
class StreamEngine {
public:
    StreamEngine();
    virtual ~StreamEngine();
    
    // Initialize the streaming engine with buffer size and sample rate
    virtual bool Initialize(int bufferSize, SampleRate sampleRate);
    
    // Load a sample file for streaming
    virtual bool LoadSample(const String& filePath);
    
    // Stream samples to output buffer
    virtual int Stream(SampleBuffer& output, int sampleCount);
    
    // Seek to a specific position in the sample
    virtual bool Seek(int samplePosition);
    
    // Get current playback position
    virtual int GetPosition() const;
    
    // Get total sample count
    virtual int GetTotalSamples() const;
    
    // Set streaming parameters
    virtual void SetLooping(bool enabled);
    virtual void SetLoopStart(int position);
    virtual void SetLoopEnd(int position);
    
    // Check if streaming is complete
    virtual bool IsFinished() const;
    
    // Reset the stream
    virtual void Reset();
    
protected:
    String filePath;
    SampleBuffer sampleData;
    int position;
    int totalSamples;
    bool isLooping;
    int loopStart;
    int loopEnd;
    int bufferSize;
    SampleRate sampleRate;
};

// Round-robin sample selector for multi-sampled instruments
class RoundRobin {
public:
    RoundRobin();
    
    // Add a sample variation to the round-robin set
    void AddSample(const String& samplePath);
    
    // Get the next sample in round-robin sequence
    String GetNextSample();
    
    // Get the current sample index
    int GetCurrentIndex() const { return currentIndex; }
    
    // Reset to first sample
    void Reset();
    
    // Get count of available samples
    int GetSampleCount() const { return samples.GetCount(); }
    
private:
    Vector<String> samples;
    int currentIndex;
};

// Loop pool for managing loop points
class LoopPool {
public:
    LoopPool();
    
    // Define a loop point
    struct LoopPoint : public Moveable<LoopPoint> {
        String name;
        int start;
        int end;
        bool enabled;
        bool isTempoSynced;
        
        LoopPoint() : start(0), end(0), enabled(true), isTempoSynced(false) {}
    };
    
    // Add a loop point
    void AddLoopPoint(const LoopPoint& loop);
    
    // Remove a loop point by name
    bool RemoveLoopPoint(const String& name);
    
    // Get a loop point by name
    const LoopPoint* GetLoopPoint(const String& name) const;
    
    // Get all loop points
    const Vector<LoopPoint>& GetLoopPoints() const { return loops; }
    
    // Find the best loop point for current position
    const LoopPoint* FindLoopForPosition(int samplePos) const;
    
    // Clear all loop points
    void Clear();
    
private:
    Vector<LoopPoint> loops;
};

// Slice engine for segment-based playback
class SliceEngine {
public:
    SliceEngine();
    
    // Define a slice
    struct Slice : public Moveable<Slice> {
        int start;
        int end;
        String name;
        
        Slice(int s, int e, const String& n) : start(s), end(e), name(n) {}
    };
    
    // Add a slice
    void AddSlice(const Slice& slice);
    
    // Get slice at a specific index
    const Slice* GetSlice(int index) const;
    
    // Get slice count
    int GetSliceCount() const { return slices.GetCount(); }
    
    // Get the slice containing a specific sample position
    const Slice* GetSliceForPosition(int samplePos) const;
    
    // Apply slicing to a sample buffer
    Vector<Slice> SliceBuffer(const SampleBuffer& buffer, int sliceCount);
    
    // Clear all slices
    void Clear();
    
private:
    Vector<Slice> slices;
};

// Time stretch processor
class TimeStretch {
public:
    TimeStretch();
    
    // Process buffer with time stretching
    void Process(const SampleBuffer& input, SampleBuffer& output, double stretchFactor);
    
    // Set time stretching parameters
    void SetWindowSize(int size);
    void SetOverlapRatio(double ratio);
    
    // Get/set algorithm type
    enum AlgorithmType {
        PhaseVocoder,
        Granular,
        WaveformSimilarity
    };
    
    void SetAlgorithm(AlgorithmType algo) { algorithm = algo; }
    AlgorithmType GetAlgorithm() const { return algorithm; }
    
private:
    AlgorithmType algorithm;
    int windowSize;
    double overlapRatio;
};

// Articulation engine for handling playing techniques
class ArticulationEngine {
public:
    ArticulationEngine();
    
    // Define an articulation
    struct Articulation : public Moveable<Articulation> {
        String name;
        String samplePath;
        int velocityStart;
        int velocityEnd;
        int keyStart;
        int keyEnd;
        double probability; // For randomizing articulation selection
        
        Articulation() : velocityStart(0), velocityEnd(127), keyStart(0), keyEnd(127), probability(1.0) {}
    };
    
    // Add an articulation
    void AddArticulation(const Articulation& articulation);
    
    // Get articulation for specific note and velocity
    const Articulation* GetArticulation(int note, int velocity) const;
    
    // Get all articulations
    const Vector<Articulation>& GetArticulations() const { return articulations; }
    
    // Clear all articulations
    void Clear();
    
private:
    Vector<Articulation> articulations;
};

// Microphone mixer for simulating different mic positions
class MicMixer {
public:
    MicMixer();
    
    // Define a microphone position
    struct MicPosition : public Moveable<MicPosition> {
        String name;
        double gain;
        double pan;
        double distance;
        double proximityEffect;
        
        MicPosition() : gain(1.0), pan(0.0), distance(1.0), proximityEffect(0.0) {}
    };
    
    // Add a microphone position
    void AddMicPosition(const MicPosition& mic);
    
    // Mix from multiple mics to stereo output
    void Mix(const Vector<SampleBuffer>& micInputs, SampleBuffer& leftOutput, SampleBuffer& rightOutput);
    
    // Get microphone positions
    const Vector<MicPosition>& GetMicPositions() const { return micPositions; }
    
    // Clear all positions
    void Clear();
    
private:
    Vector<MicPosition> micPositions;
};

// Pedal model for guitar effects simulation
class PedalModel {
public:
    PedalModel();
    
    enum PedalType {
        Distortion,
        Overdrive,
        Fuzz,
        Chorus,
        Flanger,
        Phaser,
        Delay,
        Reverb
    };
    
    // Process audio through the pedal
    void Process(const SampleBuffer& input, SampleBuffer& output);
    
    // Set pedal parameters
    void SetType(PedalType type);
    void SetDrive(double drive);
    void SetLevel(double level);
    void SetTone(double tone);
    
    // Set effect-specific parameters
    void SetRate(double rate);      // For modulation effects
    void SetDepth(double depth);    // For modulation effects
    void SetFeedback(double fb);    // For delay/reverb
    void SetMix(double mix);        // Dry/wet mix
    
private:
    PedalType type;
    double drive;
    double level;
    double tone;
    double rate;
    double depth;
    double feedback;
    double mix;
};

// Vintage DAC model for adding analog warmth
class VintageDAC {
public:
    VintageDAC();
    
    // Process audio through the DAC model
    void Process(const SampleBuffer& input, SampleBuffer& output);
    
    // Set vintage DAC parameters
    void SetWarmth(double warmth);      // Analog character
    void SetBitDepth(int bits);         // Effective bit depth
    void SetSampleRate(int rate);       // Effective sample rate
    void SetNoiseFloor(double noise);   // Added analog noise
    
private:
    double warmth;
    int bitDepth;
    int effectiveSampleRate;
    double noiseFloor;
};

// Dynamic frequency domain streaming
class DFDStream {
public:
    DFDStream();
    
    // Process buffer in frequency domain
    void Process(const SampleBuffer& input, SampleBuffer& output);
    
    // Set processing parameters
    void SetFFTSize(int size);
    void SetOverlap(int overlap);
    void SetFrequencyScale(double scale);
    
private:
    int fftSize;
    int overlap;
    double frequencyScale;
};

// Zone for mapping samples to keyboard ranges
class Zone {
public:
    Zone();
    
    // Define a zone
    struct Definition : public Moveable<Definition> {
        String samplePath;
        int keyLow;      // Low key (MIDI note number)
        int keyHigh;     // High key (MIDI note number)
        int velocityLow; // Low velocity threshold
        int velocityHigh;// High velocity threshold
        int rootKey;     // Root key for pitch playback
        double tune;     // Fine tune (in cents)
        double gain;     // Zone gain
        
        Definition() : keyLow(0), keyHigh(127), velocityLow(0), velocityHigh(127), 
                      rootKey(60), tune(0.0), gain(1.0) {}
    };
    
    // Add a zone
    void AddZone(const Definition& zone);
    
    // Get zone for specific note and velocity
    const Definition* GetZone(int note, int velocity) const;
    
    // Get all zones
    const Vector<Definition>& GetZones() const { return zones; }
    
    // Clear all zones
    void Clear();
    
private:
    Vector<Definition> zones;
};

} // namespace Sample

#endif