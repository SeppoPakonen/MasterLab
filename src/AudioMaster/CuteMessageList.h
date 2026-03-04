#ifndef _AudioMaster_CuteMessageList_h_
#define _AudioMaster_CuteMessageList_h_

class CuteMessageList {
public:
    CuteMessageList();
    ~CuteMessageList();

    static void Append(const String& text);
    static bool IsEmpty();
    static Vector<String> GetItems();
    static void Clear();

private:
    Vector<String> items;
    static CuteMessageList* instance;
};

#endif
