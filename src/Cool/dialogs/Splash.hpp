/*
    SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_dialogs_Splash_h_
#define _Cool_dialogs_Splash_h_

#include <CtrlLib/CtrlLib.h>

NAMESPACE_UPP

class Splash : public TopWindow {
public:
    typedef Splash CLASSNAME;

    Splash();
    virtual ~Splash();

    void ShowProgress(const String& message);
    void SetReady();
    void FadeOut();

    bool HasEventLoop() { return false; }
};

END_UPP_NAMESPACE

#endif
