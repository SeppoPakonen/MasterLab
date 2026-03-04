#ifndef _FileIO_CuteFileListView_h_
#define _FileIO_CuteFileListView_h_

class CuteDocument;
class CuteFileList;

class CuteFileListView : public ParentCtrl {
public:
    typedef CuteFileListView CLASSNAME;

    enum ItemType { GroupItem = 1001, FileItem = 1002, ChannelItem = 1003 };

    CuteFileListView();

    void SetFileList(CuteFileList* file_list);
    CuteFileList* GetFileList() const;
    void RefreshList();

private:
    ArrayCtrl list;
    CuteFileList* file_list = nullptr;
};

#endif
