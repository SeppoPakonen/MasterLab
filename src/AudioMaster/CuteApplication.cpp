#include "AudioMaster.h"

namespace {

struct CuteBootConfig {
	String title = CUTE_TITLE;
	String version = CUTE_VERSION;
	String locale;
	String style_theme;
	String style_sheet;
	String color_theme;
	String icons_theme;
	int base_font_height = 0;
	bool single_instance = true;
	bool enable_stacktrace = false;
	bool force_x11 = true;
};

String JoinPathParts(const String& a, const String& b) {
	if(a.IsEmpty())
		return b;
	if(b.IsEmpty())
		return a;
	if(a.EndsWith("/") || a.EndsWith("\\"))
		return a + b;
	return a + DIR_SEPS + b;
}

String CuteAppRoot() {
	String exe = GetExeFilePath();
	String dir = GetFileFolder(exe);
	return DirectoryUp(dir);
}

String CuteDataDir() {
	return JoinPathParts(CuteAppRoot(), "share/Cute");
}

String CuteTranslationDir() {
	return JoinPathParts(CuteDataDir(), "translations");
}

String CutePaletteDir() {
	return JoinPathParts(CuteDataDir(), "palette");
}

String CutePluginDir() {
	return JoinPathParts(CuteAppRoot(), "lib/qt6/plugins");
}

bool LoadTranslationCatalog(const String& path, const String& lang) {
	if(path.IsEmpty() || lang.IsEmpty())
		return false;
	if(!FileExists(path))
		return false;
	String data = LoadFile(path);
	return !data.IsEmpty();
}

void ApplyNamedPalette(const CuteBootConfig& cfg) {
	if(cfg.color_theme.IsEmpty())
		return;
	String palette_file = JoinPathParts(CutePaletteDir(), cfg.color_theme + ".conf");
	if(!FileExists(palette_file))
		return;
	// Phase 1 note: the original application loaded named palette configs here.
	// U++ palette/theme application will be finalized once the palette form is converted.
}

void ApplyStyleChoices(const CuteBootConfig& cfg) {
	if(cfg.base_font_height > 0)
		SetStdFont(SansSerif(cfg.base_font_height));
	if(!cfg.style_theme.IsEmpty()) {
		// Phase 1 note: the original application used a toolkit-native style factory here.
		// Cute should eventually route this through Theme/Appearance package services.
	}
	if(!cfg.style_sheet.IsEmpty()) {
		// Phase 1 note: the original application loaded external stylesheet data here.
	}
	ApplyNamedPalette(cfg);
}

void InstallCrashHandlers(const CuteBootConfig& cfg) {
	if(!cfg.enable_stacktrace)
		return;
	// Phase 1 note: the original application installed POSIX crash handlers and a debugger stack dump path.
}

bool NotifyExistingInstance(const String& channel) {
	if(channel.IsEmpty())
		return false;
	// Phase 1 note: the original application used platform IPC to raise an existing instance.
	return false;
}

String BuildUniqueInstanceKey(const CuteBootConfig& cfg) {
	String user = GetEnv("USER");
	if(user.IsEmpty())
		user = GetEnv("USERNAME");
	String host = GetComputerName();
	String key = cfg.title;
	if(!user.IsEmpty())
		key << ':' << user;
	if(!host.IsEmpty())
		key << '@' << host;
	return key;
}

void LoadTranslations(const CuteBootConfig& cfg) {
	String lang = cfg.locale;
	if(lang.IsEmpty())
		lang = GetLanguageInfo(GetSystemLNG()).english_name;
	if(lang.IsEmpty())
		return;
	LoadTranslationCatalog(JoinPathParts(CuteTranslationDir(), "qt_" + lang + ".tr"), lang);
	LoadTranslationCatalog(JoinPathParts(CuteTranslationDir(), "cute_" + lang + ".tr"), lang);
}

CuteBootConfig BuildBootConfig() {
	CuteBootConfig cfg;
	cfg.locale = GetLanguageInfo(GetSystemLNG()).english_name;
	return cfg;
}

void InstallCuteEnvironment(const CuteBootConfig& cfg) {
	if(cfg.force_x11) {
		// Phase 1 note: the original application forced X11 when Wayland support was disabled.
	}
	if(!cfg.icons_theme.IsEmpty()) {
		// Phase 1 note: icon theme search path handling belongs to Cute assembly startup.
	}
	String plugin_dir = CutePluginDir();
	if(!plugin_dir.IsEmpty()) {
		// Phase 1 note: toolkit plugin path extension belongs to Cute assembly startup and build integration.
	}
}

}

struct CuteApplication::Data {
	CuteBootConfig config;
	Ptr<Ctrl> main_widget;
	String unique_key;
};

CuteApplication::CuteApplication() {
	data.Create();
	data->config = BuildBootConfig();
	LoadTranslations(data->config);
}

CuteApplication::~CuteApplication() {
	ClearServerState();
}

void CuteApplication::SetMainWidget(Ctrl* widget) {
	data->main_widget = widget;
}

Ctrl* CuteApplication::GetMainWidget() const {
	return data ? ~data->main_widget : nullptr;
}

bool CuteApplication::SetupSingleInstance() {
	InstallCrashHandlers(data->config);
	if(!data->config.single_instance)
		return false;
	data->unique_key = BuildUniqueInstanceKey(data->config);
	return NotifyExistingInstance(data->unique_key);
}

void CuteApplication::ClearServerState() {
	if(data)
		data->unique_key.Clear();
}

void CuteApplication::OnNewConnection() {
	Ctrl* widget = GetMainWidget();
	if(widget) {
		if(MainWindow* main_window = dynamic_cast<MainWindow*>(widget))
			main_window->OpenMain();
		else if(CuteMainForm* main_form = dynamic_cast<CuteMainForm*>(widget))
			main_form->Open();
		else
			widget->Show();
		widget->SetFocus();
	}
}

void CuteApplication::OnReadyRead() {
	OnNewConnection();
}

int CuteApplication::Run() {
	if(SetupSingleInstance())
		return 2;

	ApplyStyleChoices(data->config);

	CuteMainForm w;
	SetMainWidget(&w);
	w.Setup();
	w.Open();
	w.Run();
	return 0;
}

int RunCuteApplication(const Vector<String>& args) {
	CuteBootConfig cfg = BuildBootConfig();
	for(int i = 0; i < args.GetCount(); i++) {
		const String& arg = args[i];
		if(arg == "--no-single-instance")
			cfg.single_instance = false;
		else if(arg == "--stacktrace")
			cfg.enable_stacktrace = true;
		else if(arg == "--no-x11")
			cfg.force_x11 = false;
		else if(arg == "--style" && i + 1 < args.GetCount())
			cfg.style_theme = args[++i];
		else if(arg == "--stylesheet" && i + 1 < args.GetCount())
			cfg.style_sheet = args[++i];
		else if(arg == "--palette" && i + 1 < args.GetCount())
			cfg.color_theme = args[++i];
		else if(arg == "--icons" && i + 1 < args.GetCount())
			cfg.icons_theme = args[++i];
		else if(arg == "--font-height" && i + 1 < args.GetCount())
			cfg.base_font_height = StrInt(args[++i]);
	}

	InstallCuteEnvironment(cfg);

	CuteApplication app;
	return app.Run();
}
