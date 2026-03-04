#ifndef _ProjectWindow_CuteScrollView_h_
#define _ProjectWindow_CuteScrollView_h_

class CuteScrollView : public ParentCtrl {
public:
    typedef CuteScrollView CLASSNAME;

    CuteScrollView();
    virtual ~CuteScrollView();

    int GetContentsX() const;
    int GetContentsY() const;
    int GetContentsWidth() const;
    int GetContentsHeight() const;
    void SetContentsPos(int contents_x, int contents_y);
    void ResizeContents(int contents_width, int contents_height);
    void EnsureVisible(int contents_x, int contents_y, int margin_x = 50, int margin_y = 50);
    Point ViewportToContents(const Point& point) const;
    Point ContentsToViewport(const Point& point) const;

private:
    int contents_x = 0;
    int contents_y = 0;
    int contents_width = 0;
    int contents_height = 0;
};

#endif
