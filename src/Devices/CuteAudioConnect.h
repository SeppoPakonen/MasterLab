#ifndef _Devices_CuteAudioConnect_h_
#define _Devices_CuteAudioConnect_h_

class CuteAudioPortItem;
class CuteAudioClientItem;
class CuteAudioClientListView;
class CuteConnectorView;
class CutePortListItem;

class CuteAudioPortItem {
public:
	CuteAudioPortItem(CuteAudioClientItem* client_item, unsigned long port_flags);
	~CuteAudioPortItem();
	void UpdatePortName();

private:
	unsigned long port_flags = 0;
};

class CuteAudioClientItem {
public:
	CuteAudioClientItem(CuteAudioClientListView* client_list_view);
	~CuteAudioClientItem();
	void UpdateClientName();
};

class CuteAudioClientListView {
public:
	CuteAudioClientListView();
	~CuteAudioClientListView();
	void* GetJackClient() const;
	int UpdateClientPorts();
};

class CuteAudioConnect {
public:
	enum {
		ClientIn = 0,
		ClientOut,
		PortIn,
		PortOut,
		PortPhysIn,
		PortPhysOut,
		IconCount,
	};

	CuteAudioConnect(CuteAudioClientListView* output_list_view, CuteAudioClientListView* input_list_view, CuteConnectorView* connector_view);
	~CuteAudioConnect();
	void* GetJackClient() const;
	static String GetIcon(int icon_index);
	bool ConnectPorts(CutePortListItem* output_port, CutePortListItem* input_port);
	bool DisconnectPorts(CutePortListItem* output_port, CutePortListItem* input_port);
	void UpdateConnections();
	void DisconnectPortsUpdate(CutePortListItem* output_port, CutePortListItem* input_port);

private:
	void CreateIcons();
	void DeleteIcons();

	CuteAudioClientListView* output_list_view = nullptr;
	CuteAudioClientListView* input_list_view = nullptr;
	CuteConnectorView* connector_view = nullptr;
	static Vector<String> icons;
	static int icon_ref_count;
};

#endif
