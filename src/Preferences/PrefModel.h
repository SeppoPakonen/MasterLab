#ifndef _Preferences_PrefModel_h_
#define _Preferences_PrefModel_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h>
#include <AudioFX/AudioFX.h>
#include <AudioGraph/AudioGraph.h>
#include <Browser/Browser.h>
#include <HelpAbout/HelpAbout.h>
#include <Math/Math.h>
#include <MIDI/MIDI.h>
#include <ProjectMgmt/ProjectMgmt.h>
#include <ProjectWindow/ProjectWindow.h>
#include <ProjectSetup/ProjectSetup.h>
#include <ScoresEngine/ScoresEngine.h>
#include <Tooling/Tooling.h>
#include <TransportPrefs/TransportPrefs.h>
#include <TransportUI/TransportUI.h>
#include <Video/Video.h>
#include <VSTHost/VstHostPrefs.h>
#include <Windowing/Windowing.h>
#include <MediaPool/MediaPool.h>
#include <ExportAudioMixdown/ExportAudioMixdown.h>
#include <FileIO/FileIO.h>
#include <Devices/Devices.h>
#include <Editors/Editors.h>
#include <AudioMaster/AudioMaster.h>
#include <PluginSDK/PluginSDK.h>
using namespace Upp;

namespace am {

// Struct definitions for preference types
struct AppearancePrefs : public Moveable<AppearancePrefs> {
	// Interface adjustments
	int saturation = 50;        // 0-100
	int brightness = 50;        // 0-100
	int button_brightness = 50; // 0-100
	
	// Add explicit copy constructor and assignment operator
	AppearancePrefs() = default;
	AppearancePrefs(const AppearancePrefs& other) 
		: saturation(other.saturation), 
		  brightness(other.brightness), 
		  button_brightness(other.button_brightness) {}
	
	AppearancePrefs& operator=(const AppearancePrefs& other) {
		if(this != &other) {
			saturation = other.saturation;
			brightness = other.brightness;
			button_brightness = other.button_brightness;
		}
		return *this;
	}
};

struct EditingPrefs : public Moveable<EditingPrefs> {
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
	
	// Event colors
	bool color_events_by_track = true;
	bool color_events_by_type = false;
	bool color_events_by_velocity = false;
	
	// Add explicit copy constructor and assignment operator
	EditingPrefs() = default;
	EditingPrefs(const EditingPrefs& other) 
		: default_track_time_type(other.default_track_time_type),
		  auto_select_under_cursor(other.auto_select_under_cursor),
		  cycle_follows_range(other.cycle_follows_range),
		  delete_overlaps(other.delete_overlaps),
		  link_editors(other.link_editors),
		  parts_get_track_names(other.parts_get_track_names),
		  quick_zoom(other.quick_zoom),
		  lock_event_attributes(other.lock_event_attributes),
		  drag_delay_ms(other.drag_delay_ms),
		  color_events_by_track(other.color_events_by_track),
		  color_events_by_type(other.color_events_by_type),
		  color_events_by_velocity(other.color_events_by_velocity) {}
	
	EditingPrefs& operator=(const EditingPrefs& other) {
		if(this != &other) {
			default_track_time_type = other.default_track_time_type;
			auto_select_under_cursor = other.auto_select_under_cursor;
			cycle_follows_range = other.cycle_follows_range;
			delete_overlaps = other.delete_overlaps;
			link_editors = other.link_editors;
			parts_get_track_names = other.parts_get_track_names;
			quick_zoom = other.quick_zoom;
			lock_event_attributes = other.lock_event_attributes;
			drag_delay_ms = other.drag_delay_ms;
			color_events_by_track = other.color_events_by_track;
			color_events_by_type = other.color_events_by_type;
			color_events_by_velocity = other.color_events_by_velocity;
		}
		return *this;
	}
};

struct EventDisplayPrefs : public Moveable<EventDisplayPrefs> {
	// Display density
	int display_density = 50; // 0-100
	
