#ifndef _AudioFX_UI_XYPAD_h_
#define _AudioFX_UI_XYPAD_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "../Modulation.h"

using namespace Upp;

namespace UI {

// XY pad for controlling two parameters simultaneously
class XYPad : public Ctrl {
public:
    XYPad();
    virtual ~XYPad();
    
    // Set the parameter IDs for X and Y axes
    void SetParameterIds(const AudioFX::ParameterId& xId, const AudioFX::ParameterId& yId);
    
    // Set the current position (0.0-1.0 for both axes)
    void SetPosition(double x, double y);
    
    // Get the current position
    Point<double> GetPosition() const;
    
    // Set parameter set to control
    void SetParameterSet(AudioFX::ParameterSet* params);
    
    // Get the parameter values at current position
    ValueMap GetParameterValues() const;
    
    // Set sensitivity for X and Y axes
    void SetSensitivity(double xSens, double ySens);
    
    // Refresh the display
    void Refresh();
    
protected:
    virtual void Paint(Draw& draw) override;
    virtual void LeftDown(Point p, dword keyflags) override;
    virtual void LeftUp(Point p, dword keyflags) override;
    virtual void MouseMove(Point p, dword keyflags) override;
    virtual void Layout() override;
    
private:
    AudioFX::ParameterId paramX, paramY;
    AudioFX::ParameterSet* parameterSet;
    Point<double> position;
    Point<double> sensitivity;
    bool isDragging;
    
    void UpdateParameters();
    void UpdateFromParameters();
    void DrawHandle(Draw& draw);
};

} // namespace UI

#endif