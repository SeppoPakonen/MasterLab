#include "FileIO.h"

CuteFileSystem::CuteFileSystem() {
    Title("Cute File System");
    Add(tree.SizePos());
}
void CuteFileSystem::SetRootPath(const String& root_path) { this->root_path = root_path; RefreshTree(); }
const String& CuteFileSystem::GetRootPath() const { return root_path; }
void CuteFileSystem::SetFlags(int flags) { this->flags = flags; }
int CuteFileSystem::GetFlags() const { return flags; }
void CuteFileSystem::RefreshTree() {
    tree.Clear();
    if(root_path.IsEmpty())
        return;
    tree.Add(Null, root_path);
}
