#include "Devices.h"

CuteNsmClient::CuteNsmClient() {}
void CuteNsmClient::SetClientName(const String& client_name) { this->client_name = client_name; }
const String& CuteNsmClient::GetClientName() const { return client_name; }
bool CuteNsmClient::Open() { opened = true; return true; }
void CuteNsmClient::Close() { opened = false; }
bool CuteNsmClient::IsOpen() const { return opened; }
