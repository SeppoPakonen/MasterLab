#ifndef _Tooling_CuteObserver_h_
#define _Tooling_CuteObserver_h_

class CuteCurve;
class CuteObserver;

class CuteSubject {
public:
    CuteSubject(float value = 0.0f, float default_value = 0.0f);
    ~CuteSubject();
    void SetValue(float value, CuteObserver* sender = nullptr);
    float GetValue() const;
    float GetPrevValue() const;
    float GetLastValue() const;
    void Notify(CuteObserver* sender, float value, bool update);
    void Attach(CuteObserver* observer);
    void Detach(CuteObserver* observer);
    void SetQueued(bool queued);
    bool IsQueued() const;
    float* Data();
    void SetName(const String& name);
    const String& GetName() const;
    void SetMaxValue(float max_value);
    float GetMaxValue() const;
    void SetMinValue(float min_value);
    float GetMinValue() const;
    void SetDefaultValue(float default_value);
    float GetDefaultValue() const;
    void ResetValue(CuteObserver* sender = nullptr);
    void SetToggled(bool toggled);
    bool IsToggled() const;
    void SetInteger(bool integer);
    bool IsInteger() const;
    bool IsDecimal() const;
    float SafeValue(float value) const;
    float ValueFromScale(float scale) const;
    float ScaleFromValue(float value) const;
    void SetCurve(CuteCurve* curve);
    CuteCurve* GetCurve() const;

private:
    float value = 0.0f;
    bool queued = false;
    float prev_value = 0.0f;
    float last_value = 0.0f;
    String name;
    float min_value = 0.0f;
    float max_value = 1.0f;
    float default_value = 0.0f;
    bool toggled = false;
    bool integer = false;
    CuteCurve* curve = nullptr;
    Vector<CuteObserver*> observers;
};

class CuteObserver {
public:
    CuteObserver(CuteSubject* subject = nullptr);
    virtual ~CuteObserver();
    void SetSubject(CuteSubject* subject);
    CuteSubject* GetSubject() const;
    virtual void Update(bool update);
private:
    CuteSubject* subject = nullptr;
};

#endif
