#ifndef _VSTConnections_VSTConnectionsWnd_h_
#define _VSTConnections_VSTConnectionsWnd_h_

#include <CtrlLib/CtrlLib.h>
#include <Docking/Docking.h>
#include "VSTConnectionsCtrl.h"
#include "VSTConnectionsPresenter.h"

NAMESPACE_UPP

class VSTConnectionsWnd : public WithDockManager<ParentCtrl> {
public:
	typedef VSTConnectionsWnd CLASSNAME;
	
	VSTConnectionsWnd();
	
	void Open();
	void Close();

private:
	VSTConnectionsCtrl connectionsCtrl;
	VSTConnections::VSTConnectionsPresenter* presenter;
	am::IOMatrixService ioMatrixService; // Service instance for the presenter
	
	// Toolbar and menu
	ToolBar toolBar;
	
	void CreateMenuBar();
	void CreateToolBar();
	void Data();
	
	// Menu callbacks
	void New();
	void OpenFile();
	void Save();
	void SaveAs();
	void CloseWindow();
};

END_UPP_NAMESPACE

#endif