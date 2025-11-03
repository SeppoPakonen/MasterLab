#include "SubWindowCtrl.h"


SubWindowCtrl::SubWindowCtrl() : wm(0), id(-1) {
	
}

void SubWindowCtrl::Init(SubWindows* wm, int id) {
	this->wm = wm;
	this->id = id;
}

void SubWindowCtrl::Title(const Upp::String& title) {
	if (wm)
		wm->SetTitle(id, title);
}

void SubWindowCtrl::ApplyTheme(bool isDark) {
	// Base implementation - can be overridden by derived classes
	// This allows each SubWindowCtrl derived class to handle theme changes
}



void SubWindow::SetContent(SubWindowCtrl& ctrl) {
	this->ctrl = &ctrl;
	
	Add(ctrl.VSizePos(24, 1).HSizePos(1, 1));
	
	// Set icon from SubWindowCtrl
	Image ctrl_icon = ctrl.GetIcon();
	if (!ctrl_icon.IsEmpty())
		Icon(ctrl_icon);
}

void SubWindow::ChildGotFocus() {
	FocusEvent();
}

void SubWindow::ChildMouseEvent(Ctrl *child, int event, Point p, int zdelta, dword keyflags) {
	if (event == LEFTDOWN) {
		// Don't focus if we're currently resizing
		if (!resizing) {
			FocusEvent();
		}
	}
}

SubWindow::SubWindow() : stored_rect(0,0,0,0) {
	ctrl = 0;
	maximized = false;
	resizing = false;
	resize_mode = 0;
	
	Add(decor.SizePos());
	
	close.SetImage(SubWindowsImg::close());
	maximize.SetImage(SubWindowsImg::maximize());
	minimize.SetImage(SubWindowsImg::minimize());
	
	Add(close.TopPos(3, 19).RightPos(3, 19));
	Add(maximize.TopPos(3, 19).RightPos(3+22, 19));
	Add(minimize.TopPos(3, 19).RightPos(3+22+19, 19));
	
	decor.WhenWindowMove = Proxy(WhenWindowMove);
	decor.WhenFocus = THISBACK(FocusEvent);
	decor.WhenMaximize = THISBACK(Maximize);
	decor.WhenMinimize = Proxy(WhenMinimize);
	decor.WhenClose = Proxy(WhenClose);
	decor.SetActive(false);  // Initially inactive
	close.WhenAction = Proxy(WhenClose);
	maximize.WhenAction = THISBACK(Maximize);
	minimize.WhenAction = Proxy(WhenMinimize);
	
}

void SubWindow::LeftUp(Point p, dword keyflags) {
	if (resizing) {
		resizing = false;
		ReleaseCapture();
	} else {
		// Handle the original behavior when not resizing
		FocusEvent();
	}
}

void SubWindow::MouseMove(Point p, dword keyflags) {
	if (resizing) {
		DoResize(p);
	} else {
		// Change cursor based on position for resize feedback
		// For now, just use default cursor - proper cursor IDs can be implemented later
		// int resize = GetResizeMode(p);
		// switch(resize) {
		//     case 1: // left
		//     case 2: // right
		//         SetCursor(Ctrl::CURSOR_HSPLIT);
		//         break;
		//     case 3: // top
		//     case 4: // bottom
		//         SetCursor(Ctrl::CURSOR_VSPLIT);
		//         break;
		//     case 5: // top-left
		//     case 8: // bottom-right
		//         SetCursor(Ctrl::CURSOR_SIZENW);
		//         break;
		//     case 6: // top-right
		//     case 7: // bottom-left
		//         SetCursor(Ctrl::CURSOR_SIZENE);
		//         break;
		//     default:
		//         SetCursor(Ctrl::CURSOR_ARROW);
		//         break;
		// }
		// For now, just use the default arrow cursor
		// SetCursor(Ctrl::ARROW); // If Ctrl::ARROW doesn't exist in this U++ version
		// Using default cursor by not changing it
	}
}

