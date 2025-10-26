#ifndef _MediaPool_PoolWindow_h_
#define _MediaPool_PoolWindow_h_

namespace am {

class PoolWindow : public TopWindow {
public:
	typedef PoolWindow CLASSNAME;
	PoolWindow();

	void OpenWindow();
	void CloseWindow();
	void RefreshList();
	void ToggleStatusBar(bool show);

private:
	void Init();
	void BuildToolbar();
	void BuildList();
	void UpdateStatusText();
	void OnToggleStatusBar();
	void OnPlaySelected();
	void OnLoopSelected();
	void OnImportMedia();
	void OnSearchMedia();
	void OnOpenAll();
	void OnCloseAll();

	ToolBar toolbar;
	SliderCtrl toolbarVolume;
	Button toggleStatusBarButton;
	Button playButton;
	Button loopButton;
	Button openAllButton;
	Button closeAllButton;
	Button importButton;
	Button searchButton;
	DropList columnVisibility;
	ArrayCtrl mediaList;
	Label projectFolderLabel;
	Label poolFolderLabel;
	StatusBar statusBar;
	bool statusVisible = true;
};

}

#endif
