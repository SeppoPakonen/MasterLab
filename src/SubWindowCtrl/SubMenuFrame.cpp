#include "SubWindowCtrl.h"


SubMenuFrame::SubMenuFrame(SubWindows* wins) : wins(wins) {
	height = 20;
	shift = 0;
	arrow_border = 12;
	
	left_arrow = false;
	right_arrow = false;
	visible = true;
	
	clr_bg = GrayColor(255);
	clr_tr = GrayColor(128+64);
}

void SubMenuFrame::Paint(Draw& w) {
	if (!visible) return; // Don't paint if not visible
	
	ImageDraw id(GetSize());
	
	Color bg_color, border_color, text_color, line_color, active_color;
	
	if (Upp::IsDarkTheme()) {
		bg_color = GrayColor(40);      // Dark background
		border_color = GrayColor(80);  // Darker border
		text_color = White();          // White text on dark background
		line_color = GrayColor(70);    // Darker line color
		active_color = GrayColor(100); // Darker active color
	} else {
		bg_color = GrayColor(255);        // Light background
		border_color = GrayColor(128+64); // Lighter border
		text_color = Black();             // Black text on light background
		line_color = GrayColor();         // Standard line color
		active_color = GrayColor(128+64+32); // Standard active color
	}
	
	Rect r = GetRect();
	
	int width = r.Width();
	id.DrawRect(0, 0, width, height, bg_color);
	
	Size menu_sz(r.GetSize());
	
	id.DrawLine(0, 0, menu_sz.cx-1, 0, 1, border_color);
	
	Font fnt = StdFont(15);
	
	int count = wins->GetCount();
	id_pos.SetCount(count);
	id_icons.SetCount(count); // Update icons vector
	int x = -shift;
	int active_pos = wins->GetActiveWindowPos();
	
	// Update icons from SubWindowCtrls
	for(int i = 0; i < count; i++) {
		SubWindow& sub = (*wins)[i];
		SubWindowCtrl* ctrl = sub.GetSubWindowCtrl();
		Image icon;
		if (ctrl) {
			icon = ctrl->GetCtrlIcon();
		}
		if (icon.IsEmpty()) {
			icon = CtrlImg::smallright(); // Use a default icon if none is provided
		}
		id_icons[i] = icon;
	}
	
	bool draw_right_arrow = false;
	for(int i = 0; i < count; i++) {
		
		x += 5;
		if (i) {
			id.DrawLine(x, 3, x, height-2, 1, line_color);
			x += 5;
		}
		SubWindow& sub = (*wins)[i];
		
		Upp::String title = sub.GetTitle();
		bool active = active_pos == i;
		Size sz = GetTextSize(title, fnt);
		
		if (x + sz.cx >= menu_sz.cx)
			draw_right_arrow = true;
		
		if (active)
			id.DrawRect(x-5+1, 0, sz.cx+10-1, sz.cy, active_color);
		
		// Draw icon if available
		Image icon = id_icons[i];
		if (!icon.IsEmpty()) {
			id.DrawImage(x, 3, 16, 16, icon);
			id.DrawText(x + 20, 0, title, fnt, text_color);
		} else {
			id.DrawText(x, 0, title, fnt, text_color);
		}
		
		x += sz.cx + 20; // Account for icon width if icon is drawn
		
		id_pos[i] = x;
	}
	
	// The last line at the right end
	if (count)
		id.DrawLine(x+5, 3, x+5, height-2, 1, line_color);
	
	// Draw shift arrows
	left_arrow = false;
	right_arrow = false;
	if (shift) {
		id.DrawRect(0, 0, arrow_border, menu_sz.cy, bg_color);
		id.DrawText(0, 0, "<", fnt, text_color);
		left_arrow = true;
	}
	if (draw_right_arrow) {
		id.DrawRect(menu_sz.cx - arrow_border, 0, arrow_border, menu_sz.cy, bg_color);
		id.DrawText(menu_sz.cx - arrow_border, 0, ">", fnt, text_color);
		right_arrow = true;
	}
	
	w.DrawImage(0, 0, id);
}




void SubMenuFrame::LeftDown(Point p, dword keyflags) {
	int limit = GetSize().cx - arrow_border;
	
	if (left_arrow && p.x < arrow_border) {
		shift -= 20;
		if (shift <= 0) shift = 0;
		Refresh();
		return;
	}
	else if (right_arrow && p.x >= limit) {
		shift += 20;
		Refresh();
		return;
	}
	
	int id = -1;
	for(int i = 0; i < id_pos.GetCount(); i++) {
		if (p.x < id_pos[i]) {id = i; break;}
	}
	if (id < 0) return;
	
	WhenFocus(id);
}

void SubMenuFrame::RightDown(Point p, dword keyflags) {
	clicked_id = -1;
	for(int i = 0; i < id_pos.GetCount(); i++) {
		if (p.x < id_pos[i]) {clicked_id = i; break;}
	}
	if (clicked_id >= 0)
		clicked_id = wins->GetPosId(clicked_id);
	MenuBar::Execute(THISBACK(LocalMenu));
}

void SubMenuFrame::MouseWheel(Point p, int zdelta, dword keyflags) {
	if (right_arrow && zdelta > 0) {
		shift += zdelta / 40 * 10;
		Refresh();
	}
	else if (left_arrow && zdelta < 0) {
		shift += zdelta / 40 * 10;
		if (shift <= 0) shift = 0;
		Refresh();
	}
}

void SubMenuFrame::LocalMenu(Bar& bar) {
	if (clicked_id >= 0) {
		bar.Add("Close", THISBACK(Close));
		bar.Separator();
		bar.Add("Maximize / Restore", THISBACK(Maximize));
		bar.Add("Minimize", THISBACK(Minimize));
		bar.Separator();
		bar.Add("Close All", Proxy(WhenCloseAll));
		bar.Add("Close Others", THISBACK(CloseOthers));
	}
	bar.Add("Tile Windows", Proxy(WhenTileWindows));
	
}
