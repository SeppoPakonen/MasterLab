#include "XYPAD.h"

namespace UI {

XYPAD::XYPAD() : x_param_min(0.0), x_param_max(1.0), 
                 y_param_min(0.0), y_param_max(1.0),
                 x_value(0.5), y_value(0.5), 
                 connected_param_set(nullptr), 
                 mode(ABSOLUTE), 
                 is_dragging(false),
                 range_min_x(0.0), range_max_x(1.0),
                 range_min_y(0.0), range_max_y(1.0) {
    NoWantFocus();
    SetFrame(ThinInsetFrame());
}

XYPAD::~XYPAD() {
    // Clean up
}

void XYPAD::SetXParameter(const Upp::String& name, double min_val, double max_val) {
    x_param_name = name;
    x_param_min = min_val;
    x_param_max = max_val;
}

void XYPAD::SetYParameter(const Upp::String& name, double min_val, double max_val) {
    y_param_name = name;
    y_param_min = min_val;
    y_param_max = max_val;
}

void XYPAD::SetValue(double x, double y) {
    x_value = max(0.0, min(1.0, x)); // Clamp to 0-1 range
    y_value = max(0.0, min(1.0, y)); // Clamp to 0-1 range
    
    if (connected_param_set) {
        // Update the connected parameter set
        if (!x_param_name.IsEmpty()) {
            double x_param_val = x_param_min + x_value * (x_param_max - x_param_min);
            connected_param_set->SetValue(x_param_name, x_param_val);
        }
        if (!y_param_name.IsEmpty()) {
            double y_param_val = y_param_min + y_value * (y_param_max - y_param_min);
            connected_param_set->SetValue(y_param_name, y_param_val);
        }
    }
    
    Refresh();
    if (WhenChanged)
        WhenChanged();
}

void XYPAD::GetValue(double& x, double& y) const {
    x = x_value;
    y = y_value;
}

void XYPAD::ConnectToParameterSet(DSP::ParameterSet* param_set) {
    connected_param_set = param_set;
    
    // Initialize values from parameter set if available
    if (connected_param_set && !x_param_name.IsEmpty() && !y_param_name.IsEmpty()) {
        double x_param_val = connected_param_set->GetValue(x_param_name);
        double y_param_val = connected_param_set->GetValue(y_param_name);
        
        // Convert parameter values back to 0-1 range
        double x_norm = (x_param_val - x_param_min) / (x_param_max - x_param_min);
        double y_norm = (y_param_val - y_param_min) / (y_param_max - y_param_min);
        
        SetValue(x_norm, y_norm);
    }
}

void XYPAD::SetRange(double min_x, double max_x, double min_y, double max_y) {
    range_min_x = min_x;
    range_max_x = max_x;
    range_min_y = min_y;
    range_max_y = max_y;
}

void XYPAD::Paint(Draw& draw) {
    // Draw background
    draw.DrawRect(GetSize(), White());
    
    // Draw grid
    Size sz = GetSize();
    for (int i = 1; i < 10; i++) {
        int x = (sz.cx * i) / 10;
        int y = (sz.cy * i) / 10;
        draw.DrawLine(x, 0, x, sz.cy, 1, LtGray());
        draw.DrawLine(0, y, sz.cx, y, 1, LtGray());
    }
    
    // Draw crosshair lines
    draw.DrawLine(0, sz.cy/2, sz.cx, sz.cy/2, 1, Gray());
    draw.DrawLine(sz.cx/2, 0, sz.cx/2, sz.cy, 1, Gray());
    
    // Draw the current position
    Point pos = ParamToControl(x_value, y_value);
    draw.DrawEllipse(pos.x - 6, pos.y - 6, 12, 12, Red());
    draw.DrawEllipse(pos.x - 6, pos.y - 6, 12, 12, 1, Black());
}

void XYPAD::LeftDown(Point p, dword keyflags) {
    is_dragging = true;
    last_mouse_pos = p;
    drag_start = p;
    
    // Set the value directly to where the user clicked
    double x, y;
    ControlToParam(p, x, y);
    SetValue(x, y);
    
    SetCapture();
    Refresh();
}

void XYPAD::LeftUp(Point p, dword keyflags) {
    if (is_dragging) {
        is_dragging = false;
        ReleaseCapture();
    }
}

void XYPAD::MouseMove(Point p, dword keyflags) {
    if (is_dragging) {
        if (mode == ABSOLUTE) {
            // Direct mapping of mouse position to value
            double x, y;
            ControlToParam(p, x, y);
            SetValue(x, y);
        } else {
            // Relative movement from starting position
            Size delta = p - drag_start;
            double dx = (double)delta.cx / GetSize().cx;
            double dy = (double)delta.cy / GetSize().cy;
            
            double new_x = x_value + dx;
            double new_y = y_value + dy;
            SetValue(new_x, new_y);
            
            // Update drag start for continuous relative movement
            drag_start = p;
        }
    }
    last_mouse_pos = p;
}

void XYPAD::ControlToParam(Point p, double& x, double& y) const {
    Size sz = GetSize();
    x = max(0.0, min(1.0, (double)p.x / sz.cx));
    y = max(0.0, min(1.0, 1.0 - (double)p.y / sz.cy)); // Y is inverted (top = 0)
}

Point XYPAD::ParamToControl(double x, double y) const {
    Size sz = GetSize();
    int px = (int)(x * sz.cx);
    int py = (int)((1.0 - y) * sz.cy); // Y is inverted (top = 0)
    return Point(px, py);
}

void XYPAD::UpdateParameters() {
    if (connected_param_set) {
        if (!x_param_name.IsEmpty()) {
            double x_param_val = x_param_min + x_value * (x_param_max - x_param_min);
            connected_param_set->SetValue(x_param_name, x_param_val);
        }
        if (!y_param_name.IsEmpty()) {
            double y_param_val = y_param_min + y_value * (y_param_max - y_param_min);
            connected_param_set->SetValue(y_param_name, y_param_val);
        }
    }
}

}