#ifndef _MIDI_CuteMidiControl_h_
#define _MIDI_CuteMidiControl_h_

class CuteTrack;
class CuteDocument;
class CuteMidiControlObserver;

class CuteMidiControl {
public:
    typedef CuteMidiEvent::EventType ControlType;

    enum Command {
        None = 0,
        TrackGain,
        TrackPan,
        TrackMute,
        TrackSolo,
        TrackRecord,
        TransportPlay,
        TransportStop
    };

    enum { TrackParam = 0x4000, TrackParamMask = 0x3fff };

    struct MapKey : Moveable<MapKey> {
        ControlType control_type = CuteMidiEvent::Controller;
        unsigned short channel = 0;
        unsigned short param = 0;
        bool operator==(const MapKey& other) const;
        unsigned GetHashValue() const;
    };

    struct MapVal {
        Command command = None;
        int track_param = 0;
        bool logarithmic = false;
        bool inverted = false;
        bool bipolar = false;
    };

    class Controller {
    public:
        enum Flags { Feedback = 1, Delta = 2 };

        void SetName(const String& name);
        const String& GetName() const;
        void SetFlags(int flags);
        int GetFlags() const;
    private:
        String name;
        int flags = 0;
    };

    CuteMidiControl();

    void MapControl(const MapKey& key, const MapVal& value);
    bool UnmapControl(const MapKey& key);
    const VectorMap<MapKey, MapVal>& GetControlMap() const;

    void AddObserver(CuteMidiControlObserver* observer);
    void RemoveObserver(CuteMidiControlObserver* observer);
    const Vector<CuteMidiControlObserver*>& GetObservers() const;

private:
    VectorMap<MapKey, MapVal> control_map;
    Vector<CuteMidiControlObserver*> observers;
};

#endif
