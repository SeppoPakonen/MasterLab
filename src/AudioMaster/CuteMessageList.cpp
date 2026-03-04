#include "AudioMaster.h"

CuteMessageList* CuteMessageList::instance = nullptr;
CuteMessageList::CuteMessageList() { instance = this; }
CuteMessageList::~CuteMessageList() { items.Clear(); if(instance == this) instance = nullptr; }
void CuteMessageList::Append(const String& text) { if(instance) instance->items.Add(text); RLOG(text); }
bool CuteMessageList::IsEmpty() { return instance ? instance->items.IsEmpty() : true; }
Vector<String> CuteMessageList::GetItems() { return instance ? clone(instance->items) : Vector<String>(); }
void CuteMessageList::Clear() { if(instance) instance->items.Clear(); }
