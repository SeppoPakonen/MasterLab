#ifndef _FileIO_CuteFileSystem_h_
#define _FileIO_CuteFileSystem_h_

class CuteFileSystem : public TopWindow {
public:
    typedef CuteFileSystem CLASSNAME;

    enum Flags {
        None = 0,
        AutoRefresh = 1,
        ShowHidden = 2,
        SessionRoot = 4
    };

    CuteFileSystem();

    void SetRootPath(const String& root_path);
    const String& GetRootPath() const;
    void SetFlags(int flags);
    int GetFlags() const;
    void RefreshTree();

private:
    TreeCtrl tree;
    String root_path;
    int flags = AutoRefresh;
};

#endif
