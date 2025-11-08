#include "XYPad.h"

namespace UI {

XYPad::XYPad() : parameterSet(nullptr), sensitivity(1.0, 1.0), isDragging(false) {
    // Initialize the XY pad
    position.x = 0.5;
    position.y = 0.5;
    AddFrame(BlackFrame());
}

XYPad::~XYPad() {
    // Clean up
}

void XYPad::SetParameterIds(const AudioFX::ParameterId& xId, const AudioFX::ParameterId& yId) {
    paramX = xId;
    paramY = yId;
    UpdateFromParameters();
}

void XYPad::SetPosition(double x, double y) {
    position.x = max(0.0, min(1.0, x));
    position.y = max(0.0, min(1.0, y));
    UpdateParameters();
    Refresh();
}

Point<double> XYPad::GetPosition() const {
    return position;
}

void XYPad::SetParameterSet(AudioFX::ParameterSet* params) {
    parameterSet = params;
    UpdateFromParameters();
}

ValueMap XYPad::GetParameterValues() const {
    ValueMap values;
    if (parameterSet) {
        if (!paramX.IsEmpty()) values.Set("x_param", parameterSet->Get(paramX));
        if (!paramY.IsEmpty()) values.Set("y_param", parameterSet->Get(paramY));
    }
    return values;
}

void XYPad::SetSensitivity(double xSens, double ySens) {
    sensitivity.x = max(0.1, min(2.0, xSens));
    sensitivity.y = max(0.1, min(2.0, ySens));
}

void XYPad::Refresh() {
    Refresh();
}

void XYPad::UpdateParameters() {
    if (parameterSet) {
        if (!paramX.IsEmpty()) {
            double minVal = parameterSet->GetMin(paramX);
            double maxVal = parameterSet->GetMax(paramX);
            double val = minVal + position.x * (maxVal - minVal);
            parameterSet->Set(paramX, val);
        }
        
        if (!paramY.IsEmpty()) {
            double minVal = parameterSet->GetMin(paramY);
            double maxVal = parameterSet->GetMax(paramY);
            double val = minVal + position.y * (maxVal - minVal);
            parameterSet->Set(paramY, val);
        }
    }
}

void XYPad::UpdateFromParameters() {
    if (parameterSet) {
        if (!paramX.IsEmpty()) {
            double minVal = parameterSet->GetMin(paramX);
            double maxVal = parameterSet->GetMax(paramX);
            if (maxVal != minVal) {
                position.x = (parameterSet->Get(paramX) - minVal) / (maxVal - minVal);
            }
        }
        
        if (!paramY.IsEmpty()) {
            double minVal = parameterSet->GetMin(paramY);
            double maxVal = parameterSet->GetMax(paramY);
            if (maxVal != minVal) {
                position.y = (parameterSet->Get(paramY) - minVal) / (maxVal - minVal);
            }
        }
    }
}

void XYPad::Paint(Draw& draw) {
    Rect r = GetSize();
    
    // Draw background
    draw.DrawRect(r, SColorFace());
    
    // Draw grid
    for (int i = 1; i < 10; i++) {
        int x = r.left + (i * r.Width()) / 10;
        int y = r.top + (i * r.Height()) / 10;
        draw.DrawLine(x, r.top, x, r.bottom, 1, Gray());
        draw.DrawLine(r.left, y, r.right, y, 1, Gray());
    }
    
    // Draw crosshair
    draw.DrawLine(r.left, r.top + r.Height()/2, r.right, r.top + r.Height()/2, 1, Gray());
    draw.DrawLine(r.left + r.Width()/2, r.top, r.left + r.Width()/2, r.bottom, 1, Gray());
    
    // Draw handle
    DrawHandle(draw);
}

void XYPad::DrawHandle(Draw& draw) {
    Rect r = GetSize();
    int handleSize = 10;
    
    int x = r.left + (int)(position.x * r.Width()) - handleSize/2;
    int y = r.top + (int)(position.y * r.Height()) - handleSize/2;
    
    Rect handleRect = RectC(x, y, handleSize, handleSize);
    draw.DrawRect(handleRect, Red());
    draw.DrawRect(handleRect.Inflated(1), Black());
}

void XYPad::LeftDown(Point p, dword keyflags) {
    isDragging = true;
    Point relativePos = p - GetSize().TopLeft();
    Size size = GetSize().Size();
    
    if (size.cx > 0 && size.cy > 0) {
        position.x = max(0.0, min(1.0, relativePos.x / (double)size.cx));
        position.y = max(0.0, min(1.0, relativePos.y / (double)size.cy));
        UpdateParameters();
        Refresh();
    }
    
    SetCapture();
    Refresh();
}

void XYPad::LeftUp(Point p, dword keyflags) {
    isDragging = false;
    Refresh();
    ReleaseCapture();
}

void XYPad::MouseMove(Point p, dword keyflags) {
    if (isDragging) {
        Point relativePos = p - GetSize().TopLeft();
        Size size = GetSize().Size();
        
        if (size.cx > 0 && size.cy > 0) {
            position.x = max(0.0, min(1.0, relativePos.x / (double)size.cx));
            position.y = max(0.0, min(1.0, relativePos.y / (double)size.cy));
            UpdateParameters();
            Refresh();
        }
    }
}

void XYPad::Layout() {
    Refresh();
}

} // namespace UI