#ifndef _FileIO_FileIO_h_
#define _FileIO_FileIO_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h> // For FileSel

// Core File IO classes
#include "CuteDocument.h"
#include "MediaFormatRegistry.h"
#include "RecentFiles.h"
#include "Import.h"
#include "Export.h"
#include "CuteFileList.h"
#include "CuteZipFile.h"

#ifdef GUI
// GUI-dependent File IO classes
#include "CuteFileListView.h"
#include "CuteFileSystem.h"
#include "CuteFiles.h"
#endif

namespace am {
namespace FileIO {

// Global functions/classes not GUI-dependent
// ...

} // namespace FileIO
} // namespace am

#endif
