#ifndef _CuteCLI_CuteCLI_h_
#define _CuteCLI_CuteCLI_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

struct CuteCli {
	int Run(const Vector<String>& args);

private:
	int ShowHelp() const;
	int CmdCreateProject(const Vector<String>& args) const;
	int CmdTestMidiNotes(const Vector<String>& args) const;
	int CmdRenderWav(const Vector<String>& args) const;
	int CmdSmoke(const Vector<String>& args) const;
};

#endif
