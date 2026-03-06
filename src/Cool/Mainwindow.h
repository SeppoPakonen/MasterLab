/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_MainWindow_h_
#define _Cool_MainWindow_h_

#include <CtrlLib/CtrlLib.h>
#include "Definitions.h"
#include "utils/Gentime.h"

NAMESPACE_UPP

// Forward declarations
class AssetPanel;
class AudioGraphSpectrum;
class EffectBasket;
class EffectListWidget;
class TransitionListWidget;
class Monitor;
class RenderWidget;
class ScopeManager;
class TimelineTabs;
class TimelineWidget;
class Bin;
class StatusBarMessageLabel;

class MainWindow : public TopWindow {
public:
	typedef MainWindow CLASSNAME;

	MainWindow();
	virtual ~MainWindow();

	void Init();

	// Global caches
	static VectorMap<String, Image> luma_cache;
	static VectorMap<String, Vector<String>> luma_files;

	// UI Component accessors
	TimelineWidget* GetCurrentTimeline() const;
	Bin*            GetBin();
	Bin*            ActiveBin();
	
	// Command management
	void AddAction(const String& name, const String& text, const Image& icon = Image(), dword key = 0);
	
	// View management
	void RaiseMonitor(bool clip_monitor, bool raise = false);
	void RaiseBin(bool unconditionally = true);
	void FocusTimeline();
	
	// Bin management
	void AddBin(Bin* bin, const String& bin_name = "", bool update_count = true);
	void CleanBins();
	
	// Status messaging
	void DisplayMessage(const String& message, int message_type, int timeout = -1);
	void DisplaySelectionMessage(const String& message);
	void SetWidgetKeyBinding(const String& text = "");

	// Lifecycle checks
	bool HasRunningTask() const;
	bool HasRunningRenderTask() const;

protected:
	virtual void Close() override;
	virtual void Layout() override;
	virtual bool Key(dword key, int count) override;

private:
	// Core UI Layout
	TabCtrl      main_tabs;
	MenuBar      menu_bar;
	ToolBar      tool_bar;
	StatusBar    status_bar;
	
	// Docks (Mapped to U++ Layout/Frames)
	ParentCtrl   timeline_area;
	ParentCtrl   bin_area;
	ParentCtrl   monitor_area;
	
	// Specific widgets
	AssetPanel*            asset_panel = nullptr;
	Monitor*               clip_monitor = nullptr;
	Monitor*               project_monitor = nullptr;
	TimelineTabs*          timeline_tabs = nullptr;
	StatusBarMessageLabel* message_label = nullptr;
	RenderWidget*          render_widget = nullptr;
	
	Vector<Bin*>           bin_widgets;

	// Internal Setup
	void SetupActions();
	void SetupMenu(Bar& bar);
	void SetupToolbar(Bar& bar);
	
	// Option management
	bool ReadOptions();
	void SaveOptions();
};

END_UPP_NAMESPACE

#endif
