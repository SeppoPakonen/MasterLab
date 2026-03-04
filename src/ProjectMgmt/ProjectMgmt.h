#ifndef _ProjectMgmt_ProjectMgmt_h_
#define _ProjectMgmt_ProjectMgmt_h_

#include <Core/Core.h>
#ifdef GUI
#include <CtrlCore/CtrlCore.h>
#include <CtrlLib/CtrlLib.h>
#endif
#include <Draw/Draw.h>
#include <AudioCore/AudioCore.h>
using namespace Upp;

#include "Commands.h"
#include "History.h"
#include "Selection.h"

// Provide ProjectMgmt namespace for compatibility with editor modules
namespace ProjectMgmt {
    using am::CommandManager;
    using am::CommandContext;
    using am::CommandFunction;
}

#endif