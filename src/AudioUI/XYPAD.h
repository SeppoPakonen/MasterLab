#ifndef _AudioUI_XYPAD_h_
#define _AudioUI_XYPAD_h_

#include <CtrlLib/CtrlLib.h>
#include <DSP/DSP.h>
using namespace Upp;

namespace UI {

// 2D control for controlling two parameters simultaneously
class XYPAD : public Ctrl {
public:
    typedef XYPAD CLASSNAME;
    
    XYPAD();
    virtual ~XYPAD();
    
    // Set/get the X parameter
    void SetXParameter(const Upp::String& name, double min_val = 0.0, double max_val = 1.0);
    Upp::String GetXParameter() const { return x_param_name; }
    
    // Set/get the Y parameter
    void SetYParameter(const Upp::String& name, double min_val = 0.0, double max_val = 1.0);
    Upp::String GetYParameter() const { return y_param_name; }
    
    // Set/get X and Y values directly (0.0 to 1.0 range)
    void SetValue(double x, double y);
    void GetValue(double& x, double& y) const;
    
    // Connect to DSP::ParameterSet for automatic parameter updates
    void ConnectToParameterSet(DSP::ParameterSet* param_set);
    
    // Set the mode for how the XYPAD behaves
    enum Mode {
        ABSOLUTE,   // Direct X/Y control
        RELATIVE    // Relative movement from current position
    };
    void SetMode(Mode mode) { this->mode = mode; }
    Mode GetMode() const { return mode; }
    
    // Set the range for how much of the XYPAD area is active
    void SetRange(double min_x, double max_x, double min_y, double max_y);
    
    // Event when parameters change
    Event<> WhenChanged;
    
protected:
    virtual void Paint(Draw& draw) override;
    virtual void LeftDown(Point p, dword keyflags) override;
    virtual void LeftUp(Point p, dword keyflags) override;
    virtual void MouseMove(Point p, dword keyflags) override;
    
private:
    Upp::String x_param_name;
    Upp::String y_param_name;
    double x_param_min, x_param_max;
    double y_param_min, y_param_max;
    double x_value, y_value;  // 0.0 to 1.0
    DSP::ParameterSet* connected_param_set;
    Mode mode;
    bool is_dragging;
    Point drag_start;
    Point last_mouse_pos;
    
    // Active range (0.0-1.0 values)
    double range_min_x, range_max_x;
    double range_min_y, range_max_y;
    
    // Convert from control coordinates to parameter values
    void ControlToParam(Point p, double& x, double& y) const;
    Point ParamToControl(double x, double y) const;
    
    void UpdateParameters();
};

}

#endif