#include "ZenCoreWorkstation.h"

#include <cmath>
#include <cstring>

namespace Instruments {

namespace {
constexpr double kTwoPi = 6.283185307179586476925286766559;

int AddParameter(PluginSDK::ParameterSet& params, const String& id, const String& name,
	double min, double max, double def, bool automatable = true) {
	PluginSDK::ParameterDescriptor desc;
	desc.id = id;
	desc.name = name;
	desc.min = min;
	desc.max = max;
	desc.default_value = def;
	desc.automatable = automatable;
	return params.Add(desc);
}
} // namespace

ZenCoreWorkstation::ZenCoreWorkstation() {
	SetupPartials();
	SetupDrumLanes();
	SetupMotionDesigner();
	SetupSceneMacros();
	RegisterParameters();
	BuildRouting();
	BuildGraph();
	UpdateGraphActivity();
}

void ZenCoreWorkstation::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	voice_manager.Configure(kMaxVoices);
	voice_manager.AllNotesOff();
	active_voices.Clear();
	AdvanceMotionLanes(0.0);
	RefreshVoiceGains();
	UpdateGraphActivity();
}

void ZenCoreWorkstation::Reset() {
	PluginSDK::PluginProcessor::Reset();
	voice_manager.AllNotesOff();
	active_voices.Clear();
	for(MotionLane& lane : motion_lanes) {
		lane.phase = 0.0;
		lane.last_value = 0.0;
	}
	AdvanceMotionLanes(0.0);
	UpdateGraphActivity();
}

void ZenCoreWorkstation::Process(PluginSDK::ProcessContext& ctx) {
	const int frames = ctx.frames;
	double delta_seconds = 0.0;
	if(current_config.sample_rate > 0 && frames > 0)
		delta_seconds = (double)frames / (double)current_config.sample_rate;

	AdvanceMotionLanes(delta_seconds);
	UpdateGraphActivity();
	RefreshVoiceGains();

	// Placeholder audio rendering: silence output while maintaining voice bookkeeping.
	if(ctx.output.IsValid()) {
		for(int ch = 0; ch < ctx.output.channel_count; ++ch) {
			float* buffer = ctx.output.GetChannel(ch);
			if(!buffer)
				continue;
			memset(buffer, 0, sizeof(float) * frames);
		}
	}
	(void)ctx;
}

void ZenCoreWorkstation::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	double velocity = Upp::Clamp(evt.velocity / 127.0, 0.0, 1.0);
	voice_manager.NoteOn(evt.note, velocity);
	RefreshVoiceGains();
}

void ZenCoreWorkstation::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	voice_manager.NoteOff(evt.note);
	RefreshVoiceGains();
}

void ZenCoreWorkstation::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	voice_manager.AllNotesOff();
	active_voices.Clear();
}

void ZenCoreWorkstation::SetupPartials() {
	partials.Clear();
	static const char* ids[] = { "A", "B", "C", "D" };
	for(int i = 0; i < kPartialCount; ++i) {
		PartialSlot slot;
		slot.id = ids[i];
		slot.node_id = Format("Partial.%s", ids[i]);
		slot.ifx_node_id = Format("IFX.%s", ids[i]);
		partials.Add(pick(slot));
	}
}

void ZenCoreWorkstation::SetupDrumLanes() {
	drum_lanes.Clear();
	for(int i = 0; i < kDrumPadCount; ++i) {
		DrumLane lane;
		lane.id = Format("Pad%02d", i + 1);
		drum_lanes.Add(pick(lane));
	}
}

void ZenCoreWorkstation::SetupMotionDesigner() {
	motion_lanes.Clear();
	for(int i = 0; i < kMotionLaneCount; ++i) {
		MotionLane lane;
		lane.id = Format("L%d", i + 1);
		lane.node_id = Format("Motion.%d", i + 1);
		motion_lanes.Add(pick(lane));
	}
}

void ZenCoreWorkstation::SetupSceneMacros() {
	scene_macros.Clear();
	for(int i = 0; i < kMacroCount; ++i) {
		SceneMacro macro;
		macro.id = Format("M%d", i + 1);
		macro.node_id = Format("Macro.%d", i + 1);
		scene_macros.Add(pick(macro));
	}
}

