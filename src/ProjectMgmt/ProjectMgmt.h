#ifndef _ProjectMgmt_ProjectMgmt_h_
#define _ProjectMgmt_ProjectMgmt_h_

#include <Core/Core.h>
#ifdef flagGUI
#include <CtrlCore/CtrlCore.h>
#include <CtrlLib/CtrlLib.h>
#endif
#include <Draw/Draw.h>
#include <AudioCore/AudioCore.h>
using namespace Upp;

#include "Commands.h"
#include "History.h"
#include "Selection.h"
#include "CuteCurveCommand.h"
#include "CuteClipCommand.h"
#include "CuteCommand.h"
#include "CuteEngineCommand.h"

// Provide ProjectMgmt namespace for compatibility with editor modules
namespace ProjectMgmt {
    using am::CommandManager;
    using am::CommandContext;
    using am::CommandFunction;
}

#endif
