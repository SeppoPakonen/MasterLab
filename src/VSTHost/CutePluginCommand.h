#ifndef _VSTHost_CutePluginCommand_h_
#define _VSTHost_CutePluginCommand_h_

class CutePlugin;
class CutePluginList;

class CutePluginCommand {
public:
    CutePluginCommand(const String& name, CutePluginList* plugin_list);
    virtual ~CutePluginCommand();

    const String& GetName() const;
    CutePluginList* GetPluginList() const;
    virtual bool Redo();
    virtual bool Undo();

protected:
    void AddPlugin(CutePlugin* plugin);
    Vector<CutePlugin*>& GetPlugins();

private:
    String name;
    CutePluginList* plugin_list = nullptr;
    Vector<CutePlugin*> plugins;
};

class CuteAddPluginCommand : public CutePluginCommand {
public:
    CuteAddPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin);
    bool Redo() override;
    bool Undo() override;
};

class CuteAddInsertPluginCommand : public CutePluginCommand {
public:
    CuteAddInsertPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin);
    bool Redo() override;
    bool Undo() override;
};

class CuteAddAuxSendPluginCommand : public CutePluginCommand {
public:
    CuteAddAuxSendPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin);
    bool Redo() override;
    bool Undo() override;
};

class CuteAddMidiControlPluginCommand : public CutePluginCommand {
public:
    CuteAddMidiControlPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin);
    bool Redo() override;
    bool Undo() override;
};

class CuteAuxSendPluginCommand : public CutePluginCommand {
public:
    CuteAuxSendPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin, const String& bus_name);
    bool Redo() override;
    bool Undo() override;

private:
    String bus_name;
};

class CuteAuxSendIOMatrixCommand : public CutePluginCommand {
public:
    CuteAuxSendIOMatrixCommand(CutePluginList* plugin_list, CutePlugin* plugin, const String& matrix_text);
    bool Redo() override;
    bool Undo() override;

private:
    String matrix_text;
};

class CuteRemovePluginCommand : public CutePluginCommand {
public:
    CuteRemovePluginCommand(CutePluginList* plugin_list, int plugin_index);
    bool Redo() override;
    bool Undo() override;

private:
    int plugin_index = -1;
};

class CuteInsertPluginCommand : public CutePluginCommand {
public:
    CuteInsertPluginCommand(const String& name, CutePluginList* plugin_list, CutePlugin* plugin, int insert_index);
    bool Redo() override;
    bool Undo() override;

private:
    int insert_index = -1;
};

class CuteMovePluginCommand : public CutePluginCommand {
public:
    CuteMovePluginCommand(CutePluginList* plugin_list, int from_index, int to_index);
    bool Redo() override;
    bool Undo() override;

private:
    int from_index = -1;
    int to_index = -1;
};

#endif