	// Zoom behavior
	bool zoom_to_selection = true;
	bool zoom_preserves_position = false;
	
	// Track height
	int default_track_height = 24; // pixels
	int minimum_track_height = 16; // pixels
	int maximum_track_height = 64; // pixels
	
	// Lane display
	bool show_track_lanes = true;
	bool show_midi_lanes = true;
	bool show_audio_lanes = true;
	bool show_video_lanes = true;
	bool show_marker_lanes = true;
	bool show_tempo_lanes = true;
	
	// Add explicit copy constructor and assignment operator
	EventDisplayPrefs() = default;
	EventDisplayPrefs(const EventDisplayPrefs& other) 
		: display_density(other.display_density),
		  zoom_to_selection(other.zoom_to_selection),
		  zoom_preserves_position(other.zoom_preserves_position),
		  default_track_height(other.default_track_height),
		  minimum_track_height(other.minimum_track_height),
		  maximum_track_height(other.maximum_track_height),
		  show_track_lanes(other.show_track_lanes),
		  show_midi_lanes(other.show_midi_lanes),
		  show_audio_lanes(other.show_audio_lanes),
		  show_video_lanes(other.show_video_lanes),
		  show_marker_lanes(other.show_marker_lanes),
		  show_tempo_lanes(other.show_tempo_lanes) {}
	
	EventDisplayPrefs& operator=(const EventDisplayPrefs& other) {
		if(this != &other) {
			display_density = other.display_density;
			zoom_to_selection = other.zoom_to_selection;
			zoom_preserves_position = other.zoom_preserves_position;
			default_track_height = other.default_track_height;
			minimum_track_height = other.minimum_track_height;
			maximum_track_height = other.maximum_track_height;
			show_track_lanes = other.show_track_lanes;
			show_midi_lanes = other.show_midi_lanes;
			show_audio_lanes = other.show_audio_lanes;
			show_video_lanes = other.show_video_lanes;
			show_marker_lanes = other.show_marker_lanes;
			show_tempo_lanes = other.show_tempo_lanes;
		}
		return *this;
	}
};

struct GeneralPrefs : public Moveable<GeneralPrefs> {
	// Startup
	bool auto_load_last_project = true;
	bool show_splash_screen = true;
	
	// Updates
	bool check_for_updates = true;
	bool auto_install_updates = false;
	
	// Undo
	int undo_levels = 50; // Number of undo levels to maintain
	
	// Localization
	String language = "en-US"; // Default language
	
	// Additional members
	int max_backup_files = 10;
	bool show_tips = true;
	int max_undo = -1; // Infinite
	bool run_setup_on_new = false;
	String on_startup = "show_open_dialog";
	bool usage_profile = false;
	
	// Add explicit copy constructor and assignment operator
	GeneralPrefs() = default;
	GeneralPrefs(const GeneralPrefs& other) 
		: auto_load_last_project(other.auto_load_last_project),
		  show_splash_screen(other.show_splash_screen),
		  check_for_updates(other.check_for_updates),
		  auto_install_updates(other.auto_install_updates),
		  undo_levels(other.undo_levels),
		  language(other.language),
		  max_backup_files(other.max_backup_files),
		  show_tips(other.show_tips),
		  max_undo(other.max_undo),
		  run_setup_on_new(other.run_setup_on_new),
		  on_startup(other.on_startup),
		  usage_profile(other.usage_profile) {}
	
	GeneralPrefs& operator=(const GeneralPrefs& other) {
		if(this != &other) {
			auto_load_last_project = other.auto_load_last_project;
			show_splash_screen = other.show_splash_screen;
			check_for_updates = other.check_for_updates;
			auto_install_updates = other.auto_install_updates;
			undo_levels = other.undo_levels;
			language = other.language;
			max_backup_files = other.max_backup_files;
			show_tips = other.show_tips;
			max_undo = other.max_undo;
			run_setup_on_new = other.run_setup_on_new;
			on_startup = other.on_startup;
			usage_profile = other.usage_profile;
		}
		return *this;
	}
};

struct MIDIPrefs : public Moveable<MIDIPrefs> {
	// Defaults
	int default_velocity = 64; // 0-127
	bool default_note_overlap_protection = true;
	
