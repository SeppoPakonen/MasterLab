#ifndef _FileIO_CuteZipFile_h_
#define _FileIO_CuteZipFile_h_

class CuteZipFile {
public:
    CuteZipFile();

    bool Open(const String& path, bool write_mode);
    void Close();
    bool IsOpen() const;
    bool AddEntry(const String& name, const String& content);
    bool ExtractEntry(const String& name, String& content) const;
    Vector<String> GetEntryNames() const;

private:
    String path;
    bool write_mode = false;
    bool is_open = false;
    VectorMap<String, String> entries;
};

#endif
