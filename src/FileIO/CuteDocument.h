#ifndef _FileIO_CuteDocument_h_
#define _FileIO_CuteDocument_h_

class CuteDocument {
public:
    enum Flags {
        Default = 0,
        Template = 1,
        Archive = 2,
        SymLink = 4,
        Temporary = 8
    };

    CuteDocument(const String& tag_name = String(), Flags flags = Default);
    virtual ~CuteDocument();

    const String& GetTagName() const;
    void SaveTextElement(const String& tag_name, const String& text, String& out) const;

    bool IsTemplate() const;
    bool IsArchive() const;
    bool IsTemporary() const;
    bool IsSymLink() const;

    String AddFile(const String& filename);
    bool Load(const String& filename, Flags flags = Default);
    bool Save(const String& filename, Flags flags = Default);

    static bool BoolFromText(const String& text);
    static String TextFromBool(bool value);

    static void SetDefaultExt(const String& default_ext);
    static void SetTemplateExt(const String& template_ext);
    static void SetArchiveExt(const String& archive_ext);

    static const String& DefaultExt();
    static const String& TemplateExt();
    static const String& ArchiveExt();

    static const Vector<String>& ExtractedArchives();
    static void ClearExtractedArchives(bool remove = false);
    static String AddFile(const String& dir, const String& filename);

protected:
    void SetFlags(Flags flags);
    Flags GetFlags() const;

    virtual bool LoadElement(const String& serialized_state) = 0;
    virtual bool SaveElement(String& serialized_state) = 0;

private:
    String tag_name;
    Flags flags = Default;
    String name;
    Vector<String> temp_files;

    static String default_ext;
    static String template_ext;
    static String archive_ext;
    static Vector<String> extracted_archives;
    static CuteDocument* current_document;
};

#endif
