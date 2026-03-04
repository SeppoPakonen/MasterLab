#ifndef _AudioCore_CuteCurve_h_
#define _AudioCore_CuteCurve_h_

class CuteCurveList;
class CuteCurveEditList;
class CuteSubject;

class CuteCurve {
public:
    enum Mode { Hold = 0, Linear = 1, Spline = 2 };
    enum State { Idle = 0, Process = 1, Capture = 2, Locked = 4 };

    struct Node {
        unsigned long frame = 0;
        float value = 0.0f;
        float a = 0.0f;
        float b = 0.0f;
        float c = 0.0f;
        float d = 0.0f;
    };

    class Cursor {
    public:
        Cursor(CuteCurve* curve = nullptr);
        Node* Seek(unsigned long frame);
        void Reset(Node* node = nullptr);
        float Value(unsigned long frame);
        float Scale(unsigned long frame);

    private:
        CuteCurve* curve = nullptr;
        int node_index = -1;
        unsigned long frame = 0;
    };

    CuteCurve(CuteCurveList* list = nullptr, CuteSubject* subject = nullptr, Mode mode = Hold, unsigned int min_frame_dist = 3200);
    ~CuteCurve();
    void SetList(CuteCurveList* list);
    CuteCurveList* GetList() const;
    void SetMode(Mode mode);
    Mode GetMode() const;
    void SetMinFrameDist(unsigned int min_frame_dist);
    unsigned int GetMinFrameDist() const;
    const Vector<Node>& GetNodes() const;
    void Clear();
    Node* AddNode(unsigned long frame, float value, CuteCurveEditList* edit_list = nullptr);
    void InsertNode(const Node& node);
    void RemoveNode(int index);
    float Value(const Node* node, unsigned long frame) const;
    float Value(unsigned long frame);
    float ValueFromScale(float scale) const;
    float ScaleFromValue(float value) const;
    void SetDefaultValue(float default_value);
    float GetDefaultValue() const;
    void SetLength(unsigned long length);
    unsigned long GetLength() const;
    void Update();
    Cursor& GetCursor();
    void SetCapture(bool capture);
    void SetProcess(bool process);
    void SetLocked(bool locked);
    bool IsIdle() const;
    bool IsProcess() const;
    bool IsCapture() const;
    bool IsLocked() const;
    void ProcessFrame(unsigned long frame);
    void CaptureFrame(unsigned long frame);

private:
    CuteCurveList* list = nullptr;
    CuteSubject* subject = nullptr;
    Mode mode = Hold;
    State state = Idle;
    unsigned int min_frame_dist = 3200;
    Vector<Node> nodes;
    Cursor cursor;
    float default_value = 0.0f;
    unsigned long length = 0;
};

#endif
