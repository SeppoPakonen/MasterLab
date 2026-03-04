#include "AudioMaster.h"

namespace {

struct CuteBootConfig {
	String title = "Cute";
	String version;
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
	if(data.IsEmpty())
		return false;
	return true;
}

void ApplyNamedPalette(const CuteBootConfig& cfg) {
	if(cfg.color_theme.IsEmpty())
		return;
	String palette_file = JoinPathParts(CutePaletteDir(), cfg.color_theme + ".conf");
	if(!FileExists(palette_file))
		return;
	// Phase 1 note: qtractor loads named Qt palette configs here.
	// U++ palette/theme application will be finalized once the palette form is converted.
}

void ApplyStyleChoices(const CuteBootConfig& cfg) {
	if(cfg.base_font_height > 0)
		SetStdFont(SansSerif(cfg.base_font_height));
	if(!cfg.style_theme.IsEmpty()) {
		// Phase 1 note: qtractor used QStyleFactory for native/Qt styles.
		// Cute should eventually route this through Theme/Appearance package services.
	}
	if(!cfg.style_sheet.IsEmpty()) {
		// Phase 1 note: qtractor loaded QSS from disk. The U++ port needs an Appearance/Theme equivalent.
	}
	ApplyNamedPalette(cfg);
}

void InstallCrashHandlers(const CuteBootConfig& cfg) {
	if(!cfg.enable_stacktrace)
		return;
	// Phase 1 note: original qtractor installed POSIX signal handlers and invoked gdb for stack traces.
	// The U++ port should keep that behavior behind a Cute-owned debug switch in phase 2.
}

bool NotifyExistingInstance(const String& channel) {
	if(channel.IsEmpty())
		return false;
	// Phase 1 note: qtractor used X11 selection ownership or QLocalServer/QSharedMemory.
	// Cute should provide a single-instance coordinator in phase 2, likely under Windowing or AudioMaster.
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
	LoadTranslationCatalog(JoinPathParts(CuteTranslationDir(), "qtractor_" + lang + ".tr"), lang);
}

CuteBootConfig BuildBootConfig() {
	CuteBootConfig cfg;
	cfg.version = "phase1";
	cfg.locale = GetLanguageInfo(GetSystemLNG()).english_name;
	return cfg;
}

}

class qtractorApplication {
public:
	qtractorApplication();
	~qtractorApplication();

	void setMainWidget(Ctrl* widget);
	Ctrl* mainWidget() const;
	bool setup();
	void clearServer();
	void newConnectionSlot();
	void readyReadSlot();
	int Run();

private:
	CuteBootConfig config;
	Ptr<Ctrl> main_widget;
	String unique_key;
};

qtractorApplication::qtractorApplication()
	: config(BuildBootConfig()) {
	LoadTranslations(config);
}

qtractorApplication::~qtractorApplication() {
	clearServer();
}

void qtractorApplication::setMainWidget(Ctrl* widget) {
	main_widget = widget;
}

Ctrl* qtractorApplication::mainWidget() const {
	return main_widget;
}

bool qtractorApplication::setup() {
	InstallCrashHandlers(config);
	if(!config.single_instance)
		return false;
	unique_key = BuildUniqueInstanceKey(config);
	return NotifyExistingInstance(unique_key);
}

void qtractorApplication::clearServer() {
	unique_key.Clear();
}

void qtractorApplication::newConnectionSlot() {
	if(main_widget) {
		main_widget->OpenMain();
		main_widget->SetFocus();
	}
}

void qtractorApplication::readyReadSlot() {
	newConnectionSlot();
}

int qtractorApplication::Run() {
	if(setup())
		return 2;

	ApplyStyleChoices(config);

	MainWindow w;
	setMainWidget(&w);
	w.OpenMain();
	w.Run();
	return 0;
}

void InstallCuteEnvironment(const CuteBootConfig& cfg) {
	if(cfg.force_x11) {
		// Phase 1 note: qtractor forced xcb when Wayland support was disabled.
		// The Cute build script may later export backend-specific environment variables before launch.
	}

	String icon_theme = cfg.icons_theme;
	if(!icon_theme.IsEmpty()) {
		// Phase 1 note: qtractor adjusted fallback icon search paths here.
	}

	String plugin_dir = CutePluginDir();
	if(!plugin_dir.IsEmpty()) {
		// Phase 1 note: Qt plugin path extension belongs to Cute assembly startup and build integration.
	}
}

int qtractor_main(const Vector<String>& args) {
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

	qtractorApplication app;
	app.clearServer();
	return app.Run();
}