	// Behavior
	bool auto_quantize_on_record = false;
	bool auto_quantize_on_paste = false;
	bool auto_quantize_on_import = false;
	
	// Editor
	bool show_velocity_colors = true;
	bool show_note_names = true;
	bool snap_to_grid = true;
	
	// Real-time behavior
	bool thru_active = true;
	bool reset_on_stop = false;
	int length_adjust_ticks = -2;
	
	// Chase settings
	struct {
		bool note = true;
		bool poly_pressure = true;
		bool controller = true;
		bool prog_change = true;
		bool aftertouch = true;
		bool pitchbend = true;
		bool sysex = false;
		bool ignore_part_bounds = true;
	} chase;
	
	// Timing
	int ppq_base = 480;
	int display_res_1_16_ticks = 120;
	bool insert_reset_after_record = false;
	bool audition_through_inserts = false;
	int max_feedback_ms = 250;
	
	// Add explicit copy constructor and assignment operator
	MIDIPrefs() = default;
	MIDIPrefs(const MIDIPrefs& other) 
		: default_velocity(other.default_velocity),
		  default_note_overlap_protection(other.default_note_overlap_protection),
		  auto_quantize_on_record(other.auto_quantize_on_record),
		  auto_quantize_on_paste(other.auto_quantize_on_paste),
		  auto_quantize_on_import(other.auto_quantize_on_import),
		  show_velocity_colors(other.show_velocity_colors),
		  show_note_names(other.show_note_names),
		  snap_to_grid(other.snap_to_grid),
		  thru_active(other.thru_active),
		  reset_on_stop(other.reset_on_stop),
		  length_adjust_ticks(other.length_adjust_ticks),
		  chase(other.chase),
		  ppq_base(other.ppq_base),
		  display_res_1_16_ticks(other.display_res_1_16_ticks),
		  insert_reset_after_record(other.insert_reset_after_record),
		  audition_through_inserts(other.audition_through_inserts),
		  max_feedback_ms(other.max_feedback_ms) {}
	
	MIDIPrefs& operator=(const MIDIPrefs& other) {
		if(this != &other) {
			default_velocity = other.default_velocity;
			default_note_overlap_protection = other.default_note_overlap_protection;
			auto_quantize_on_record = other.auto_quantize_on_record;
			auto_quantize_on_paste = other.auto_quantize_on_paste;
			auto_quantize_on_import = other.auto_quantize_on_import;
			show_velocity_colors = other.show_velocity_colors;
			show_note_names = other.show_note_names;
			snap_to_grid = other.snap_to_grid;
			thru_active = other.thru_active;
			reset_on_stop = other.reset_on_stop;
			length_adjust_ticks = other.length_adjust_ticks;
			chase = other.chase;
			ppq_base = other.ppq_base;
			display_res_1_16_ticks = other.display_res_1_16_ticks;
			insert_reset_after_record = other.insert_reset_after_record;
			audition_through_inserts = other.audition_through_inserts;
			max_feedback_ms = other.max_feedback_ms;
		}
		return *this;
	}
};

struct MediaBayPrefs : public Moveable<MediaBayPrefs> {
	// Display
	bool show_preview = true;
	bool show_thumbnails = true;
	bool show_details = true;
	
	// Search
	bool search_in_subfolders = true;
	bool search_metadata = true;
	
	// Organization
	bool auto_tag_imported_files = true;
	bool auto_conform_audio_files = true;
	
