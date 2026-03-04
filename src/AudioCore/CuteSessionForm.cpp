#include "AudioCore.h"

CuteSessionForm::CuteSessionForm() {
    Title("Cute Session");
    Sizeable().Zoomable();
    Add(session_dir.TopPosZ(8, 24).HSizePosZ(8, 8));
    Add(session_name.TopPosZ(40, 24).HSizePosZ(8, 8));
    Add(description.VSizePosZ(72, 8).HSizePosZ(8, 8));
}
void CuteSessionForm::SetSession(CuteSession* session, bool session_dir_enabled) { this->session = session; this->session_dir_enabled = session_dir_enabled; if (session) properties = session->GetProperties(); session_dir.SetData(properties.session_dir); session_name.SetData(properties.session_name); description.SetData(properties.description); }
const CuteSession::Properties& CuteSessionForm::GetProperties() const { return properties; }
bool CuteSessionForm::IsSessionDirEnabled() const { return session_dir_enabled; }
