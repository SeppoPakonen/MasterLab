#include "ProjectMgmt.h"

CuteCommand::CuteCommand(const String& name) : name(name) {}
CuteCommand::~CuteCommand() {}
void CuteCommand::SetName(const String& name) { this->name = name; }
const String& CuteCommand::GetName() const { return name; }
unsigned int CuteCommand::GetFlags() const { return flags; }
void CuteCommand::SetAutoDelete(bool auto_delete) { SetFlags(AutoDelete, auto_delete); }
bool CuteCommand::IsAutoDelete() const { return IsFlags(AutoDelete); }
void CuteCommand::SetRefresh(bool refresh) { SetFlags(Refresh, refresh); }
bool CuteCommand::IsRefresh() const { return IsFlags(Refresh); }
void CuteCommand::SetClearSelect(bool clear_select) { SetFlags(ClearSelect, clear_select); }
bool CuteCommand::IsClearSelect() const { return IsFlags(ClearSelect); }
void CuteCommand::SetClearSelectReset(bool clear_select_reset) { SetFlags(ClearSelectReset, clear_select_reset); }
bool CuteCommand::IsClearSelectReset() const { return IsFlags(ClearSelectReset); }
void CuteCommand::SetFlags(unsigned int flags, bool is_on) { if(is_on) this->flags |= flags; else this->flags &= ~flags; }
bool CuteCommand::IsFlags(unsigned int flags) const { return (this->flags & flags) == flags; }
CuteCommandList::CuteCommandList() {}
CuteCommandList::~CuteCommandList() { Clear(); }
void CuteCommandList::Clear() { commands.Clear(); last_command = nullptr; }
CuteCommand* CuteCommandList::GetLastCommand() const { return last_command; }
CuteCommand* CuteCommandList::GetNextCommand() const { return nullptr; }
void CuteCommandList::RemoveLastCommand() { last_command = nullptr; }
void CuteCommandList::Backout(CuteCommand* command) { (void)command; }
bool CuteCommandList::Push(CuteCommand* command) { commands.Add(command); last_command = command; return true; }
bool CuteCommandList::Execute(CuteCommand* command) { if(!command) return false; if(command->Redo()) return Push(command); return false; }
bool CuteCommandList::Undo() { return last_command ? last_command->Undo() : false; }
bool CuteCommandList::Redo() { return last_command ? last_command->Redo() : false; }
