#ifndef _Devices_CuteNsmClient_h_
#define _Devices_CuteNsmClient_h_

class CuteNsmClient {
public:
    enum ReplyCode { Ok = 0, Error = -1, Failed = -2 };

    CuteNsmClient();
    void SetClientName(const String& client_name);
    const String& GetClientName() const;
    bool Open();
    void Close();
    bool IsOpen() const;

private:
    String client_name;
    bool opened = false;
};

#endif
