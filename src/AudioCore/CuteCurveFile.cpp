#include "AudioCore.h"

CuteCurveFile::CuteCurveFile(CuteCurveList* curve_list) : curve_list(curve_list) {}
CuteCurveFile::~CuteCurveFile() { Clear(); }
void CuteCurveFile::SetList(CuteCurveList* curve_list) { this->curve_list = curve_list; }
CuteCurveList* CuteCurveFile::GetList() const { return curve_list; }
void CuteCurveFile::SetBaseDir(const String& base_dir) { this->base_dir = base_dir; }
const String& CuteCurveFile::GetBaseDir() const { return base_dir; }
void CuteCurveFile::SetFilename(const String& filename) { this->filename = filename; }
const String& CuteCurveFile::GetFilename() const { return filename; }
void CuteCurveFile::SetCurrentIndex(unsigned long current_index) { this->current_index = current_index; }
unsigned long CuteCurveFile::GetCurrentIndex() const { return current_index; }
const Array<CuteCurveFile::Item>& CuteCurveFile::GetItems() const { return items; }
CuteCurveFile::Item& CuteCurveFile::AddItem() { return items.Add(); }
void CuteCurveFile::Clear() { items.Clear(); current_index = 0; }
bool CuteCurveFile::IsEmpty() const { return items.IsEmpty(); }

void CuteCurveFile::Load(const String& serialized_state) {
    Clear();
    Vector<String> lines = Split(serialized_state, '\n');
    for(const String& line : lines) {
        if(line.IsEmpty())
            continue;
        if(line.StartsWith("filename="))
            filename = line.Mid(9);
        else if(line.StartsWith("current="))
            current_index = ScanUint64(line.Mid(8));
        else if(line.StartsWith("curve-item=")) {
            Item& item = items.Add();
            item.name = line.Mid(11);
            item.index = items.GetCount() - 1;
        }
    }
}

void CuteCurveFile::Save(CuteDocument* document, String& serialized_state, CuteTimeScale* time_scale) const {
    (void)document;
    (void)time_scale;
    String out;
    out << "filename=" << filename << '\n';
    out << "current=" << current_index << '\n';
    for(const Item& item : items)
        out << "curve-item=" << item.name << '\n';
    serialized_state = out;
}

void CuteCurveFile::Apply(CuteTimeScale* time_scale) {
    (void)time_scale;
    for(Item& item : items)
        item.subject = nullptr;
}

CuteCurve::Mode CuteCurveFile::ModeFromText(const String& text) {
    if(text.CompareNoCase("Linear") == 0)
        return CuteCurve::Linear;
    if(text.CompareNoCase("Spline") == 0)
        return CuteCurve::Spline;
    return CuteCurve::Hold;
}

String CuteCurveFile::TextFromMode(CuteCurve::Mode mode) {
    switch(mode) {
    case CuteCurve::Linear: return "Linear";
    case CuteCurve::Spline: return "Spline";
    default: return "Hold";
    }
}
