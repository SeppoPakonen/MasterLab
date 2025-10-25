#ifndef _Preferences_PrefModel_h_
#define _Preferences_PrefModel_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

// Forward declarations for the model
struct AppearancePrefs;
struct EditingPrefs;
struct EventDisplayPrefs;
struct GeneralPrefs;
struct MIDIPrefs;
struct MediaBayPrefs;
struct RecordPrefs;
struct ScoresPrefs;
struct TransportPrefs;
struct VSTPrefs;
struct VariAudioPrefs;

class PreferencesModel {
public:
	PreferencesModel();
	
	// Model access
	AppearancePrefs& GetAppearance() { return appearance; }
	EditingPrefs& GetEditing() { return editing; }
	EventDisplayPrefs& GetEventDisplay() { return event_display; }
	GeneralPrefs& GetGeneral() { return general; }
	MIDIPrefs& GetMIDI() { return midi; }
	MediaBayPrefs& GetMediaBay() { return mediabay; }
	RecordPrefs& GetRecord() { return record; }
	ScoresPrefs& GetScores() { return scores; }
	TransportPrefs& GetTransport() { return transport; }
	VSTPrefs& GetVST() { return vst; }
	VariAudioPrefs& GetVariAudio() { return variaudio; }
	
	// Version for schema versioning
	int GetVersion() const { return version; }
	void SetVersion(int v) { version = v; }
	
	// Load defaults
	void LoadDefaults();
	
private:
	int version = 1;  // Schema version
	
	AppearancePrefs appearance;
	EditingPrefs editing;
	EventDisplayPrefs event_display;
	GeneralPrefs general;
	MIDIPrefs midi;
	MediaBayPrefs mediabay;
	RecordPrefs record;
	ScoresPrefs scores;
	TransportPrefs transport;
	VSTPrefs vst;
	VariAudioPrefs variaudio;
};

// Basic preference structures
struct AppearancePrefs {
	// Interface adjustments
	int saturation = 50;        // 0-100
	int brightness = 50;        // 0-100
	int button_brightness = 50; // 0-100
};

struct EditingPrefs {
	// Defaults
	String default_track_time_type = "musical"; // { musical | time_linear | follow_transport }
	
	// Behavior
	bool auto_select_under_cursor = false;
	bool cycle_follows_range = false;
	bool delete_overlaps = false;
	bool link_editors = true;
	bool parts_get_track_names = false;
	bool quick_zoom = false;
	
	// Lock attributes
	int lock_event_attributes = 0; // bitmask(Position | Size | Other)
	
	// Drag delay
	int drag_delay_ms = 200;
};

struct EventDisplayPrefs {
	// General
	bool show_names = true;
	bool transparent = false;
	bool show_on_small_heights = false;
	bool colorize_bg = true;
};

struct GeneralPrefs {
	String language = "English";  // Language selection
	bool autosave = true;
	double autosave_minutes = 15.0;
	int max_backup_files = 10;
	bool show_tips = true;
	int max_undo = -1;  // -1 = infinite
	bool run_setup_on_new = false;
	String on_startup = "show_open_dialog"; // { do_nothing, open_last, open_default_template, show_open_dialog, show_template_dialog, show_options_dialog }
	bool usage_profile = false;
};

struct MIDIPrefs {
	// Core
	bool thru_active = true;
	bool reset_on_stop = false;
	int length_adjust_ticks = -2;
	
	// Chase 
	struct ChasePrefs {
		bool note = true;
		bool poly_pressure = true;
		bool controller = true;
		bool ignore_part_bounds = true;
		bool prog_change = true;
		bool aftertouch = true;
		bool pitchbend = true;
		bool sysex = false;
	} chase;
	
	// Display
	int ppq_base = 480;
	int display_res_1_16_ticks = 120;
	
	// Record
	bool insert_reset_after_record = false;
	bool audition_through_inserts = false;
	int max_feedback_ms = 250;
};

struct MediaBayPrefs {
	int max_results = 100000;
	bool allow_edit = false;
	bool stop_scan_on_close = true;
	bool show_extensions = false;
};

struct RecordPrefs {
	// Audio
	double pre_record_seconds = 1.0;
	bool create_images_during_record = true;
	String cycle_record_mode = "create_events_regions"; // { create_regions, create_events, create_events_regions }
	
	// Audio - BWF
	String descriptor = "MasterLab";
	String author = "MasterLab";
	String reference = "";
	
	// MIDI
	bool snap_parts_to_bars = true;
	bool solo_record_in_editors = true;
	int catch_range_ms = 0;
	bool retrospective_record = true;
	int retro_buffer_events = 10000;
	String replace_recording_in_editors = "none"; // { none, controller, all }
};

struct ScoresPrefs {
	// Scores preferences will be defined in ScoresEngine package
};

struct TransportPrefs {
	// Transport behavior
	bool playback_toggle_preview = false;
	bool zoom_while_locating = false;
	int cursor_width = 3;
	bool return_to_start = false;
	bool deactivate_punch_on_stop = false;
	bool stop_after_auto_punch = false;
	bool stop_while_winding = false;
	String wind_mode = "adjust_to_zoom"; // { adjust_to_zoom, fixed }
	int speed_factor = 1;
	int fast_wind_factor = 10;
	bool show_timecode_subframes = false;
	int user_framerate = 30;
	bool stationary_cursor = false;
	bool locate_on_empty_click = false;
	
	// Scrub
	struct ScrubPrefs {
		int response = 50;
		int volume = 50;
		bool cpu_saving = false;
	} scrub;
};

struct VSTPrefs {
	// Core
	bool connect_sends_auto = true;
	bool instr_use_automation_rw_all = true;
	bool mute_pre_send_on_mute = true;
	bool group_channels_mute_sources = true;
	double delay_comp_threshold_ms = 10.0;
	bool export_warnings_as_text = false;
	bool use_cubase3_eq_as_default = false;
	String default_stereo_panner = "dual"; // { dual, combined, balance }
	bool link_send_panners = true;
	String auto_monitoring = "manual"; // { manual, while_record_enabled, while_record_running, tape_machine }
	bool warn_overloads = true;
	
	// Plugins
	bool warn_before_remove_modified = true;
	bool open_editor_after_load = true;
	String create_midi_track_policy = "ask"; // { ask, always, never }
	bool suspend_vst3_when_silent = true;
	bool sort_menu_by_vendor = true;
	bool plugin_editor_always_on_top = true;
	
	// Metering
	int peak_hold_ms = 5000;
	int slow_fallback_dbps = 10;
	int fast_fallback_dbps = 100;
	bool map_inputbus_to_track = true;
	
	// Control room
	bool show_volume_in_transport = true;
	bool disable_talkback = false;
	bool phones_as_preview = false;
	bool dim_studio = false;
	bool signal_presence = false;
	bool multi_channel_solo = false;
	bool show_downmix_presets = false;
	bool metronome_in_studio = false;
	bool metronome_in_control_room = false;
	bool show_reference_level = false;
	double reference_level_db = -18.0;
	double max_dim_db = 20.0;
};

struct VariAudioPrefs {
	bool inhibit_warn_change_sample = false;
	bool inhibit_warn_offline_process = false;
};

}

#endif