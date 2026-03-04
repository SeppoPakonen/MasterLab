#ifndef _Preferences_CutePaletteForm_h_
#define _Preferences_CutePaletteForm_h_

class CutePaletteForm : public TopWindow {
public:
    typedef CutePaletteForm CLASSNAME;

    class PaletteModel : public ArrayCtrl {
    public:
        typedef PaletteModel CLASSNAME;
        PaletteModel();
    };

    class ColorDelegate : public ParentCtrl {
    public:
        typedef ColorDelegate CLASSNAME;
        ColorDelegate();
    };

    class ColorButton : public Button {
    public:
        typedef ColorButton CLASSNAME;
        ColorButton();
    };

    class ColorEditor : public ParentCtrl {
    public:
        typedef ColorEditor CLASSNAME;
        ColorEditor();
    };

    class RoleEditor : public ParentCtrl {
    public:
        typedef RoleEditor CLASSNAME;
        RoleEditor();
    };

    CutePaletteForm();
    void SetPaletteName(const String& palette_name);
    String GetPaletteName() const;
    bool IsDirty() const;

private:
    String palette_name;
    int dirty_count = 0;
    PaletteModel palette_model;
    DropList name_list;
    Button save_button;
    Button delete_button;
};

#endif