int SubWindow::GetResizeMode(Point p) {
	if (maximized) return 0;  // Can't resize maximized windows
	
	Rect r = GetRect();
	int border_size = 5;  // pixels from edge where resize is active
	
	// Check corners first (they take precedence)
	if (p.x <= border_size && p.y <= border_size) return 5; // top-left
	if (p.x >= r.GetWidth() - border_size && p.y <= border_size) return 6; // top-right
	if (p.x <= border_size && p.y >= r.GetHeight() - border_size) return 7; // bottom-left
	if (p.x >= r.GetWidth() - border_size && p.y >= r.GetHeight() - border_size) return 8; // bottom-right
	
	// Check edges
	if (p.x <= border_size) return 1; // left
	if (p.x >= r.GetWidth() - border_size) return 2; // right
	if (p.y <= border_size) return 3; // top
	if (p.y >= r.GetHeight() - border_size) return 4; // bottom
	
	return 0; // no resize
}

void SubWindow::StartResize(int mode, Point p) {
	resizing = true;
	resize_mode = mode;
	resize_start = p;
	resize_original = GetRect();
	SetCapture();
}

void SubWindow::DoResize(Point p) {
	if (!resizing) return;
	
	Point delta = p - resize_start;
	Rect r = resize_original;
	
	switch(resize_mode) {
		case 1: // left
			r.left += delta.x;
			if (r.GetWidth() < 100) r.left = r.right - 100; // minimum width
			break;
		case 2: // right
			r.right += delta.x;
			if (r.GetWidth() < 100) r.right = r.left + 100; // minimum width
			break;
		case 3: // top
			r.top += delta.y;
			if (r.GetHeight() < 50) r.top = r.bottom - 50; // minimum height
			break;
		case 4: // bottom
			r.bottom += delta.y;
			if (r.GetHeight() < 50) r.bottom = r.top + 50; // minimum height
			break;
		case 5: // top-left
			r.left += delta.x;
			r.top += delta.y;
			if (r.GetWidth() < 100) r.left = r.right - 100;
			if (r.GetHeight() < 50) r.top = r.bottom - 50;
			break;
		case 6: // top-right
			r.right += delta.x;
			r.top += delta.y;
			if (r.GetWidth() < 100) r.right = r.left + 100;
			if (r.GetHeight() < 50) r.top = r.bottom - 50;
			break;
		case 7: // bottom-left
			r.left += delta.x;
			r.bottom += delta.y;
			if (r.GetWidth() < 100) r.left = r.right - 100;
			if (r.GetHeight() < 50) r.bottom = r.top + 50;
			break;
		case 8: // bottom-right
			r.right += delta.x;
			r.bottom += delta.y;
			if (r.GetWidth() < 100) r.right = r.left + 100;
			if (r.GetHeight() < 50) r.bottom = r.top + 50;
			break;
	}
	
	SetRect(r);
}

void SubWindow::ApplyThemeToWindow(bool isDark) {
	// This method would be called when theme changes to update the appearance
	// In a real implementation, this would update the appearance of buttons and other elements
	// to match the dark/light theme
	
	if (isDark) {
		// In dark theme, buttons might have different appearance
		// For now, we'll just refresh the window to repaint everything
		Refresh();
	} else {
		// In light theme
		Refresh();
	}
}




SubWindowDecoration::SubWindowDecoration() {
	left_down = false;
	icon_clicked = false;
	
}
	
