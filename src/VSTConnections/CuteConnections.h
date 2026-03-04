#ifndef _VSTConnections_CuteConnections_h_
#define _VSTConnections_CuteConnections_h_

namespace VSTConnections {

class CuteConnectForm;
class CuteBus;

class CuteConnections : public TopWindow {
public:
    typedef CuteConnections CLASSNAME;
    CuteConnections();
    ~CuteConnections();
    CuteConnectForm* GetConnectForm() const;
    void ShowBus(CuteBus* bus, int bus_mode);
    void RefreshAll();
    void Clear();
    void Reset();

private:
    CuteConnectForm* connect_form = nullptr;
};

}

#endif
