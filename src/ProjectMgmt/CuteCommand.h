#ifndef _ProjectMgmt_CuteCommand_h_
#define _ProjectMgmt_CuteCommand_h_

class CuteCommand {
public:
    enum Flag {
        None = 0,
        AutoDelete = 1,
        Refresh = 2,
        Clear = 4,
        Select = 8,
        Reset = 16,
        ClearSelect = Clear | Select,
        ClearSelectReset = ClearSelect | Reset,
    };

    CuteCommand(const String& name);
    virtual ~CuteCommand();
    void SetName(const String& name);
    const String& GetName() const;
    unsigned int GetFlags() const;
    void SetAutoDelete(bool auto_delete);
    bool IsAutoDelete() const;
    void SetRefresh(bool refresh);
    bool IsRefresh() const;
    void SetClearSelect(bool clear_select);
    bool IsClearSelect() const;
    void SetClearSelectReset(bool clear_select_reset);
    bool IsClearSelectReset() const;
    virtual bool Redo() = 0;
    virtual bool Undo() = 0;

protected:
    void SetFlags(unsigned int flags, bool is_on = true);
    bool IsFlags(unsigned int flags) const;

private:
    String name;
    unsigned int flags = Refresh;
};

class CuteCommandList {
public:
    CuteCommandList();
    ~CuteCommandList();
    void Clear();
    CuteCommand* GetLastCommand() const;
    CuteCommand* GetNextCommand() const;
    void RemoveLastCommand();
    void Backout(CuteCommand* command);
    bool Push(CuteCommand* command);
    bool Execute(CuteCommand* command);
    bool Undo();
    bool Redo();

private:
    Array<CuteCommand> commands;
    CuteCommand* last_command = nullptr;
};

#endif