void ZenCoreWorkstation::RegisterParameters() {
	PluginSDK::ParameterSet& params = Parameters();

	engine_mode_param = AddParameter(params, "engine_mode", "Engine Mode (0: Tone, 1: Drum)", 0.0, 1.0, 0.0, false);
	morph_param = AddParameter(params, "scene_morph", "Scene Morph", 0.0, 1.0, 0.0);
	scene_blend_param = AddParameter(params, "scene_blend", "Scene Blend", 0.0, 1.0, 0.5);

	for(PartialSlot& slot : partials) {
		slot.enable_param = AddParameter(params, Format("partial%s_enable", slot.id), Format("Partial %s Enable", slot.id), 0.0, 1.0, 1.0);
		slot.level_param = AddParameter(params, Format("partial%s_level", slot.id), Format("Partial %s Level", slot.id), 0.0, 1.0, 0.75);
		slot.cutoff_param = AddParameter(params, Format("partial%s_cutoff", slot.id), Format("Partial %s Cutoff", slot.id), 0.0, 1.0, 0.5);
		slot.resonance_param = AddParameter(params, Format("partial%s_resonance", slot.id), Format("Partial %s Resonance", slot.id), 0.0, 1.0, 0.1);
		slot.coarse_param = AddParameter(params, Format("partial%s_coarse", slot.id), Format("Partial %s Coarse Tune", slot.id), -24.0, 24.0, 0.0);
		slot.fine_param = AddParameter(params, Format("partial%s_fine", slot.id), Format("Partial %s Fine Tune", slot.id), -100.0, 100.0, 0.0);
		slot.ifx_send_param = AddParameter(params, Format("partial%s_ifx_send", slot.id), Format("Partial %s IFX Send", slot.id), 0.0, 1.0, 0.5);
	}

	for(MotionLane& lane : motion_lanes) {
		lane.rate_param = AddParameter(params, Format("motion%s_rate", lane.id), Format("Motion %s Rate", lane.id), 0.0, 1.0, 0.25);
		lane.depth_param = AddParameter(params, Format("motion%s_depth", lane.id), Format("Motion %s Depth", lane.id), 0.0, 1.0, 0.0);
		lane.probability_param = AddParameter(params, Format("motion%s_probability", lane.id), Format("Motion %s Probability", lane.id), 0.0, 1.0, 1.0);
	}

	for(SceneMacro& macro : scene_macros) {
		macro.param = AddParameter(params, Format("macro%s_amount", macro.id), Format("Macro %s Amount", macro.id), 0.0, 1.0, 0.0);
	}

	for(DrumLane& lane : drum_lanes) {
		lane.level_param = AddParameter(params, Format("drum%s_level", lane.id), Format("%s Level", lane.id), 0.0, 1.0, 0.7);
		lane.pan_param = AddParameter(params, Format("drum%s_pan", lane.id), Format("%s Pan", lane.id), -1.0, 1.0, 0.0);
		lane.attack_param = AddParameter(params, Format("drum%s_attack", lane.id), Format("%s Attack", lane.id), 0.0, 1.0, 0.1);
		lane.decay_param = AddParameter(params, Format("drum%s_decay", lane.id), Format("%s Decay", lane.id), 0.0, 1.0, 0.5);
		lane.release_param = AddParameter(params, Format("drum%s_release", lane.id), Format("%s Release", lane.id), 0.0, 1.0, 0.5);
	}
}

void ZenCoreWorkstation::BuildRouting() {
	routing = PluginSDK::RoutingMap();
	for(const PartialSlot& slot : partials) {
		routing.Add("Tone.In", slot.node_id);
		routing.Add(slot.node_id, slot.ifx_node_id);
		routing.Add(slot.ifx_node_id, "Scene.MFX");
	}
	routing.Add("Scene.MFX", "Scene.TFX");
	routing.Add("Scene.TFX", "Output");
	routing.Add("Tone.In", "DrumKit");
	routing.Add("DrumKit", "Scene.MFX");
}

