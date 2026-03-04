#include "FileIO.h"

CuteFiles::CuteFiles() {
    Title("Cute Files");
    Add(tabs.SizePos());
    tabs.Add(audio_list_view.SizePos(), "Audio");
    tabs.Add(midi_list_view.SizePos(), "Midi");
}
CuteFileListView& CuteFiles::GetAudioListView() { return audio_list_view; }
CuteFileListView& CuteFiles::GetMidiListView() { return midi_list_view; }
void CuteFiles::SetCurrentPage(PageIndex page) { current_page = page; tabs.Set(page); }
CuteFiles::PageIndex CuteFiles::GetCurrentPage() const { return current_page; }
