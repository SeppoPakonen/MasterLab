#ifndef _Cool_Cool_h_
#define _Cool_Cool_h_

#include <Core/Core.h>
#include <Draw/Draw.h>
#include <memory>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <list>
#include <cmath>
#include <utility>
#include <cassert>

// Include MLT types before our shims to avoid redefinitions
#include <framework/mlt_types.h>

// specialization for std::hash<Upp::String> to support std::unordered_map
namespace std {
    template<> struct hash<Upp::String> {
        size_t operator()(const Upp::String& s) const {
            return (size_t)Upp::GetHashValue(s);
        }
    };
}

// Qt/KDE type shims for Stage 2 bring-up
#define Q_OBJECT
#define Q_SLOTS
#define Q_SIGNALS public
#define Q_EMIT
#define QStringLiteral(x) x
#define QLatin1String(x) x
#define QLatin1Char(x) x
#define Q_NAMESPACE
#define QML_ELEMENT
#define Q_ENUM_NS(...)
#define Q_DECLARE_METATYPE(...)
#define Q_PROPERTY(...)
#define Q_INVOKABLE
#define Q_UNUSED(x) (void)x
#define Q_ASSERT(x) ASSERT(x)

namespace Upp {

typedef int64 qint64;
typedef int16 qint16;

typedef String QString;

// QVector/QList wrapper forward decl
template <typename T> class QListWrapper;
typedef QListWrapper<QString> QStringList;

struct QString_ {
    static void remove(QString& s, char c) {
        Upp::String result;
        for(int i = 0; i < s.GetLength(); ++i)
            if(s[i] != c) result.Cat(s[i]);
        s = result;
    }
    static QStringList split(const QString& s, const QString& sep);
};

typedef double qreal;
typedef QString QUrl;
typedef String QByteArray;
template <typename T1, typename T2> using QPair = std::pair<T1, T2>;
template <typename K, typename V> using QMap = Upp::VectorMap<K, V>;

template <typename T> void qRegisterMetaType(const char* = nullptr) {}

struct QUuid : String {
    QUuid() : String("") {}
    QUuid(const String& s) : String(s) {}
    String toString() const { return *this; }
    static QUuid createUuid() { return QUuid("placeholder-uuid"); }
    bool isNull() const { return IsEmpty(); }
};

struct QColor : Color {
    QColor() : Color(Color(0, 0, 0)) {}
    QColor(int r, int g, int b, int a = 255) : Color(Color(r, g, b)) { (void)a; }
    QColor(Color c) : Color(c) {}
    explicit QColor(const QString& s) : Color(Color(0,0,0)) { (void)s; }
    int red() const { return GetR(); }
    int green() const { return GetG(); }
    int blue() const { return GetB(); }
    int alpha() const { return 255; }
    double redF() const { return GetR() / 255.0; }
    double greenF() const { return GetG() / 255.0; }
    double blueF() const { return GetB() / 255.0; }
    void setRgb(int r, int g, int b, int a = 255) { *this = Color(r, g, b); (void)a; }
};

typedef Value QVariant;
typedef uint32 QRgb;
typedef Mutex QReadWriteLock;
typedef Mutex QMutex;

struct QModelIndex {
    int row_index{-1};
    int row() const { return row_index; }
    int column() const { return 0; }
    bool isValid() const { return row_index >= 0; }
    bool operator==(const QModelIndex& other) const { return row_index == other.row_index; }
};

inline int qHash(const QModelIndex& index) { return index.row_index; }

typedef QModelIndex QPersistentModelIndex;

// specialization for std::hash<QPersistentModelIndex>
} // namespace Upp

namespace std {
    template<> struct hash<Upp::QPersistentModelIndex> {
        size_t operator()(const Upp::QPersistentModelIndex& i) const {
            return (size_t)i.row();
        }
    };
}

