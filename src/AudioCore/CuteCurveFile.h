#ifndef _AudioCore_CuteCurveFile_h_
#define _AudioCore_CuteCurveFile_h_

class CuteCurve;
class CuteCurveList;
class CuteDocument;
class CuteTimeScale;
class CuteSubject;

class CuteCurveFile {
public:
    enum ControlType {
        Controller = 0,
        Rpn = 1,
        Nrpn = 2,
        PitchBend = 3,
        ChannelPressure = 4,
        KeyPressure = 5
    };

    struct Item {
        String name;
        unsigned long index = 0;
        ControlType control_type = Controller;
        unsigned short channel = 0;
        unsigned short param = 0;
        CuteCurve::Mode mode = CuteCurve::Hold;
        bool process = false;
        bool capture = false;
        bool locked = false;
        bool logarithmic = false;
        String color_text;
        CuteSubject* subject = nullptr;
    };

    CuteCurveFile(CuteCurveList* curve_list = nullptr);
    ~CuteCurveFile();

    void SetList(CuteCurveList* curve_list);
    CuteCurveList* GetList() const;

    void SetBaseDir(const String& base_dir);
    const String& GetBaseDir() const;

    void SetFilename(const String& filename);
    const String& GetFilename() const;

    void SetCurrentIndex(unsigned long current_index);
    unsigned long GetCurrentIndex() const;

    const Array<Item>& GetItems() const;
    Item& AddItem();
    void Clear();
    bool IsEmpty() const;

    void Load(const String& serialized_state);
    void Save(CuteDocument* document, String& serialized_state, CuteTimeScale* time_scale) const;
    void Apply(CuteTimeScale* time_scale);

    static CuteCurve::Mode ModeFromText(const String& text);
    static String TextFromMode(CuteCurve::Mode mode);

private:
    CuteCurveList* curve_list = nullptr;
    String base_dir;
    String filename;
    Array<Item> items;
    unsigned long current_index = 0;
};

#endif
