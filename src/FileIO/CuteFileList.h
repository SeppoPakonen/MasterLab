#ifndef _FileIO_CuteFileList_h_
#define _FileIO_CuteFileList_h_

class CuteClip;

class CuteFileList {
public:
    enum Type { Audio = 0, Midi = 1 };

    struct Key : Moveable<Key> {
        String path;
        int channel = -1;
        Type type = Audio;
        bool operator==(const Key& other) const { return path == other.path && channel == other.channel && type == other.type; }
        unsigned GetHashValue() const { return CombineHash(path, channel, (int)type); }
    };

    struct Item {
        Key key;
        String name;
        int clips = 0;
        int refs = 0;
        bool auto_remove = false;
    };

    CuteFileList();
    ~CuteFileList();

    Item& AddFile(const Key& key, const String& name);
    Item* FindFile(const Key& key);
    void RemoveFile(const Key& key);
    void Clear();
    const Array<Item>& GetItems() const;

private:
    Array<Item> items;
};

#endif