	// Advanced
	int max_results = 100000;
	bool allow_edit = false;
	bool stop_scan_on_close = true;
	bool show_extensions = false;
	
	// Add explicit copy constructor and assignment operator
	MediaBayPrefs() = default;
	MediaBayPrefs(const MediaBayPrefs& other) 
		: show_preview(other.show_preview),
		  show_thumbnails(other.show_thumbnails),
		  show_details(other.show_details),
		  search_in_subfolders(other.search_in_subfolders),
		  search_metadata(other.search_metadata),
		  auto_tag_imported_files(other.auto_tag_imported_files),
		  auto_conform_audio_files(other.auto_conform_audio_files),
		  max_results(other.max_results),
		  allow_edit(other.allow_edit),
		  stop_scan_on_close(other.stop_scan_on_close),
		  show_extensions(other.show_extensions) {}
	
	MediaBayPrefs& operator=(const MediaBayPrefs& other) {
		if(this != &other) {
			show_preview = other.show_preview;
			show_thumbnails = other.show_thumbnails;
			show_details = other.show_details;
			search_in_subfolders = other.search_in_subfolders;
			search_metadata = other.search_metadata;
			auto_tag_imported_files = other.auto_tag_imported_files;
			auto_conform_audio_files = other.auto_conform_audio_files;
			max_results = other.max_results;
			allow_edit = other.allow_edit;
			stop_scan_on_close = other.stop_scan_on_close;
			show_extensions = other.show_extensions;
		}
		return *this;
	}
};

struct RecordPrefs : public Moveable<RecordPrefs> {
	// Input monitoring
	bool input_monitoring = true;
	bool software_monitoring = false;
	
	// Count-in
	bool enable_count_in = true;
	int count_in_measures = 2;
	
	// Punch-in/out
	bool auto_punch_in = false;
	bool auto_punch_out = false;
	bool use_punch_points = true;
	
	// Recording behavior
	double pre_record_seconds = 1.0;
	bool create_images_during_record = true;
	String cycle_record_mode = "create_events_regions"; // { create_events_regions | overwrite_existing | extend_existing }
	
	// File info
	String descriptor = "MasterLab";
	String author = "MasterLab";
	String reference = "";
	
	// Behavior
	bool snap_parts_to_bars = true;
	bool solo_record_in_editors = true;
	int catch_range_ms = 0;
	bool retrospective_record = true;
	int retro_buffer_events = 10000;
	String replace_recording_in_editors = "none"; // { none | selected | all }
	
	// Add explicit copy constructor and assignment operator
	RecordPrefs() = default;
	RecordPrefs(const RecordPrefs& other) 
		: input_monitoring(other.input_monitoring),
		  software_monitoring(other.software_monitoring),
		  enable_count_in(other.enable_count_in),
		  count_in_measures(other.count_in_measures),
		  auto_punch_in(other.auto_punch_in),
		  auto_punch_out(other.auto_punch_out),
		  use_punch_points(other.use_punch_points),
		  pre_record_seconds(other.pre_record_seconds),
		  create_images_during_record(other.create_images_during_record),
		  cycle_record_mode(other.cycle_record_mode),
		  descriptor(other.descriptor),
		  author(other.author),
		  reference(other.reference),
		  snap_parts_to_bars(other.snap_parts_to_bars),
		  solo_record_in_editors(other.solo_record_in_editors),
		  catch_range_ms(other.catch_range_ms),
		  retrospective_record(other.retrospective_record),
		  retro_buffer_events(other.retro_buffer_events),
		  replace_recording_in_editors(other.replace_recording_in_editors) {}
	
