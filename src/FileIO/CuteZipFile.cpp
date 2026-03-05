#include "FileIO.h"

CuteZipFile::CuteZipFile() {}
bool CuteZipFile::Open(const String& path, bool write_mode) { this->path = path; this->write_mode = write_mode; is_open = true; return true; }
void CuteZipFile::Close() { is_open = false; }
bool CuteZipFile::IsOpen() const { return is_open; }
bool CuteZipFile::AddEntry(const String& name, const String& content) { if (!is_open || !write_mode) return false; int index = entries.Find(name); if (index < 0) entries.Add(name, content); else entries[index] = content; return true; }
bool CuteZipFile::ExtractEntry(const String& name, String& content) const { int index = entries.Find(name); if (index < 0) return false; content = entries[index]; return true; }
Vector<String> CuteZipFile::GetEntryNames() const { Vector<String> names; for (int i = 0; i < entries.GetCount(); ++i) names.Add(entries.GetKey(i)); return names; }
