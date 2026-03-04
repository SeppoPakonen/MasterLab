#include "AudioEditing.h"

CuteCurveSelect::CuteCurveSelect() {}
CuteCurveSelect::~CuteCurveSelect() { Clear(); }
CuteCurveSelect::Item* CuteCurveSelect::FindItem(CuteCurve::Node* node) {
    int index = items.Find((void*)node);
    return index >= 0 ? &items[index] : nullptr;
}
void CuteCurveSelect::AddItem(CuteCurve::Node* node, const Rect& rect_node) {
    Item item;
    item.rect_node = rect_node;
    items.GetAdd((void*)node, item) = item;
    rect = rect.Union(rect_node);
    if(anchor_node == nullptr || anchor_node->frame > node->frame)
        anchor_node = node;
}
void CuteCurveSelect::RemoveItem(CuteCurve::Node* node) {
    int index = items.Find((void*)node);
    if(index >= 0) {
        items.Remove(index);
        Commit();
    }
}
void CuteCurveSelect::SelectItem(CuteCurve* curve, CuteCurve::Node* node, const Rect& rect_node, bool select, bool toggle) {
    Item* item = FindItem(node);
    if(item) {
        unsigned int flags = item->flags;
        if((!select && (flags & 2) == 0) || ((select && (flags & 3) == 3) && toggle))
            item->flags &= ~1u;
        else if((select && (flags & 2) == 0) || ((!select && (flags & 3) == 2) && toggle))
            item->flags |= 1u;
    }
    else if(select) {
        if(this->curve == nullptr)
            this->curve = curve;
        if(this->curve == curve)
            AddItem(node, rect_node);
    }
}
void CuteCurveSelect::Update(bool commit) {
    for(int i = items.GetCount() - 1; i >= 0; --i) {
        Item& item = items[i];
        if(commit) {
            if(item.flags & 1)
                item.flags |= 2;
            else
                item.flags &= ~2u;
        }
        if((item.flags & 3) == 0)
            items.Remove(i);
    }
    Commit();
}
void CuteCurveSelect::Commit() {
    rect = Rect(0, 0, 0, 0);
    anchor_node = nullptr;
    for(int i = 0; i < items.GetCount(); ++i) {
        rect = rect.Union(items[i].rect_node);
        CuteCurve::Node* node = (CuteCurve::Node*)items.GetKey(i);
        if(node && (anchor_node == nullptr || anchor_node->frame > node->frame))
            anchor_node = node;
    }
}
void CuteCurveSelect::Clear() { items.Clear(); rect = Rect(0, 0, 0, 0); curve = nullptr; anchor_node = nullptr; }
void CuteCurveSelect::SetCurve(CuteCurve* curve) { this->curve = curve; }
CuteCurve* CuteCurveSelect::GetCurve() const { return curve; }
CuteCurve::Node* CuteCurveSelect::GetAnchorNode() const { return anchor_node; }
const Rect& CuteCurveSelect::GetRect() const { return rect; }
