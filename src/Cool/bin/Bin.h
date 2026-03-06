/*
SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_Bin_h_
#define _Cool_Bin_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"
#include "../utils/Timecode.h"

NAMESPACE_UPP

// Forward declarations
class AbstractProjectItem;
class ProjectItemModel;
class ProjectClip;
class CoolDoc;
class Monitor;

// Custom TreeView for Bin
class BinTreeCtrl : public TreeCtrl {
public:
	typedef BinTreeCtrl CLASSNAME;
	BinTreeCtrl();
	
	virtual void LeftDown(Point p, dword flags) override;
	virtual void RightDown(Point p, dword flags) override;
	virtual void DragAndDrop(Point p, PasteClip& d) override;
};

class Bin : public ParentCtrl {
public:
	typedef Bin CLASSNAME;

	enum ViewType { TREE_VIEW, ICON_VIEW, UNKNOWN_VIEW };

	Bin();
	virtual ~Bin();

	// Initialization
	const String SetDocument(CoolDoc* project, const String& id = "");
	void CleanDocument();

	// Clip management
	void CreateClip(const XmlElement& xml);
	std::shared_ptr<ProjectClip> GetBinClip(const String& id);
	
	// Accessors
	size_t GetClipDuration(int item_id) const;
	Size   GetFrameSize(int item_id) const;
	
	// UI Actions
	void RefreshClip(const String& id);
	void ReloadClip(const String& id);
	void SelectClipById(const String& id, int frame = -1, Point zone = Point(-1, -1), bool activate_monitor = true);
	
	// State
	bool IsLoading() const { return is_loading; }
	bool IsMainBin() const { return is_main_bin; }

protected:
	virtual void Layout() override;
	virtual void Paint(Draw& draw) override;

private:
	bool is_loading = false;
	bool is_main_bin = true;
	ViewType view_type = TREE_VIEW;

	std::shared_ptr<ProjectItemModel> item_model;
	BinTreeCtrl tree_view;
	
	// UI Components
	ToolBar tool_bar;
	EditField search_line;
	
	// Internal logic
	void SetupMenu();
	void SetupToolbar(Bar& bar);
	void OnSearch();
};

END_UPP_NAMESPACE

#endif
