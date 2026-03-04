#ifndef _VSTHost_CuteLv2Gtk2Plugin_h_
#define _VSTHost_CuteLv2Gtk2Plugin_h_

class CuteLv2Gtk2Plugin {
public:
    CuteLv2Gtk2Plugin();
    bool Open();
    void Close();
    bool HasGtk2Editor() const;
private:
    bool gtk2_editor = false;
};

#endif