	RecordPrefs& operator=(const RecordPrefs& other) {
		if(this != &other) {
			input_monitoring = other.input_monitoring;
			software_monitoring = other.software_monitoring;
			enable_count_in = other.enable_count_in;
			count_in_measures = other.count_in_measures;
			auto_punch_in = other.auto_punch_in;
			auto_punch_out = other.auto_punch_out;
			use_punch_points = other.use_punch_points;
			pre_record_seconds = other.pre_record_seconds;
			create_images_during_record = other.create_images_during_record;
			cycle_record_mode = other.cycle_record_mode;
			descriptor = other.descriptor;
			author = other.author;
			reference = other.reference;
			snap_parts_to_bars = other.snap_parts_to_bars;
			solo_record_in_editors = other.solo_record_in_editors;
			catch_range_ms = other.catch_range_ms;
			retrospective_record = other.retrospective_record;
			retro_buffer_events = other.retro_buffer_events;
			replace_recording_in_editors = other.replace_recording_in_editors;
		}
		return *this;
	}
};

struct ScoresPrefs : public Moveable<ScoresPrefs> {
	// Display
	bool show_page_view = true;
	bool show_scroll_view = false;
	bool show_keyboard_view = false;
	
	// Notation
	bool auto_beam_notes = true;
	bool show_accidentals = true;
	bool use_standard_notation = true;
	
	// Playback
	bool play_notes_as_you_edit = false;
	bool highlight_played_notes = true;
	
	// Add explicit copy constructor and assignment operator
	ScoresPrefs() = default;
	ScoresPrefs(const ScoresPrefs& other) 
		: show_page_view(other.show_page_view),
		  show_scroll_view(other.show_scroll_view),
		  show_keyboard_view(other.show_keyboard_view),
		  auto_beam_notes(other.auto_beam_notes),
		  show_accidentals(other.show_accidentals),
		  use_standard_notation(other.use_standard_notation),
		  play_notes_as_you_edit(other.play_notes_as_you_edit),
		  highlight_played_notes(other.highlight_played_notes) {}
	
	ScoresPrefs& operator=(const ScoresPrefs& other) {
		if(this != &other) {
			show_page_view = other.show_page_view;
			show_scroll_view = other.show_scroll_view;
			show_keyboard_view = other.show_keyboard_view;
			auto_beam_notes = other.auto_beam_notes;
			show_accidentals = other.show_accidentals;
			use_standard_notation = other.use_standard_notation;
			play_notes_as_you_edit = other.play_notes_as_you_edit;
			highlight_played_notes = other.highlight_played_notes;
		}
		return *this;
	}
};

struct TransportPrefs : public Moveable<TransportPrefs> {
	// Display
	bool show_transport = true;
	bool show_time_display = true;
	bool show_locator = true;
	
	// Behavior
	bool auto_return_to_start = true;
	bool stop_at_end_of_loop = false;
	bool stop_on_lost_focus = false;
	
	// Advanced behavior
	bool playback_toggle_preview = false;
	bool zoom_while_locating = false;
	int cursor_width = 3;
	bool return_to_start = false;
	bool deactivate_punch_on_stop = false;
	bool stop_after_auto_punch = false;
	bool stop_while_winding = false;
	String wind_mode = "adjust_to_zoom"; // { adjust_to_zoom | constant_speed }
	double speed_factor = 1;
	double fast_wind_factor = 10;
	bool show_timecode_subframes = false;
	int user_framerate = 30;
	bool stationary_cursor = false;
	bool locate_on_empty_click = false;
	
	// Scrubbing
	struct {
		int response = 50; // 0-100
		int volume = 50; // 0-100
		bool cpu_saving = false;
	} scrub;
	
