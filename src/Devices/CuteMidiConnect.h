#ifndef _Devices_CuteMidiConnect_h_
#define _Devices_CuteMidiConnect_h_

class CuteMidiPortItem;
class CuteMidiClientItem;
class CuteMidiClientListView;
class CuteConnectorView;
class CutePortListItem;

class CuteMidiPortItem {
public:
    CuteMidiPortItem(CuteMidiClientItem* client_item = nullptr, unsigned long port_flags = 0);
    ~CuteMidiPortItem();
    void UpdatePortName();
private:
    unsigned long port_flags = 0;
};

class CuteMidiClientItem {
public:
    CuteMidiClientItem(CuteMidiClientListView* client_list_view = nullptr);
    ~CuteMidiClientItem();
    void UpdateClientName();
};

class CuteMidiClientListView {
public:
    CuteMidiClientListView();
    ~CuteMidiClientListView();
    void* GetAlsaClient() const;
    int UpdateClientPorts();
};

class CuteMidiConnect {
public:
    enum {
        ClientInput = 0,
        ClientOutput,
        PortInput,
        PortOutput,
        PortPhysicalInput,
        PortPhysicalOutput,
        IconCount,
    };

    CuteMidiConnect(CuteMidiClientListView* output_list_view = nullptr, CuteMidiClientListView* input_list_view = nullptr, CuteConnectorView* connector_view = nullptr);
    ~CuteMidiConnect();

    void* GetAlsaClient() const;
    static String GetIcon(int icon_index);
    bool ConnectPorts(CutePortListItem* output_port, CutePortListItem* input_port);
    bool DisconnectPorts(CutePortListItem* output_port, CutePortListItem* input_port);
    void UpdateConnections();
    void DisconnectPortsUpdate(CutePortListItem* output_port, CutePortListItem* input_port);

private:
    void CreateIcons();
    void DeleteIcons();

    CuteMidiClientListView* output_list_view = nullptr;
    CuteMidiClientListView* input_list_view = nullptr;
    CuteConnectorView* connector_view = nullptr;
    static Vector<String> icons;
    static int icon_ref_count;
};

#endif
