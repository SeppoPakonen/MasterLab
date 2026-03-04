#include "MIDI.h"

void CuteMidiEngineProxy::NotifyMmcEvent(const CuteCtlEvent& mmc_event) { (void)mmc_event; }
void CuteMidiEngineProxy::NotifyCtlEvent(const CuteCtlEvent& ctl_event) { (void)ctl_event; }
void CuteMidiEngineProxy::NotifySppEvent(int spp_cmd, unsigned short song_pos) { (void)spp_cmd; (void)song_pos; }
void CuteMidiEngineProxy::NotifyClkEvent(float tempo) { (void)tempo; }
void CuteMidiEngineProxy::NotifyInpEvent(unsigned short flags) { (void)flags; }

CuteMidiEngine::CuteMidiEngine() {}
bool CuteMidiEngine::Init() { return true; }
CuteMidiEngineProxy* CuteMidiEngine::GetProxy() { return &proxy; }
void CuteMidiEngine::Process() {}
void CuteMidiEngine::Sync() {}
void CuteMidiEngine::ResetTime() {}
void CuteMidiEngine::ResetSync() {}
void CuteMidiEngine::ResetTempo() {}
void CuteMidiEngine::ResetAllMonitors() {}
void CuteMidiEngine::ResetAllControllers(bool force_immediate) { reset_all_controllers_pending = !force_immediate; }
bool CuteMidiEngine::IsResetAllControllersPending() const { return reset_all_controllers_pending; }
void CuteMidiEngine::ShutOffAllBuses(bool close) { (void)close; }
void CuteMidiEngine::ShutOffAllTracks() {}
void CuteMidiEngine::SetReadAhead(unsigned int read_ahead) { this->read_ahead = read_ahead; }
unsigned int CuteMidiEngine::GetReadAhead() const { return read_ahead; }
