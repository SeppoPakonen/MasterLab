#ifndef _MIDI_CuteMidiFileTempo_h_
#define _MIDI_CuteMidiFileTempo_h_

class CuteMidiFile;
class CuteTimeScale;

class CuteMidiFileTempo {
public:
    class Node : public CuteList<Node>::Link {
    public:
        Node(unsigned long tick = 0, float tempo = 120.0f, unsigned short beats_per_bar = 4, unsigned short beat_divisor = 2);
        void Update(CuteMidiFile* midi_file);
        void Reset(Node* node);
        unsigned short BarFromTick(unsigned long tick) const;
        unsigned long TickFromBar(unsigned short bar) const;
        unsigned long TickSnapToBar(unsigned long tick) const;

        unsigned long tick = 0;
        unsigned short bar = 0;
        float tempo = 120.0f;
        unsigned short beats_per_bar = 4;
        unsigned short beat_divisor = 2;
        unsigned short ticks_per_beat = 960;
    };

    class Marker : public CuteList<Marker>::Link {
    public:
        Marker(unsigned long tick = 0, const String& text = String());
        unsigned long tick = 0;
        String text;
    };

    CuteMidiFileTempo(CuteMidiFile* midi_file = nullptr);
    ~CuteMidiFileTempo();
    void Clear();
    Node* SeekNode(unsigned long tick) const;
    Node* AddNode(unsigned long tick = 0, float tempo = 120.0f, unsigned short beats_per_bar = 4, unsigned short beat_divisor = 2);
    void UpdateNode(Node* node);
    void RemoveNode(Node* node);
    Marker* SeekMarker(unsigned long tick) const;
    Marker* AddMarker(unsigned long tick, const String& text);
    void RemoveMarker(Marker* marker);
    float GetTempo() const;
    unsigned short GetBeatsPerBar() const;
    unsigned short GetBeatDivisor() const;
    unsigned short GetTicksPerBeat() const;

private:
    CuteMidiFile* midi_file = nullptr;
    Array<Node> nodes;
    Array<Marker> markers;
};

#endif
