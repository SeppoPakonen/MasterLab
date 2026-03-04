#ifndef _Tooling_CuteList_h_
#define _Tooling_CuteList_h_

template <class T>
class CuteList {
public:
    struct Link {
        T* prev = nullptr;
        T* next = nullptr;
    };

    CuteList() = default;

    void AddTail(T& item) { items.Add(&item); }
    void Clear() { items.Clear(); }
    int GetCount() const { return items.GetCount(); }
    T* operator[](int index) const { return items[index]; }

private:
    Vector<T*> items;
};

#endif
