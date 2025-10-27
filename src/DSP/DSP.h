#ifndef _DSP_DSP_h_
#define _DSP_DSP_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <Math/Math.h>
using namespace Upp;

namespace DSP {

// Forward declarations
class SignalBus;
class ParameterSet;
class ModMatrix;
class LatencyBuffer;
class PresetManager;
class ZenCoreMFXCatalogue;
class Analyzer;
class SpectrumAnalyzer;
class LUFSMeter;
class ISPDetector;
class VoiceFeatureExtractor;
class HarmonyGenerator;
class StyleTransferNet;
class FormantMorpher;
class VoiceEncoder;
class VoiceDecoder;

// Basic types
typedef Vector<double> BufferView;
struct BusLayout {
    int channels;
    int sample_rate;
    String format; // "mono", "stereo", "surround", etc.
    
    BusLayout() : channels(2), sample_rate(44100) {}
    BusLayout(int ch, int sr) : channels(ch), sample_rate(sr) {}
};

}

#endif
