#ifndef _AudioCore_MidiPreview_h_
#define _AudioCore_MidiPreview_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <AudioCore/Transport.h>

using namespace Upp;

namespace AudioCore {

class MidiPreview {
public:
    MidiPreview();
    virtual ~MidiPreview();
    
    // Preview a single note
    void PreviewNote(int pitch, int velocity = 100, int duration = 500); // duration in ms
    
    // Preview a chord (multiple notes simultaneously)
    void PreviewChord(const Vector<int>& pitches, int velocity = 100, int duration = 500);
    
    // Set the instrument for preview (by ID or name)
    void SetInstrument(const String& instrumentName);
    void SetInstrument(int instrumentId);
    
    // Channel settings
    void SetChannel(int channel);
    int GetChannel() const { return currentChannel; }
    
    // Volume control
    void SetVolume(double volume); // 0.0 to 1.0
    double GetVolume() const { return volume; }
    
    // Transport integration
    void SetTransport(am::Transport* transport);
    am::Transport* GetTransport() const { return transport; }
    
    // Set the audio output device
    void SetOutputDevice(const String& deviceId);
    
    // Check if preview is available
    bool IsAvailable() const { return available; }
    
private:
    bool available;
    int currentChannel;
    double volume;
    String currentInstrument;
    am::Transport* transport;
    
    // Internal implementation
    void InternalPreviewNote(int pitch, int velocity, int duration);
    void InternalPreviewChord(const Vector<int>& pitches, int velocity, int duration);
};

}

#endif