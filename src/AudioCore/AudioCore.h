#ifndef _MasterLab_AudioCore_h_
#define _MasterLab_AudioCore_h_

#include <Core/Core.h>
#ifdef flagGUI
#include <CtrlLib/CtrlLib.h>
#endif
using namespace Upp;

#include "AudioTypes.h"
#include "AudioBuffer.h"
#include "CuteAudioBuffer.h"
#include "CuteAudioClip.h"
#include "CuteAudioEngine.h"
#include "IIdentified.h"
#include "Clip.h"
#include "Timeline.h"
#include "Transport.h"
#include "Channel.h"
#include "Bus.h"
#include "Mixer.h"
#include "Synth.h"
#include "Project.h"
#include "WavFile.h"

#include "CuteAudioFile.h"
#include "CuteAudioMadFile.h"
#include "CuteAudioMeter.h"
#include "CuteAudioMonitor.h"
#include "CuteAudioPeak.h"
#include "CuteAudioSndFile.h"
#include "CuteAudioVorbisFile.h"
#include "CuteClip.h"
#include "CuteCurve.h"
#include "CuteCurveFile.h"
#include "CuteEngine.h"
#include "CuteMonitor.h"
#include "CuteSession.h"
#include "CuteSessionCursor.h"
#ifdef flagGUI
#include "CuteSessionForm.h"
#endif
#include "CuteMixer.h"
#endif
