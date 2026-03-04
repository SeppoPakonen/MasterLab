#ifndef _VSTConnections_CuteBusForm_h_
#define _VSTConnections_CuteBusForm_h_

namespace VSTConnections {

class CuteBus;

class CuteBusForm : public TopWindow {
public:
    typedef CuteBusForm CLASSNAME;
    enum { Create = 1, Update = 2, Delete = 4, MoveUp = 8, MoveDown = 16 };

    CuteBusForm();
    void SetBus(CuteBus* bus);
    CuteBus* GetBus() const;
    bool IsDirty() const;
    unsigned int GetFlags() const;
    void ShowBus(CuteBus* bus);
    bool UpdateBus(CuteBus* bus);
    void UpdateMidiInstruments();
    void UpdateMidiSysex();
    void ResetPluginLists();
    void RefreshBuses();
    void Reject();
    void SelectBus();
    void MoveUpBus();
    void MoveDownBus();
    void CreateBus();
    void UpdateBus();
    void DeleteBus();
    void Changed();
    void StabilizeForm();
    void ContextMenu();
    void MidiSysex();

private:
    CuteBus* bus = nullptr;
    int dirty_setup = 0;
    int dirty_count = 0;
    int dirty_total = 0;
};

}

#endif
