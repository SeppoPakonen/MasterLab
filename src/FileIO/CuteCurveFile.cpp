#include "FileIO.h"

namespace am {
namespace FileIO {

bool CuteCurveFile::Load(const String& path) {
    FileIn in(path);
    if (!in)
        return false;

    int current_index = -1;
    while (!in.IsEof()) {
        String line = in.GetLine();
        if (line.StartsWith("point")) {
            current_index = ScanInt(line.Mid(5));
            if (current_index >= 0)
                points.At(current_index);
        }
        else if (line.StartsWith("index=")) {
            if (current_index >= 0)
                points[current_index].index = ScanInt(line.Mid(6));
        }
        else if (line.StartsWith("time=")) {
            if (current_index >= 0)
                points[current_index].time = ScanInt64(line.Mid(5));
        }
        else if (line.StartsWith("value=")) {
            if (current_index >= 0)
                points[current_index].value = ScanFloat(line.Mid(6));
        }
        else if (line.StartsWith("shape=")) {
            if (current_index >= 0) {
                String shape_text = line.Mid(6);
                if (ToLower(shape_text) == "linear")
                    points[current_index].shape = CuteCurve::Linear;
                else if (ToLower(shape_text) == "spline")
                    points[current_index].shape = CuteCurve::Spline;
            }
        }
    }
    return true;
}

bool CuteCurveFile::Save(const String& path) {
    FileOut out(path);
    if (!out)
        return false;

    for (int i = 0; i < points.GetCount(); i++) {
        out.PutLine(Format("point%d", i));
        out.PutLine(Format("index=%d", points[i].index));
        out.PutLine(Format("time=%d", points[i].time));
        out.PutLine(Format("value=%f", points[i].value));
        String shape_text;
        if (points[i].shape == CuteCurve::Linear)
            shape_text = "Linear";
        else if (points[i].shape == CuteCurve::Spline)
            shape_text = "Spline";
        out.PutLine(Format("shape=%s", shape_text));
    }
    return true;
}

} // namespace FileIO
} // namespace am
