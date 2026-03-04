#ifndef _VSTConnections_CuteConnectForm_h_
#define _VSTConnections_CuteConnectForm_h_

namespace VSTConnections {

class CuteAudioConnect;
class CuteMidiConnect;

class CuteConnectForm : public ParentCtrl {
public:
    typedef CuteConnectForm CLASSNAME;
    CuteConnectForm();
    void AudioIClientChanged();
    void AudioOClientChanged();
    void AudioConnectSelected();
    void AudioDisconnectSelected();
    void AudioDisconnectAll();
    void AudioRefresh();
    void MidiIClientChanged();
    void MidiOClientChanged();
    void MidiConnectSelected();
    void MidiDisconnectSelected();
    void MidiDisconnectAll();
    void MidiRefresh();
    void RefreshAll();

private:
    CuteAudioConnect* audio_connect = nullptr;
    CuteMidiConnect* midi_connect = nullptr;
};

}

#endif
