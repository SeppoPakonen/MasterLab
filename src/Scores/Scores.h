#ifndef _Scores_Scores_h_
#define _Scores_Scores_h_

#include <CtrlLib/CtrlLib.h>
#include <Draw/Draw.h>
#include <Editors/Editors.h>
using namespace Upp;

#include "LayoutEngine.h"
#include "NotationModel.h"
#include "Functions.h"
#include "ScoreProject.h"

// Provide Scores namespace for compatibility with editor modules
namespace Scores {
    using am::NotationModel;
    using am::Note;
    using am::Measure;
}

#endif