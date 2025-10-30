#include "Preferences.h"
namespace am {

PreferencesModel::PreferencesModel() {
	// Initialize the model with default values
	LoadDefaults();
}

void PreferencesModel::LoadDefaults() {
	// Appearance defaults
	appearance.saturation = 50;
	appearance.brightness = 50;
	appearance.button_brightness = 50;
	
	// Editing defaults
	editing.default_track_time_type = "musical";
	editing.auto_select_under_cursor = false;
	editing.cycle_follows_range = false;
	editing.delete_overlaps = false;
	editing.link_editors = true;
	editing.parts_get_track_names = false;
	editing.quick_zoom = false;
	editing.lock_event_attributes = 0;
	editing.drag_delay_ms = 200;
	
	// Event display defaults
	event_display.display_density = 50;
	event_display.zoom_to_selection = true;
	event_display.zoom_preserves_position = false;
	event_display.default_track_height = 24;
	event_display.minimum_track_height = 16;
	event_display.maximum_track_height = 64;
	event_display.show_track_lanes = true;
	event_display.show_midi_lanes = true;
	event_display.show_audio_lanes = true;
	event_display.show_video_lanes = true;
	event_display.show_marker_lanes = true;
	event_display.show_tempo_lanes = true;
	general.auto_load_last_project = true;
	general.show_splash_screen = true;
	general.check_for_updates = true;
	general.auto_install_updates = false;
	general.undo_levels = 50;
	general.language = "en-US";
	general.max_backup_files = 10;
	general.show_tips = true;
	general.max_undo = -1; // Infinite
	general.run_setup_on_new = false;
	general.on_startup = "show_open_dialog";
	general.usage_profile = false;
	
	// MIDI defaults
	midi.default_velocity = 64;
	midi.default_note_overlap_protection = true;
	midi.auto_quantize_on_record = false;
	midi.auto_quantize_on_paste = false;
	midi.auto_quantize_on_import = false;
	midi.show_velocity_colors = true;
	midi.show_note_names = true;
	midi.snap_to_grid = true;
	midi.thru_active = true;
	midi.reset_on_stop = false;
	midi.length_adjust_ticks = -2;
	
	midi.chase.note = true;
	midi.chase.poly_pressure = true;
	midi.chase.controller = true;
	midi.chase.ignore_part_bounds = true;
	midi.chase.prog_change = true;
	midi.chase.aftertouch = true;
	midi.chase.pitchbend = true;
	midi.chase.sysex = false;
	
	midi.ppq_base = 480;
	midi.display_res_1_16_ticks = 120;
	
	midi.insert_reset_after_record = false;
	midi.audition_through_inserts = false;
	midi.max_feedback_ms = 250;
	
	// MediaBay defaults
	mediabay.max_results = 100000;
	mediabay.allow_edit = false;
	mediabay.stop_scan_on_close = true;
	mediabay.show_extensions = false;
	
	// Record defaults
	record.pre_record_seconds = 1.0;
	record.create_images_during_record = true;
	record.cycle_record_mode = "create_events_regions";
	
	record.descriptor = "MasterLab";
	record.author = "MasterLab";
	record.reference = "";
	
	record.snap_parts_to_bars = true;
	record.solo_record_in_editors = true;
	record.catch_range_ms = 0;
	record.retrospective_record = true;
	record.retro_buffer_events = 10000;
	record.replace_recording_in_editors = "none";
	
	// Transport defaults
	transport.playback_toggle_preview = false;
	transport.zoom_while_locating = false;
	transport.cursor_width = 3;
	transport.return_to_start = false;
	transport.deactivate_punch_on_stop = false;
	transport.stop_after_auto_punch = false;
	transport.stop_while_winding = false;
	transport.wind_mode = "adjust_to_zoom";
	transport.speed_factor = 1;
	transport.fast_wind_factor = 10;
	transport.show_timecode_subframes = false;
	transport.user_framerate = 30;
	transport.stationary_cursor = false;
	transport.locate_on_empty_click = false;
	
	transport.scrub.response = 50;
	transport.scrub.volume = 50;
	transport.scrub.cpu_saving = false;
	
	// VST defaults
	vst.connect_sends_auto = true;
	vst.instr_use_automation_rw_all = true;
	vst.mute_pre_send_on_mute = true;
	vst.group_channels_mute_sources = true;
	vst.delay_comp_threshold_ms = 10.0;
	vst.export_warnings_as_text = false;
	vst.use_cubase3_eq_as_default = false;
	vst.default_stereo_panner = "dual";
	vst.link_send_panners = true;
	vst.auto_monitoring = "manual";
	vst.warn_overloads = true;
	
	vst.warn_before_remove_modified = true;
	vst.open_editor_after_load = true;
	vst.create_midi_track_policy = "ask";
	vst.suspend_vst3_when_silent = true;
	vst.sort_menu_by_vendor = true;
	vst.plugin_editor_always_on_top = true;
	
	vst.peak_hold_ms = 5000;
	vst.slow_fallback_dbps = 10;
	vst.fast_fallback_dbps = 100;
	vst.map_inputbus_to_track = true;
	
	vst.show_volume_in_transport = true;
	vst.disable_talkback = false;
	vst.phones_as_preview = false;
	vst.dim_studio = false;
	vst.signal_presence = false;
	vst.multi_channel_solo = false;
	vst.show_downmix_presets = false;
	vst.metronome_in_studio = false;
	vst.metronome_in_control_room = false;
	vst.show_reference_level = false;
	vst.reference_level_db = -18.0;
	vst.max_dim_db = 20.0;
	
	// VariAudio defaults
	variaudio.inhibit_warn_change_sample = false;
	variaudio.inhibit_warn_offline_process = false;
}

}