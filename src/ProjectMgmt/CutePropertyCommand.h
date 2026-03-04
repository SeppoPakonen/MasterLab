#ifndef _ProjectMgmt_CutePropertyCommand_h_
#define _ProjectMgmt_CutePropertyCommand_h_

template <class T>
class CutePropertyCommand {
public:
    CutePropertyCommand(const String& name, T& reference, const T& value)
        : name(name), reference(reference), before_value(reference), after_value(value) {}

    const String& GetName() const { return name; }
    bool Redo() { reference = after_value; return true; }
    bool Undo() { reference = before_value; return true; }

private:
    String name;
    T& reference;
    T before_value;
    T after_value;
};

#endif
