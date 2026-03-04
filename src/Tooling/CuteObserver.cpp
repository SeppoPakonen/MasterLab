#include "Tooling.h"

CuteSubject::CuteSubject(float value, float default_value) : value(value), prev_value(value), last_value(value), default_value(default_value) {}
CuteSubject::~CuteSubject() {}
void CuteSubject::SetValue(float value, CuteObserver* sender) { prev_value = this->value; this->value = SafeValue(value); Notify(sender, this->value, true); }
float CuteSubject::GetValue() const { return value; }
float CuteSubject::GetPrevValue() const { return prev_value; }
float CuteSubject::GetLastValue() const { return last_value; }
void CuteSubject::Notify(CuteObserver* sender, float value, bool update) { (void)sender; last_value = value; for(CuteObserver* o : observers) if(o) o->Update(update); }
void CuteSubject::Attach(CuteObserver* observer) { if(observers.Find(observer) < 0) observers.Add(observer); }
void CuteSubject::Detach(CuteObserver* observer) { int i = observers.Find(observer); if(i >= 0) observers.Remove(i); }
void CuteSubject::SetQueued(bool queued) { this->queued = queued; }
bool CuteSubject::IsQueued() const { return queued; }
float* CuteSubject::Data() { return &value; }
void CuteSubject::SetName(const String& name) { this->name = TrimBoth(name); }
const String& CuteSubject::GetName() const { return name; }
void CuteSubject::SetMaxValue(float max_value) { this->max_value = max_value; }
float CuteSubject::GetMaxValue() const { return max_value; }
void CuteSubject::SetMinValue(float min_value) { this->min_value = min_value; }
float CuteSubject::GetMinValue() const { return min_value; }
void CuteSubject::SetDefaultValue(float default_value) { this->default_value = default_value; }
float CuteSubject::GetDefaultValue() const { return default_value; }
void CuteSubject::ResetValue(CuteObserver* sender) { SetValue(default_value, sender); }
void CuteSubject::SetToggled(bool toggled) { this->toggled = toggled; }
bool CuteSubject::IsToggled() const { return toggled; }
void CuteSubject::SetInteger(bool integer) { this->integer = integer; }
bool CuteSubject::IsInteger() const { return integer; }
bool CuteSubject::IsDecimal() const { return !toggled && !integer; }
float CuteSubject::SafeValue(float value) const { if(toggled) { float threshold = 0.5f * (min_value + max_value); return value > threshold ? max_value : min_value; } if(value > max_value) value = max_value; if(value < min_value) value = min_value; if(integer) value = floorf(value); return value; }
float CuteSubject::ValueFromScale(float scale) const { return min_value + scale * (max_value - min_value); }
float CuteSubject::ScaleFromValue(float value) const { return (value - min_value) / max(0.0001f, max_value - min_value); }
void CuteSubject::SetCurve(CuteCurve* curve) { this->curve = curve; }
CuteCurve* CuteSubject::GetCurve() const { return curve; }
CuteObserver::CuteObserver(CuteSubject* subject) : subject(subject) { if(subject) subject->Attach(this); }
CuteObserver::~CuteObserver() { if(subject) subject->Detach(this); }
void CuteObserver::SetSubject(CuteSubject* subject) { if(this->subject) this->subject->Detach(this); this->subject = subject; if(this->subject) this->subject->Attach(this); }
CuteSubject* CuteObserver::GetSubject() const { return subject; }
void CuteObserver::Update(bool update) { (void)update; }
