#ifndef _Theme_CuteComboBox_h_
#define _Theme_CuteComboBox_h_

class CuteAudioFileTypeDropList : public DropList {
public:
    typedef CuteAudioFileTypeDropList CLASSNAME;
    CuteAudioFileTypeDropList();
    void SetCurrentType(const String& ext, int type);
    int GetCurrentType() const;
    String GetCurrentExt() const;
};

#endif
