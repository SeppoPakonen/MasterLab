/*
    SPDX-FileCopyrightText: 2010 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_widgets_TimecodeDisplay_h_
#define _Cool_widgets_TimecodeDisplay_h_

#include <CtrlLib/CtrlLib.h>
#include "../utils/Gentime.h"
#include "../utils/Timecode.h"

NAMESPACE_UPP

/** @class TimecodeDisplay
    @brief A widget for inserting a timecode value.
 */
class TimecodeDisplay : public EditField {
public:
    typedef TimecodeDisplay CLASSNAME;

    explicit TimecodeDisplay(bool auto_adjust = true);
    explicit TimecodeDisplay(const Timecode& t);
    virtual ~TimecodeDisplay();

    // Range management
    void SetRange(int min, int max);
    int  GetMinimum() const { return min_value; }
    int  GetMaximum() const { return max_value; }

    // Value access
    int     GetValue() const { return value; }
    GenTime GetGentime() const;
    void    SetValue(int v);
    void    SetValue(const String& s);
    void    SetValue(const GenTime& v);

    // Format management
    void SetTimeCodeFormat(bool frames, bool force = false);
    void UpdateTimeCode(const Timecode& t);
    
    // UI state
    void SetBold(bool bold);

    // Callbacks replacing Qt Signals
    Callback1<int> WhenEditingFinished;
    Callback       WhenUpdated;

protected:
    virtual void LeftDown(Point p, dword flags) override;
    virtual void MouseMove(Point p, dword flags) override;
    virtual void LeftUp(Point p, dword flags) override;
    virtual void MouseWheel(Point p, int zdelta, dword flags) override;
    virtual bool Key(dword key, int count) override;

private:
    Timecode timecode;
    bool     is_frames_format = false;
    
    int min_value = 0;
    int max_value = -1;
    int value = 0;
    int offset = 0;
    
    Pointf start_drag_pos;
    bool   is_dragging = false;
    
    void Initialize();
    void RefreshDisplay();
    void OnEditingFinished();
};

END_UPP_NAMESPACE

#endif
