#ifndef _VSTConnections_CuteConnect_h_
#define _VSTConnections_CuteConnect_h_

namespace VSTConnections {

class CutePortListItem {
public:
    CutePortListItem();
    virtual ~CutePortListItem();
    void SetPortName(const String& port_name);
    const String& GetPortName() const;
    void SetClientName(const String& client_name);
    const String& GetClientName() const;
    String GetClientPortName() const;
    void MarkPort(int mark);
    int GetPortMark() const;
    void AddConnect(CutePortListItem* port_item);
    void RemoveConnect(CutePortListItem* port_item);
    const Vector<CutePortListItem*>& GetConnects() const;
    void SetHilite(bool hilite);
    bool IsHilite() const;

private:
    String client_name;
    String port_name;
    int port_mark = 0;
    bool hilite = false;
    Vector<CutePortListItem*> connects;
};

class CuteClientListItem {
public:
    CuteClientListItem();
    virtual ~CuteClientListItem();
    void SetClientName(const String& client_name);
    const String& GetClientName() const;
    void MarkClient(int mark);
    int GetClientMark() const;
    void SetHilite(bool hilite);
    bool IsHilite() const;
    void SetOpen(bool open);
    bool IsOpen() const;

private:
    String client_name;
    int client_mark = 0;
    bool hilite = false;
    bool open = false;
};

class CuteClientListView : public ArrayCtrl {
public:
    typedef CuteClientListView CLASSNAME;
    CuteClientListView();
    void SetReadable(bool readable);
    bool IsReadable() const;
    void SetClientNameFilter(const String& client_name);
    String GetClientNameFilter() const;
    void SetPortNameFilter(const String& port_name);
    String GetPortNameFilter() const;

private:
    bool readable = false;
    String client_name_filter;
    String port_name_filter;
};

class CuteConnectorView : public Ctrl {
public:
    typedef CuteConnectorView CLASSNAME;
    CuteConnectorView();
};

class CuteConnect {
public:
    CuteConnect(CuteClientListView* output_list_view, CuteClientListView* input_list_view, CuteConnectorView* connector_view);
    virtual ~CuteConnect();
    virtual bool ConnectPorts(CutePortListItem* output_port, CutePortListItem* input_port);
    virtual bool DisconnectPorts(CutePortListItem* output_port, CutePortListItem* input_port);
    virtual void UpdateConnections();

private:
    Ptr<CuteClientListView> output_list_view;
    Ptr<CuteClientListView> input_list_view;
    Ptr<CuteConnectorView> connector_view;
};

}

#endif
