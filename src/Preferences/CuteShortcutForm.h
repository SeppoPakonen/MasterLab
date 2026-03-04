#ifndef _Preferences_CuteShortcutForm_h_
#define _Preferences_CuteShortcutForm_h_

class CuteActionControl;

class CuteShortcutTableItemEdit : public EditString {
public:
    typedef CuteShortcutTableItemEdit CLASSNAME;

    CuteShortcutTableItemEdit();
};

class CuteShortcutTableItemEditor : public ParentCtrl {
public:
    typedef CuteShortcutTableItemEditor CLASSNAME;

    CuteShortcutTableItemEditor();

    void SetText(const String& text);
    String GetText() const;
    void SetIndex(int index);
    int GetIndex() const;
    void SetDefaultText(const String& default_text);
    const String& GetDefaultText() const;
    void Clear();

private:
    CuteShortcutTableItemEdit edit;
    int index = -1;
    String default_text;
};

class CuteShortcutTableItemDelegate {
public:
    CuteShortcutTableItemDelegate();
};

class CuteShortcutForm : public TopWindow {
public:
    typedef CuteShortcutForm CLASSNAME;

    CuteShortcutForm();

    ArrayCtrl& GetTableWidget();
    void SetActionControl(CuteActionControl* action_control);
    CuteActionControl* GetActionControl() const;
    bool IsDirtyActionShortcuts() const;
    bool IsDirtyActionControls() const;
    void CommitEditor();

private:
    ArrayCtrl table_widget;
    CuteActionControl* action_control = nullptr;
    bool dirty_action_shortcuts = false;
    bool dirty_action_controls = false;
};

#endif
