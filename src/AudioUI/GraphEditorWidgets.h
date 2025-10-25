#pragma once
#include <CtrlLib/CtrlLib.h>
#include "../AudioGraph/Node.h"
#include "../AudioGraph/Edge.h"
namespace am::ui {
using namespace Upp;
struct NodeWidget : Ctrl { Node* node = nullptr; };
struct EdgeWidget : Ctrl { Edge* edge = nullptr; };
}