void SubWindowDecoration::Paint(Draw& draw) {
	ImageDraw id(GetSize());
	
	Color border_tl, border_br;
	Color left, right;
	Color text_color;
	
	if (Upp::IsDarkTheme()) {
		border_tl = GrayColor(64);  // Darker border in dark theme
		border_br = GrayColor(32);
		text_color = White();       // White text on dark background
	} else {
		border_tl = GrayColor(128+64);
		border_br = GrayColor(128);
		text_color = Black();       // Black text on light background
	}
	
	Size sz(GetSize());
	
	if (Upp::IsDarkTheme()) {
		id.DrawRect(sz, GrayColor(40));  // Dark background
	} else {
		id.DrawRect(sz, White());        // Light background
	}
	
	id.DrawLine(0,0, 0, sz.cy-1, 1, border_tl);
	id.DrawLine(0,0, sz.cx-1, 0, 1, border_tl);
	id.DrawLine(sz.cx-1,0, sz.cx-1, sz.cy-1, 1, border_br);
	id.DrawLine(0,sz.cy-1, sz.cx-1, sz.cy-1, 1, border_br);
	
	if (GetActive()) {
		if (Upp::IsDarkTheme()) {
			left = Color(30, 90, 150);    // Darker active color in dark theme
			right = Color(80, 160, 220);
		} else {
			left = Color(0, 64, 128);
			right = Color(57, 141, 195);
		}
	} else {
		if (Upp::IsDarkTheme()) {
			left = GrayColor(80);         // Darker inactive color in dark theme
			right = GrayColor(120);
		} else {
			left = GrayColor();
			right = GrayColor(195);
		}
	}
	for(int i = 0; i < sz.cx; i++) {
		int x = i;
		int alpha = 255 * i / (sz.cx -2);
		Color clr = Blend(left, right, alpha);
		id.DrawLine(i, 0, i, 23, 1, clr);
	}
	
	// Draw icon if available
	if (!icon.IsEmpty()) {
		id.DrawImage(4, 4, 16, 16, icon);
		id.DrawText(24, 4, label, StdFont(15), text_color);
	} else {
		id.DrawText(7, 4, label, StdFont(15), text_color);
	}
	
	Color tl, br;
	if (Upp::IsDarkTheme()) {
		tl = GrayColor(96);
		br = GrayColor(32);
	} else {
		tl = GrayColor(128+64+32);
		br = GrayColor(128-64-32);
	}
	
	id.DrawLine(0,0, sz.cx-1, 0, 1, tl);
	id.DrawLine(0,0, 0, sz.cy-1, 1, tl);
	id.DrawLine(sz.cx-1, sz.cy-1, sz.cx-1, 0, 1, br);
	id.DrawLine(sz.cx-1, sz.cy-1, 0, sz.cy-1, 1, br);
	
	draw.DrawImage(0, 0, id);
}

void SubWindowDecoration::LeftDown(Point p, dword keyflags) {
	left_down = true;
	left_down_pt = p;
	icon_clicked = IsIconAt(p);
	SetCapture();
	
	if (icon_clicked) {
		// Left click on icon - show context menu
		MenuBar::Execute(THISBACK(LocalMenu));
	} else {
		// Normal click - focus the window
		WhenFocus();
	}
}

void SubWindowDecoration::LeftDouble(Point p, dword keyflags) {
	WhenMaximize();
}

void SubWindowDecoration::LeftUp(Point p, dword keyflags) {
	left_down = false;
	ReleaseCapture();
	
}

void SubWindowDecoration::MouseMove(Point p, dword keyflags) {
	if (left_down) {
		WhenWindowMove(p - left_down_pt);
	}
}

bool SubWindowDecoration::IsIconAt(Point p) const {
	if (icon.IsEmpty()) return false;
	return p.x >= 4 && p.x < 20 && p.y >= 4 && p.y < 20;  // Icon position and size
}

void SubWindowDecoration::RightDown(Point p, dword keyflags) {
	if (IsIconAt(p)) {
		// Right click on icon - handle differently if needed
		MenuBar::Execute(THISBACK(LocalMenu));
	} else {
		MenuBar::Execute(THISBACK(LocalMenu));
	}
}

void SubWindowDecoration::LocalMenu(Bar& bar) {
	bar.Add("Maximize / Restore", Proxy(WhenMaximize));
	bar.Add("Minimize", Proxy(WhenMinimize));
	bar.Separator();
	bar.Add("Close", Proxy(WhenClose));
}
