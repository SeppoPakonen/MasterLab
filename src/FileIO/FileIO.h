#ifndef _FileIO_FileIO_h_
#define _FileIO_FileIO_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h> // For FileSel
#include <AudioCore/AudioCore.h>
using namespace Upp;

// Core File IO classes
#include "CuteDocument.h"
#include "MediaFormatRegistry.h"
#include "RecentFiles.h"
#include "Import.h"
#include "Export.h"
#include "CuteFileList.h"
#include "CuteZipFile.h"
#include "Backup.h"
#include "Templates.h"

#ifdef flagGUI
// GUI-dependent File IO classes
#include "CuteFileListView.h"
#include "CuteFileSystem.h"
#include "CuteFiles.h"
#endif

namespace am {
namespace FileIO {

class CuteTrack;

class CuteTrackClip {
public:
	CuteTrackClip();
	~CuteTrackClip();

	void SetTrack(CuteTrack* track);
	CuteTrack* GetTrack() const;
	void SetName(const String& name);
	const String& GetName() const;
	void SetClipStart(unsigned long clip_start);
	unsigned long GetClipStart() const;
	void SetClipLength(unsigned long clip_length);
	unsigned long GetClipLength() const;
	void SetClipSelected(bool clip_selected);
	bool IsClipSelected() const;

private:
	CuteTrack* track = nullptr;
	String name;
	unsigned long clip_start = 0;
	unsigned long clip_length = 0;
	bool clip_selected = false;
};

class CuteCurveFile {
public:
	struct Point {
		int index = 0;
		int64 time = 0;
		double value = 0.0;
		CuteCurve::Mode shape = CuteCurve::Linear;
	};

	bool Load(const String& path);
	bool Save(const String& path);

private:
	Vector<Point> points;
};

// Global functions/classes not GUI-dependent
// ...

} // namespace FileIO
} // namespace am

#endif