void ZenCoreWorkstation::BuildGraph() {
	PluginSDK::GraphVisualization& g = Graph();
	g.Clear();

	auto add_node = [&](const String& id, const String& label, const String& group) {
		PluginSDK::GraphNode& node = g.nodes.Add();
		node.id = id;
		node.label = label;
		node.group = group;
		return g.nodes.GetCount() - 1;
	};

	auto add_audio_edge = [&](const String& from, const String& to) {
		PluginSDK::GraphEdge& edge = g.edges.Add();
		edge.from = from;
		edge.to = to;
		edge.audio = true;
		edge.control = false;
		edge.active = true;
		return g.edges.GetCount() - 1;
	};

	auto add_control_edge = [&](const String& from, const String& to) {
		PluginSDK::GraphEdge& edge = g.edges.Add();
		edge.from = from;
		edge.to = to;
		edge.audio = false;
		edge.control = true;
		edge.active = true;
		return g.edges.GetCount() - 1;
	};

	add_node("Tone.In", "Tone In", "Voice");
	add_node("CrossMod.Bus", "Cross Mod Bus", "Voice");
	add_node("Scene.MFX", "Scene MFX", "FX");
	add_node("Scene.TFX", "Scene TFX", "FX");
	add_node("Output", "Output", "IO");
	add_node("DrumKit", "Drum Kit Engine", "Drum");
	add_node("MotionDesigner", "Motion Designer", "Mod");
	add_node("MacroMorph", "Macro Morph", "Macro");
	add_node("MacroSurface", "Macro Surface", "Macro");

	for(MotionLane& lane : motion_lanes) {
		add_node(lane.node_id, Format("Motion %s", lane.id), "Mod");
		lane.control_edges.Clear();
		lane.control_edges.Add(add_control_edge("MotionDesigner", lane.node_id));
	}

	for(SceneMacro& macro : scene_macros) {
		add_node(macro.node_id, Format("Macro %s", macro.id), "Macro");
		macro.control_edges.Clear();
		macro.control_edges.Add(add_control_edge("MacroSurface", macro.node_id));
	}

	for(PartialSlot& slot : partials) {
		add_node(slot.node_id, Format("Partial %s", slot.id), "Voice");
		add_node(slot.ifx_node_id, Format("IFX %s", slot.id), "FX");
		slot.control_edges.Clear();
		slot.tone_edge = add_audio_edge("Tone.In", slot.node_id);
		slot.ifx_edge = add_audio_edge(slot.node_id, slot.ifx_node_id);
		slot.to_mfx_edge = add_audio_edge(slot.ifx_node_id, "Scene.MFX");
		slot.control_edges.Add(add_control_edge(slot.node_id, "CrossMod.Bus"));
		slot.control_edges.Add(add_control_edge("MacroMorph", slot.ifx_node_id));
		for(MotionLane& lane : motion_lanes) {
			int edge = add_control_edge(lane.node_id, slot.node_id);
			lane.control_edges.Add(edge);
			slot.control_edges.Add(edge);
		}
	}

	drum_edge = add_audio_edge("Tone.In", "DrumKit");
	drum_to_mfx_edge = add_audio_edge("DrumKit", "Scene.MFX");
	int mfx_to_tfx = add_audio_edge("Scene.MFX", "Scene.TFX");
	int tfx_to_out = add_audio_edge("Scene.TFX", "Output");
	(void)mfx_to_tfx;
	(void)tfx_to_out;

	motion_drive_edge = add_control_edge("MotionDesigner", "Scene.MFX");
	macro_drive_edge = add_control_edge("MacroMorph", "Scene.MFX");

	for(SceneMacro& macro : scene_macros) {
		int to_mfx = add_control_edge(macro.node_id, "Scene.MFX");
		int to_tfx = add_control_edge(macro.node_id, "Scene.TFX");
		macro.control_edges.Add(to_mfx);
		macro.control_edges.Add(to_tfx);
	}
}

