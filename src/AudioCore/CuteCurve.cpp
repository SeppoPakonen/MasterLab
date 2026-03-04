#include "AudioCore.h"

CuteCurve::Cursor::Cursor(CuteCurve* curve) : curve(curve) {}
CuteCurve::Node* CuteCurve::Cursor::Seek(unsigned long frame) { this->frame = frame; return curve && !curve->GetNodes().IsEmpty() ? const_cast<CuteCurve::Node*>(&curve->GetNodes().Top()) : nullptr; }
void CuteCurve::Cursor::Reset(Node* node) { (void)node; node_index = -1; frame = 0; }
float CuteCurve::Cursor::Value(unsigned long frame) { Node* node = Seek(frame); return curve ? curve->Value(node, frame) : 0.0f; }
float CuteCurve::Cursor::Scale(unsigned long frame) { return curve ? curve->ScaleFromValue(Value(frame)) : 0.0f; }

CuteCurve::CuteCurve(CuteCurveList* list, CuteSubject* subject, Mode mode, unsigned int min_frame_dist)
    : list(list), subject(subject), mode(mode), min_frame_dist(min_frame_dist), cursor(this) {}
CuteCurve::~CuteCurve() {}
void CuteCurve::SetList(CuteCurveList* list) { this->list = list; }
CuteCurveList* CuteCurve::GetList() const { return list; }
void CuteCurve::SetMode(Mode mode) { this->mode = mode; }
CuteCurve::Mode CuteCurve::GetMode() const { return mode; }
void CuteCurve::SetMinFrameDist(unsigned int min_frame_dist) { this->min_frame_dist = min_frame_dist; }
unsigned int CuteCurve::GetMinFrameDist() const { return min_frame_dist; }
const Vector<CuteCurve::Node>& CuteCurve::GetNodes() const { return nodes; }
void CuteCurve::Clear() { nodes.Clear(); }
CuteCurve::Node* CuteCurve::AddNode(unsigned long frame, float value, CuteCurveEditList* edit_list) { (void)edit_list; Node& node = nodes.Add(); node.frame = frame; node.value = value; return &node; }
void CuteCurve::InsertNode(const Node& node) { nodes.Add(node); }
void CuteCurve::RemoveNode(int index) { if(index >= 0 && index < nodes.GetCount()) nodes.Remove(index); }
float CuteCurve::Value(const Node* node, unsigned long frame) const { (void)frame; return node ? node->value : default_value; }
float CuteCurve::Value(unsigned long frame) { return cursor.Value(frame); }
float CuteCurve::ValueFromScale(float scale) const { return scale; }
float CuteCurve::ScaleFromValue(float value) const { return value; }
void CuteCurve::SetDefaultValue(float default_value) { this->default_value = default_value; }
float CuteCurve::GetDefaultValue() const { return default_value; }
void CuteCurve::SetLength(unsigned long length) { this->length = length; }
unsigned long CuteCurve::GetLength() const { return length; }
void CuteCurve::Update() {}
CuteCurve::Cursor& CuteCurve::GetCursor() { return cursor; }
void CuteCurve::SetCapture(bool capture) { if(capture) state = (State)(state | Capture); else state = (State)(state & ~Capture); }
void CuteCurve::SetProcess(bool process) { if(process) state = (State)(state | Process); else state = (State)(state & ~Process); }
void CuteCurve::SetLocked(bool locked) { if(locked) state = (State)(state | Locked); else state = (State)(state & ~Locked); }
bool CuteCurve::IsIdle() const { return state == Idle; }
bool CuteCurve::IsProcess() const { return (state & Process) != 0; }
bool CuteCurve::IsCapture() const { return (state & Capture) != 0; }
bool CuteCurve::IsLocked() const { return (state & Locked) != 0; }
void CuteCurve::ProcessFrame(unsigned long frame) { (void)frame; }
void CuteCurve::CaptureFrame(unsigned long frame) { if(IsCapture()) AddNode(frame, default_value, nullptr); }
