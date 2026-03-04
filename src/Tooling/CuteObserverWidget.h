#ifndef _Tooling_CuteObserverWidget_h_
#define _Tooling_CuteObserverWidget_h_

template <class T>
class CuteObserverWidget : public T {
public:
    typedef CuteObserverWidget CLASSNAME;
    CuteObserverWidget() = default;
    void SetSubject(CuteSubject* subject) { observer.SetSubject(subject); }
    CuteSubject* GetSubject() const { return observer.GetSubject(); }
protected:
    CuteObserver observer;
};

class CuteObserverCheckBox : public CuteObserverWidget<Option> {
public:
    typedef CuteObserverCheckBox CLASSNAME;
};

class CuteObserverSpinBox : public CuteObserverWidget<EditInt> {
public:
    typedef CuteObserverSpinBox CLASSNAME;
};

class CuteObserverSlider : public CuteObserverWidget<SliderCtrl> {
public:
    typedef CuteObserverSlider CLASSNAME;
};

#endif
