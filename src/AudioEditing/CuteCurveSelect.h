#ifndef _AudioEditing_CuteCurveSelect_h_
#define _AudioEditing_CuteCurveSelect_h_

class CuteCurve;

class CuteCurveSelect {
public:
    struct Item {
        Rect rect_node;
        unsigned int flags = 1;
    };

    CuteCurveSelect();
    ~CuteCurveSelect();

    Item* FindItem(CuteCurve::Node* node);
    void AddItem(CuteCurve::Node* node, const Rect& rect_node);
    void RemoveItem(CuteCurve::Node* node);
    void SelectItem(CuteCurve* curve, CuteCurve::Node* node, const Rect& rect_node, bool select = true, bool toggle = false);
    void Update(bool commit);
    void Commit();
    void Clear();

    void SetCurve(CuteCurve* curve);
    CuteCurve* GetCurve() const;
    CuteCurve::Node* GetAnchorNode() const;
    const Rect& GetRect() const;

private:
    VectorMap<void*, Item> items;
    Rect rect;
    CuteCurve* curve = nullptr;
    CuteCurve::Node* anchor_node = nullptr;
};

#endif
