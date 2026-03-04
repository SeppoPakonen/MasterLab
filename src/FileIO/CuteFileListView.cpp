#include "FileIO.h"

CuteFileListView::CuteFileListView() {
    Add(list.SizePos());
    list.AddColumn("Name");
    list.AddColumn("Type");
    list.AddColumn("Refs");
}
void CuteFileListView::SetFileList(CuteFileList* file_list) { this->file_list = file_list; RefreshList(); }
CuteFileList* CuteFileListView::GetFileList() const { return file_list; }
void CuteFileListView::RefreshList() {
    list.Clear();
    if(!file_list)
        return;
    for(const CuteFileList::Item& item : file_list->GetItems())
        list.Add(item.name, item.key.type == CuteFileList::Audio ? "Audio" : "Midi", item.refs);
}
