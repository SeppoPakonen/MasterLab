#include "Theme.h"
#include <AudioCore/AudioCore.h>

CuteAudioFileTypeDropList::CuteAudioFileTypeDropList() {
    const auto& formats = CuteAudioFileFactory::GetFormats();
    for(int i = 0; i < formats.GetCount(); i++)
        if(formats[i].type != CuteAudioFileFactory::MadFile)
            Add(i, formats[i].name);
}
void CuteAudioFileTypeDropList::SetCurrentType(const String& ext, int type) { (void)ext; SetIndex(type); }
int CuteAudioFileTypeDropList::GetCurrentType() const { return GetIndex(); }
String CuteAudioFileTypeDropList::GetCurrentExt() const { return GetIndex() >= 0 ? CuteAudioFileFactory::GetExtensions()[GetIndex()] : String(); }