	// Add explicit copy constructor and assignment operator
	TransportPrefs() = default;
	TransportPrefs(const TransportPrefs& other) 
		: show_transport(other.show_transport),
		  show_time_display(other.show_time_display),
		  show_locator(other.show_locator),
		  auto_return_to_start(other.auto_return_to_start),
		  stop_at_end_of_loop(other.stop_at_end_of_loop),
		  stop_on_lost_focus(other.stop_on_lost_focus),
		  playback_toggle_preview(other.playback_toggle_preview),
		  zoom_while_locating(other.zoom_while_locating),
		  cursor_width(other.cursor_width),
		  return_to_start(other.return_to_start),
		  deactivate_punch_on_stop(other.deactivate_punch_on_stop),
		  stop_after_auto_punch(other.stop_after_auto_punch),
		  stop_while_winding(other.stop_while_winding),
		  wind_mode(other.wind_mode),
		  speed_factor(other.speed_factor),
		  fast_wind_factor(other.fast_wind_factor),
		  show_timecode_subframes(other.show_timecode_subframes),
		  user_framerate(other.user_framerate),
		  stationary_cursor(other.stationary_cursor),
		  locate_on_empty_click(other.locate_on_empty_click),
		  scrub(other.scrub) {}
	
	TransportPrefs& operator=(const TransportPrefs& other) {
		if(this != &other) {
			show_transport = other.show_transport;
			show_time_display = other.show_time_display;
			show_locator = other.show_locator;
			auto_return_to_start = other.auto_return_to_start;
			stop_at_end_of_loop = other.stop_at_end_of_loop;
			stop_on_lost_focus = other.stop_on_lost_focus;
			playback_toggle_preview = other.playback_toggle_preview;
			zoom_while_locating = other.zoom_while_locating;
			cursor_width = other.cursor_width;
			return_to_start = other.return_to_start;
			deactivate_punch_on_stop = other.deactivate_punch_on_stop;
			stop_after_auto_punch = other.stop_after_auto_punch;
			stop_while_winding = other.stop_while_winding;
			wind_mode = other.wind_mode;
			speed_factor = other.speed_factor;
			fast_wind_factor = other.fast_wind_factor;
			show_timecode_subframes = other.show_timecode_subframes;
			user_framerate = other.user_framerate;
			stationary_cursor = other.stationary_cursor;
			locate_on_empty_click = other.locate_on_empty_click;
			scrub = other.scrub;
		}
		return *this;
	}
};

struct VSTPrefs : public Moveable<VSTPrefs> {
	// Scanning
	bool scan_vst_on_startup = true;
	bool scan_vst_periodically = false;
	
	// Processing
	bool process_vst_in_separate_thread = true;
	int vst_buffer_size = 512; // samples
	
	// Compatibility
	bool enable_vst_bridge = false;
	bool use_vst_compatibility_mode = false;
	
	// Connection behavior
	bool connect_sends_auto = true;
	bool instr_use_automation_rw_all = true;
	bool mute_pre_send_on_mute = true;
	bool group_channels_mute_sources = true;
	double delay_comp_threshold_ms = 10.0;
	bool export_warnings_as_text = false;
	bool use_cubase3_eq_as_default = false;
	String default_stereo_panner = "dual"; // { dual | stereo_link }
	bool link_send_panners = true;
	String auto_monitoring = "manual"; // { manual | auto }
	bool warn_overloads = true;
	
	// Plugin management
	bool warn_before_remove_modified = true;
	bool open_editor_after_load = true;
	String create_midi_track_policy = "ask"; // { ask | always | never }
	bool suspend_vst3_when_silent = true;
	bool sort_menu_by_vendor = true;
	bool plugin_editor_always_on_top = true;
	
	// Performance
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
	