void ZenCoreWorkstation::UpdateGraphActivity() {
	PluginSDK::GraphVisualization& g = Graph();
	if(g.edges.IsEmpty())
		return;

	bool drum_mode = GetParameterValue(engine_mode_param) > 0.5;
	if(drum_edge >= 0 && drum_edge < g.edges.GetCount())
		g.edges[drum_edge].active = drum_mode;
	if(drum_to_mfx_edge >= 0 && drum_to_mfx_edge < g.edges.GetCount())
		g.edges[drum_to_mfx_edge].active = drum_mode;

	for(PartialSlot& slot : partials) {
		bool enabled = GetParameterValue(slot.enable_param) > 0.5 && !drum_mode;
		if(slot.tone_edge >= 0 && slot.tone_edge < g.edges.GetCount())
			g.edges[slot.tone_edge].active = enabled;
		if(slot.ifx_edge >= 0 && slot.ifx_edge < g.edges.GetCount())
			g.edges[slot.ifx_edge].active = enabled;
		if(slot.to_mfx_edge >= 0 && slot.to_mfx_edge < g.edges.GetCount())
			g.edges[slot.to_mfx_edge].active = enabled;
		for(int idx : slot.control_edges) {
			if(idx >= 0 && idx < g.edges.GetCount())
				g.edges[idx].active = enabled;
		}
	}

	bool any_motion = false;
	for(MotionLane& lane : motion_lanes) {
		bool lane_active = GetParameterValue(lane.depth_param) > 0.001;
		any_motion = any_motion || lane_active;
		for(int idx : lane.control_edges) {
			if(idx >= 0 && idx < g.edges.GetCount())
				g.edges[idx].active = lane_active;
		}
	}
	if(motion_drive_edge >= 0 && motion_drive_edge < g.edges.GetCount())
		g.edges[motion_drive_edge].active = any_motion;

	bool any_macro = false;
	for(SceneMacro& macro : scene_macros) {
		bool macro_active = GetParameterValue(macro.param) > 0.001;
		any_macro = any_macro || macro_active;
		for(int idx : macro.control_edges) {
			if(idx >= 0 && idx < g.edges.GetCount())
				g.edges[idx].active = macro_active;
		}
	}
	if(macro_drive_edge >= 0 && macro_drive_edge < g.edges.GetCount())
		g.edges[macro_drive_edge].active = any_macro;
}

void ZenCoreWorkstation::AdvanceMotionLanes(double delta_seconds) {
	if(delta_seconds <= 0.0)
		return;

	for(MotionLane& lane : motion_lanes) {
		double rate = GetParameterValue(lane.rate_param);
		double depth = GetParameterValue(lane.depth_param);
		if(depth <= 0.0) {
			lane.last_value = 0.0;
			continue;
		}

		// Map rate control (0..1) to roughly 0..8 Hz
		double frequency = Upp::Clamp(rate, 0.0, 1.0) * 8.0;
		lane.phase += frequency * delta_seconds * kTwoPi;
		if(lane.phase > kTwoPi)
			lane.phase = std::fmod(lane.phase, kTwoPi);
		double probability = GetParameterValue(lane.probability_param);
		double raw = std::sin(lane.phase);
		lane.last_value = raw * depth * Upp::Clamp(probability, 0.0, 1.0);
	}
}

void ZenCoreWorkstation::RefreshVoiceGains() {
	bool drum_mode = GetParameterValue(engine_mode_param) > 0.5;
	double motion_sum = 0.0;
	for(const MotionLane& lane : motion_lanes)
		motion_sum += lane.last_value;
	double morph = GetParameterValue(morph_param);

	Vector<VoiceState> previous;
	previous <<= active_voices;
	Vector<VoiceState> updated;

	voice_manager.ForEachActive([&](am::Synth::VoiceHandle& handle) {
		VoiceState state;
		bool reused = false;
		for(const VoiceState& existing : previous) {
			if(existing.voice_id == handle.id) {
				state = existing;
				reused = true;
				break;
			}
		}
		state.voice_id = handle.id;
		state.note = handle.note;
		state.velocity = handle.velocity;
		state.releasing = handle.releasing;
		state.morph_position = morph;
		state.partial_gains.SetCount(partials.GetCount(), 0.0);

		if(!drum_mode) {
			for(int i = 0; i < partials.GetCount(); ++i) {
				const PartialSlot& slot = partials[i];
				bool enabled = GetParameterValue(slot.enable_param) > 0.5;
				if(!enabled)
					continue;
				double level = GetParameterValue(slot.level_param);
				double gain = state.velocity * Upp::Clamp(level + motion_sum * 0.1, 0.0, 1.0) * (1.0 - morph * 0.1);
				state.partial_gains[i] = gain;
			}
		}

		if(!reused && state.partial_gains.IsEmpty())
			state.partial_gains.SetCount(partials.GetCount(), 0.0);

		updated.Add(state);
	});

	active_voices = pick(updated);
}

double ZenCoreWorkstation::GetParameterValue(int index) const {
	if(index < 0)
		return 0.0;
	return Parameters().GetValue(index);
}

} // namespace Instruments
