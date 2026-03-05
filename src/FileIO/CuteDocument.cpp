#include "FileIO.h"

String CuteDocument::default_ext = "cute";
String CuteDocument::template_ext = "cutetpl";
String CuteDocument::archive_ext = "cutear";
Vector<String> CuteDocument::extracted_archives;
CuteDocument* CuteDocument::current_document = nullptr;

CuteDocument::CuteDocument(const String& tag_name, Flags flags) : tag_name(tag_name), flags(flags) { current_document = this; }
CuteDocument::~CuteDocument() { if(current_document == this) current_document = nullptr; }
const String& CuteDocument::GetTagName() const { return tag_name; }
void CuteDocument::SaveTextElement(const String& tag_name, const String& text, String& out) const { out << '<' << tag_name << '>' << text << "</" << tag_name << ">\n"; }
bool CuteDocument::IsTemplate() const { return (flags & Template) != 0; }
bool CuteDocument::IsArchive() const { return (flags & Archive) != 0; }
bool CuteDocument::IsTemporary() const { return (flags & Temporary) != 0; }
bool CuteDocument::IsSymLink() const { return (flags & SymLink) != 0; }
String CuteDocument::AddFile(const String& filename) { temp_files.Add(filename); return filename; }
bool CuteDocument::Load(const String& filename, Flags flags) { this->flags = flags; name = GetFileTitle(filename); String data = LoadFile(filename); return !data.IsVoid() && LoadElement(data); }
bool CuteDocument::Save(const String& filename, Flags flags) { this->flags = flags; name = GetFileTitle(filename); String data; if(!SaveElement(data)) return false; SaveFile(filename, data); return true; }
bool CuteDocument::BoolFromText(const String& text) {
	String lower_text = ToLower(text);
	return lower_text == "true" || lower_text == "1" || lower_text == "yes";
}
String CuteDocument::TextFromBool(bool value) { return value ? "true" : "false"; }
void CuteDocument::SetDefaultExt(const String& default_ext) { CuteDocument::default_ext = default_ext; }
void CuteDocument::SetTemplateExt(const String& template_ext) { CuteDocument::template_ext = template_ext; }
void CuteDocument::SetArchiveExt(const String& archive_ext) { CuteDocument::archive_ext = archive_ext; }
const String& CuteDocument::DefaultExt() { return default_ext; }
const String& CuteDocument::TemplateExt() { return template_ext; }
const String& CuteDocument::ArchiveExt() { return archive_ext; }
const Vector<String>& CuteDocument::ExtractedArchives() { return extracted_archives; }
void CuteDocument::ClearExtractedArchives(bool remove) { (void)remove; extracted_archives.Clear(); }
String CuteDocument::AddFile(const String& dir, const String& filename) { return AppendFileName(dir, GetFileName(filename)); }
void CuteDocument::SetFlags(Flags flags) { this->flags = flags; }
CuteDocument::Flags CuteDocument::GetFlags() const { return flags; }
