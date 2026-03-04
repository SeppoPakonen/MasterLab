#ifndef _AudioMaster_CuteMessages_h_
#define _AudioMaster_CuteMessages_h_

class CuteMessages : public TopWindow {
public:
    typedef CuteMessages CLASSNAME;

    CuteMessages();
    void AppendMessage(const String& text);
    void SetMessagesLimit(int messages_limit);
    int GetMessagesLimit() const;
    void Clear();

private:
    RichTextCtrl text;
    int messages_limit = 1000;
};

#endif