	// Add explicit copy constructor and assignment operator
	VSTPrefs() = default;
	VSTPrefs(const VSTPrefs& other) 
		: scan_vst_on_startup(other.scan_vst_on_startup),
		  scan_vst_periodically(other.scan_vst_periodically),
		  process_vst_in_separate_thread(other.process_vst_in_separate_thread),
		  vst_buffer_size(other.vst_buffer_size),
		  enable_vst_bridge(other.enable_vst_bridge),
		  use_vst_compatibility_mode(other.use_vst_compatibility_mode),
		  connect_sends_auto(other.connect_sends_auto),
		  instr_use_automation_rw_all(other.instr_use_automation_rw_all),
		  mute_pre_send_on_mute(other.mute_pre_send_on_mute),
		  group_channels_mute_sources(other.group_channels_mute_sources),
		  delay_comp_threshold_ms(other.delay_comp_threshold_ms),
		  export_warnings_as_text(other.export_warnings_as_text),
		  use_cubase3_eq_as_default(other.use_cubase3_eq_as_default),
		  default_stereo_panner(other.default_stereo_panner),
		  link_send_panners(other.link_send_panners),
		  auto_monitoring(other.auto_monitoring),
		  warn_overloads(other.warn_overloads),
		  warn_before_remove_modified(other.warn_before_remove_modified),
		  open_editor_after_load(other.open_editor_after_load),
		  create_midi_track_policy(other.create_midi_track_policy),
		  suspend_vst3_when_silent(other.suspend_vst3_when_silent),
		  sort_menu_by_vendor(other.sort_menu_by_vendor),
		  plugin_editor_always_on_top(other.plugin_editor_always_on_top),
		  peak_hold_ms(other.peak_hold_ms),
		  slow_fallback_dbps(other.slow_fallback_dbps),
		  fast_fallback_dbps(other.fast_fallback_dbps),
		  map_inputbus_to_track(other.map_inputbus_to_track),
		  show_volume_in_transport(other.show_volume_in_transport),
		  disable_talkback(other.disable_talkback),
		  phones_as_preview(other.phones_as_preview),
		  dim_studio(other.dim_studio),
		  signal_presence(other.signal_presence),
		  multi_channel_solo(other.multi_channel_solo),
		  show_downmix_presets(other.show_downmix_presets),
		  metronome_in_studio(other.metronome_in_studio),
		  metronome_in_control_room(other.metronome_in_control_room),
		  show_reference_level(other.show_reference_level),
		  reference_level_db(other.reference_level_db),
		  max_dim_db(other.max_dim_db) {}
	
	VSTPrefs& operator=(const VSTPrefs& other) {
		if(this != &other) {
			scan_vst_on_startup = other.scan_vst_on_startup;
			scan_vst_periodically = other.scan_vst_periodically;
			process_vst_in_separate_thread = other.process_vst_in_separate_thread;
			vst_buffer_size = other.vst_buffer_size;
			enable_vst_bridge = other.enable_vst_bridge;
			use_vst_compatibility_mode = other.use_vst_compatibility_mode;
			connect_sends_auto = other.connect_sends_auto;
			instr_use_automation_rw_all = other.instr_use_automation_rw_all;
			mute_pre_send_on_mute = other.mute_pre_send_on_mute;
			group_channels_mute_sources = other.group_channels_mute_sources;
			delay_comp_threshold_ms = other.delay_comp_threshold_ms;
			export_warnings_as_text = other.export_warnings_as_text;
			use_cubase3_eq_as_default = other.use_cubase3_eq_as_default;
			default_stereo_panner = other.default_stereo_panner;
			link_send_panners = other.link_send_panners;
			auto_monitoring = other.auto_monitoring;
			warn_overloads = other.warn_overloads;
			warn_before_remove_modified = other.warn_before_remove_modified;
			open_editor_after_load = other.open_editor_after_load;
			create_midi_track_policy = other.create_midi_track_policy;
			suspend_vst3_when_silent = other.suspend_vst3_when_silent;
			sort_menu_by_vendor = other.sort_menu_by_vendor;
			plugin_editor_always_on_top = other.plugin_editor_always_on_top;
			peak_hold_ms = other.peak_hold_ms;
			slow_fallback_dbps = other.slow_fallback_dbps;
			fast_fallback_dbps = other.fast_fallback_dbps;
			map_inputbus_to_track = other.map_inputbus_to_track;
			show_volume_in_transport = other.show_volume_in_transport;
			disable_talkback = other.disable_talkback;
			phones_as_preview = other.phones_as_preview;
			dim_studio = other.dim_studio;
			signal_presence = other.signal_presence;
			multi_channel_solo = other.multi_channel_solo;
			show_downmix_presets = other.show_downmix_presets;
			metronome_in_studio = other.metronome_in_studio;
			metronome_in_control_room = other.metronome_in_control_room;
			show_reference_level = other.show_reference_level;
			reference_level_db = other.reference_level_db;
			max_dim_db = other.max_dim_db;
		}
		return *this;
	}
};

struct VariAudioPrefs : public Moveable<VariAudioPrefs> {
	// Analysis
	bool auto_analyze_on_import = true;
	int analysis_granularity = 50; // 0-100
	