namespace Upp {

// QVector/QList wrapper
template <typename T> class QListWrapper : public Vector<T> {
public:
    QListWrapper() {}
    QListWrapper(const Vector<T>& v) : Vector<T>(v, 1) {}
    QListWrapper<T>& operator=(const Vector<T>& v) { this->Clear(); for(const auto& x : v) this->Add(x); return *this; }
    int count() const { return this->GetCount(); }
    int length() const { return this->GetCount(); }
    int size() const { return this->GetCount(); }
    const T& at(int i) const { return (*this)[i]; }
    const T& first() const { return (*this)[0]; }
    const T& last() const { return (*this)[this->GetCount() - 1]; }
    QListWrapper<T>& operator<<(const T& t) { this->Add(t); return *this; }
    bool isEmpty() const { return this->IsEmpty(); }
    void clear() { this->Clear(); }
    int indexOf(const T& t) const { return this->Find(t); }
    void removeAt(int i) { this->Remove(i); }
};

template <typename T> using QVector = QListWrapper<T>;
template <typename T> using QList = QListWrapper<T>;
typedef QListWrapper<QModelIndex> QModelIndexList;
typedef QListWrapper<QVariant> QVariantList;

inline QStringList QString_::split(const QString& s, const QString& sep) {
    QStringList res;
    Vector<String> parts = Split(s, (String)sep);
    for(const auto& x : parts) res.Add(x);
    return res;
}

class QObject {
public:
    QObject(QObject* parent = nullptr) { (void)parent; }
    virtual ~QObject();
    static void connect(...) {}
    void blockSignals(bool) {}
};

namespace Qt {
    enum ItemFlag { NoItemFlags = 0, ItemIsSelectable = 1, ItemIsEnabled = 2, ItemIsEditable = 4 };
    typedef int ItemFlags;
    enum Orientation { Horizontal, Vertical };
    enum ItemDataRole { DisplayRole = 0, EditRole = 2, DecorationRole = 3, ToolTipRole = 4, UserRole = 100 };
    enum DropAction { CopyAction, MoveAction };
    typedef int DropActions;
    enum ConnectionType { QueuedConnection, DirectConnection };
}

class QMimeData {};

struct QSize : Size {
    QSize() { cx = cy = 0; }
    QSize(int w, int h) : Size(w, h) {}
    QSize(Size s) : Size(s) {}
    int width() const { return cx; }
    int height() const { return cy; }
    void setWidth(int w) { cx = w; }
    void setHeight(int h) { cy = h; }
    bool isEmpty() const { return cx <= 0 || cy <= 0; }
    bool isNull() const { return cx == 0 && cy == 0; }
};

struct QPoint : Point {
    QPoint() { x = y = 0; }
    QPoint(int x, int y) : Point(x, y) {}
    QPoint(Point p) : Point(p) {}
};

struct QRect : Rect {
    QRect() { left = top = right = bottom = 0; }
    QRect(int x, int y, int w, int h) : Rect(x, y, x + w, y + h) {}
    QRect(Point p, Size s) : Rect(p, s) {}
    int x() const { return left; }
    int y() const { return top; }
    int width() const { return Width(); }
    int height() const { return Height(); }
};

struct QRectF {
    double x() const { return 0; }
    double y() const { return 0; }
    double width() const { return 0; }
    double height() const { return 0; }
};

struct QImage : Image {
    QImage() {}
    explicit QImage(const Size& size) : Image(size) {}
    QImage(Image img) : Image(img) {}
    Size GetSize() const { return Size(*this); }
};

class QUndoCommand {
public:
    explicit QUndoCommand(QUndoCommand *parent = nullptr) { (void)parent; }
    virtual ~QUndoCommand() = default;
    virtual void Undo() {}
    virtual void Redo() {}
    void setText(const String& text) { m_text = text; }
private:
    String m_text;
};

class QAction : public QObject {};
class QTimer : public QObject {
public:
    void setInterval(int) {}
    void setSingleShot(bool) {}
    void start() {}
    void stop() {}
    bool isActive() { return false; }
    static void timeout() {}
    static void singleShot(...) {}
};
class QEventLoop {
public:
    int exec() { return 0; }
    void quit() {}
};

// multiple inheritance shared_ptr helpers
template <typename T> struct enable_shared_from_this_virtual;

class enable_shared_from_this_virtual_base : public std::enable_shared_from_this<enable_shared_from_this_virtual_base>
{
    using base_type = std::enable_shared_from_this<enable_shared_from_this_virtual_base>;
    template <typename T> friend struct enable_shared_from_this_virtual;

public:
    std::shared_ptr<enable_shared_from_this_virtual_base> shared_from_this() { return base_type::shared_from_this(); }
    std::shared_ptr<enable_shared_from_this_virtual_base const> shared_from_this() const { return base_type::shared_from_this(); }
    virtual ~enable_shared_from_this_virtual_base() {}
};

template <typename T> struct enable_shared_from_this_virtual : virtual enable_shared_from_this_virtual_base
{
public:
    std::shared_ptr<T> shared_from_this()
    {
        return std::static_pointer_cast<T>(enable_shared_from_this_virtual_base::shared_from_this());
    }

    std::shared_ptr<T const> shared_from_this() const
    {
        return std::static_pointer_cast<T const>(enable_shared_from_this_virtual_base::shared_from_this());
    }
};

struct QDebug {
    template <typename T> QDebug& operator<<(const T&) { return *this; }
    QDebug& maybeSpace() { return *this; }
};
#define qDebug() QDebug()
#define qWarning() QDebug()
#define qCritical() QDebug()

typedef std::function<bool(void)> Fun;

namespace Mlt {
    class Profile;
    class Playlist;
    class Producer;
    class Tractor;
    class Filter;
    class Transition;
    class Service;
    class Properties;
}

class QThreadPool {
public:
    static QThreadPool* globalInstance() { static QThreadPool p; return &p; }
    void clear() {}
};

class QFileInfo {
public:
    QFileInfo(const QString&) {}
    bool exists() const { return true; }
    String absoluteFilePath() const { return ""; }
};

class QDomElement { public: QString tagName() const { return ""; } };
class QDomDocument {};
typedef String QIcon;

class QIODevice : public QObject {
public:
    QIODevice(QObject* p = nullptr) : QObject(p) {}
    virtual qint64 readData(char*, qint64) { return 0; }
    virtual qint64 writeData(const char*, qint64) { return 0; }
    virtual bool open(int) { return true; }
    virtual void close() {}
    virtual void write(const QByteArray&) {}
    enum OpenMode { WriteOnly };
};

class QFile : public QIODevice {
public:
    QFile(const QString&) {}
    bool exists() const { return true; }
    void remove() {}
};

class QAudioFormat {};
class QAudioDevice {};
class QMediaDevices {
public:
    static QAudioDevice defaultAudioInput() { return QAudioDevice(); }
    static Vector<QAudioDevice> audioInputs() { return Vector<QAudioDevice>(); }
};
class QMediaFormat {};
class QMediaCaptureSession : public QObject {
public:
    QMediaCaptureSession(QObject* p = nullptr) : QObject(p) {}
    void setAudioInput(class QAudioInput*) {}
    void setRecorder(class QMediaRecorder*) {}
};
class QMediaRecorder : public QObject {
public:
    QMediaRecorder(QObject* p = nullptr) : QObject(p) {}
    enum State { RecordingState, StoppedState, PausedState };
    State recorderState() const { return StoppedState; }
    void setAudioSampleRate(int) {}
    void setAudioChannelCount(int) {}
    void setOutputLocation(const QString&) {}
    void setMediaFormat(const QMediaFormat&) {}
    void record() {}
    void stop() {}
    void pause() {}
    static void recorderStateChanged() {}
    static void errorChanged() {}
};
class QAudioSource : public QObject {
public:
    QAudioSource(const QAudioDevice&, const QAudioFormat&, QObject* p = nullptr) : QObject(p) {}
    void setVolume(qreal) {}
    void start(QIODevice*) {}
    void stop() {}
    void reset() {}
};
class QAudioInput : public QObject {
public:
    QAudioInput(const QAudioDevice&, QObject* p = nullptr) : QObject(p) {}
};
class QCamera : public QObject {
public:
    QCamera(QObject* p = nullptr) : QObject(p) {}
};
class QElapsedTimer {
public:
    void invalidate() {}
    void start() {}
    qint64 elapsed() const { return 0; }
};
class QMutexLocker { public: QMutexLocker(Mutex*) {} };

inline qreal IEC_ScaleMax(qreal v, int) { return v; }
#define i18n(x, ...) String(x)
#define i18nc(c, x) String(x)

namespace QAudio {
    enum VolumeScale { LogarithmicVolumeScale, LinearVolumeScale };
    inline qreal convertVolume(qreal v, VolumeScale, VolumeScale) { return v; }
}

inline double qAbs(double v) { return std::abs(v); }
inline double qMax(double a, double b) { return std::max(a, b); }
inline int qRound(double v) { return (int)std::round(v); }

template <typename T> class QScopedPointer {
    T* p;
public:
    QScopedPointer(T* p = nullptr) : p(p) {}
    ~QScopedPointer() { delete p; }
    void reset(T* newP = nullptr) { if(p) delete p; p = newP; }
    T* operator->() const { return p; }
    T* data() const { return p; }
    T* get() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

class AbstractMonitor { public: virtual void stop() {} virtual void start() {} virtual void slotPlay() {} virtual void mute(bool) {} virtual void refreshMonitorIfActive(bool) {} virtual void slotMouseSeek(int, uint) {} virtual void slotSwitchFullScreen(bool) {} virtual void slotForward(double, bool) {} virtual void slotRewind(double) {} };
class QDir {
public:
    QDir(const QString& = "") {}
    bool exists() const { return true; }
    void mkpath(const String&) {}
    String absoluteFilePath(const String& s) const { return s; }
    static QDir temp() { return QDir(); }
    static String separator() { return "/"; }
};

class SharedFrame {};
class KRecentFilesAction {};
typedef VectorMap<QString, QVariant> QVariantMap;
class QDateTime {};

class QWidget { public: QWidget(QWidget* = nullptr) {} virtual ~QWidget() {} void show() {} void setPalette(const class QPalette&) {} };

#define QT_VERSION_CHECK(a,b,c) 0

class KConfigGroup {
public:
    KConfigGroup(...) {}
    bool exists() { return false; }
    QMap<QString, QString> entryMap() { return QMap<QString, QString>(); }
};
class KSharedConfig { public: static int openConfig() { return 0; } };
namespace KMessageBox { enum Action { PrimaryAction }; inline int questionTwoActions(...) { return 0; } }
struct KGuiItem { KGuiItem(...) {} };
namespace KStandardGuiItem { inline int cont() { return 0; } }
namespace QStandardPaths { enum Location { GenericConfigLocation, GenericDataLocation }; inline QString locate(...) { return ""; } }

class QApplication { public: static QWidget* activeWindow() { return nullptr; } static void closeAllWindows() {} static void exit(int) {} };
extern QApplication* qApp;

class QMetaObject {
public:
    enum Connection {};
    static void invokeMethod(...) {}
};

class QImageReader { public: static void setAllocationLimit(int) {} };

class ProfileParam {};

int RunConvertedKdenliveMain(const Vector<String>& args);

} // namespace Upp

#endif
