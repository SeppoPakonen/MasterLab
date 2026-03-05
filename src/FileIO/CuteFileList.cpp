#include "FileIO.h"

CuteFileList::CuteFileList() {}
CuteFileList::~CuteFileList() { Clear(); }
CuteFileList::Item& CuteFileList::AddFile(const Key& key, const String& name) { Item& item = items.Add(); item.key = key; item.name = name; return item; }
CuteFileList::Item* CuteFileList::FindFile(const Key& key) { for(Item& item : items) if(item.key == key) return &item; return nullptr; }
void CuteFileList::RemoveFile(const Key& key) { for(int i = 0; i < items.GetCount(); ++i) if(items[i].key == key) { items.Remove(i); break; } }
void CuteFileList::Clear() { items.Clear(); }
const Array<CuteFileList::Item>& CuteFileList::GetItems() const { return items; }
