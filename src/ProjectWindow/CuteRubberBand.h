#ifndef _ProjectWindow_CuteRubberBand_h_
#define _ProjectWindow_CuteRubberBand_h_

class CuteRubberBand : public StaticRect {
public:
    typedef CuteRubberBand CLASSNAME;

    class Style {
    public:
        Style(int thickness = 1) : thickness(thickness) {}
        void SetThickness(int thickness) { this->thickness = thickness; }
        int GetThickness() const { return thickness; }

    private:
        int thickness = 1;
    };

    CuteRubberBand();

    void SetThickness(int thickness);
    int GetThickness() const;

private:
    int thickness = 1;
    Style style;
};

#endif