	// Processing
	bool preserve_formants = true;
	bool adaptive_pitch_tracking = true;
	
	// Display
	bool show_analysis_overlay = true;
	bool color_by_pitch_confidence = true;
	
	// Warnings
	bool inhibit_warn_change_sample = false;
	bool inhibit_warn_offline_process = false;
	
	// Add explicit copy constructor and assignment operator
	VariAudioPrefs() = default;
	VariAudioPrefs(const VariAudioPrefs& other) 
		: auto_analyze_on_import(other.auto_analyze_on_import),
		  analysis_granularity(other.analysis_granularity),
		  preserve_formants(other.preserve_formants),
		  adaptive_pitch_tracking(other.adaptive_pitch_tracking),
		  show_analysis_overlay(other.show_analysis_overlay),
		  color_by_pitch_confidence(other.color_by_pitch_confidence),
		  inhibit_warn_change_sample(other.inhibit_warn_change_sample),
		  inhibit_warn_offline_process(other.inhibit_warn_offline_process) {}
	
	VariAudioPrefs& operator=(const VariAudioPrefs& other) {
		if(this != &other) {
			auto_analyze_on_import = other.auto_analyze_on_import;
			analysis_granularity = other.analysis_granularity;
			preserve_formants = other.preserve_formants;
			adaptive_pitch_tracking = other.adaptive_pitch_tracking;
			show_analysis_overlay = other.show_analysis_overlay;
			color_by_pitch_confidence = other.color_by_pitch_confidence;
			inhibit_warn_change_sample = other.inhibit_warn_change_sample;
			inhibit_warn_offline_process = other.inhibit_warn_offline_process;
		}
		return *this;
	}
};

class PreferencesModel : public Moveable<PreferencesModel> {
public:
	PreferencesModel();
	
	// Model access
	AppearancePrefs& GetAppearance() { return appearance; }
	const AppearancePrefs& GetAppearance() const { return appearance; }
	EditingPrefs& GetEditing() { return editing; }
	const EditingPrefs& GetEditing() const { return editing; }
	EventDisplayPrefs& GetEventDisplay() { return event_display; }
	const EventDisplayPrefs& GetEventDisplay() const { return event_display; }
	GeneralPrefs& GetGeneral() { return general; }
	const GeneralPrefs& GetGeneral() const { return general; }
	MIDIPrefs& GetMIDI() { return midi; }
	const MIDIPrefs& GetMIDI() const { return midi; }
	MediaBayPrefs& GetMediaBay() { return mediabay; }
	const MediaBayPrefs& GetMediaBay() const { return mediabay; }
	RecordPrefs& GetRecord() { return record; }
	const RecordPrefs& GetRecord() const { return record; }
	ScoresPrefs& GetScores() { return scores; }
	const ScoresPrefs& GetScores() const { return scores; }
	TransportPrefs& GetTransport() { return transport; }
	const TransportPrefs& GetTransport() const { return transport; }
	VSTPrefs& GetVST() { return vst; }
	const VSTPrefs& GetVST() const { return vst; }
	VariAudioPrefs& GetVariAudio() { return variaudio; }
	const VariAudioPrefs& GetVariAudio() const { return variaudio; }
	
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

}

#endif