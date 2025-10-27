#include "ZenCoreFxRack.h"

#include <cmath>
#include <cstring>

namespace Effects {

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

ZenCoreFxRack::ZenCoreFxRack() {
	SetupSlots();
	SetupMotionDesigner();
	SetupMacroControls();
	RegisterParameters();
	BuildRouting();
	BuildGraph();
	RefreshAlgorithmMetadata();
	UpdateGraphActivity();
}

void ZenCoreFxRack::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	envelope_state = 0.0;
	AdvanceMotionLFO(0.0);
	UpdateGraphActivity();
	RefreshAlgorithmMetadata();
}

void ZenCoreFxRack::Reset() {
	PluginSDK::PluginProcessor::Reset();
	envelope_state = 0.0;
	for(MotionLane& lane : motion_lanes) {
		lane.phase = 0.0;
		lane.last_value = 0.0;
	}
	UpdateGraphActivity();
	RefreshAlgorithmMetadata();
}

void ZenCoreFxRack::Process(PluginSDK::ProcessContext& ctx) {
	const int frames = ctx.frames;
	double delta_seconds = 0.0;
	if(current_config.sample_rate > 0 && frames > 0)
		delta_seconds = (double)frames / (double)current_config.sample_rate;

	AdvanceMotionLFO(delta_seconds);
	UpdateEnvelopeFollower(ctx);
	UpdateGraphActivity();
	RefreshAlgorithmMetadata();

	if(!ctx.input.IsValid() || !ctx.output.IsValid()) {
		return;
	}

	double lane_mod = 0.0;
	for(const MotionLane& lane : motion_lanes)
		lane_mod += lane.last_value;

	double macro_sum = 0.0;
	for(const MacroControl& macro : macro_controls)
		macro_sum += GetParameterValue(macro.param);
	if(!macro_controls.IsEmpty())
		macro_sum /= macro_controls.GetCount();

	double morph = GetParameterValue(morph_param);
	double scene_balance = GetParameterValue(scene_balance_param);
	double macro_link = GetParameterValue(macro_link_param);

	for(int ch = 0; ch < ctx.output.channel_count; ++ch) {
		const float* in = ctx.input.GetChannel(ch);
		float* out = ctx.output.GetChannel(ch);
		if(!in || !out)
			continue;

		for(int i = 0; i < frames; ++i) {
			double sample = in[i];
			double processed = sample;

			for(int slot_index = 0; slot_index < ifx_slots.GetCount(); ++slot_index) {
				const RackSlot& slot = ifx_slots[slot_index];
				if(GetParameterValue(slot.enable_param) <= 0.5)
					continue;

				double mix = GetParameterValue(slot.mix_param);
				double tone = GetParameterValue(slot.tone_param);
				double feedback = GetParameterValue(slot.feedback_param);
				double character = GetParameterValue(slot.character_param);
				if(slot_index < motion_lanes.GetCount())
					mix += motion_lanes[slot_index].last_value * 0.5;
				mix += envelope_state * 0.04;
				mix = Upp::clamp(mix, 0.0, 1.0);

				double alg_colour = GetParameterValue(slot.algorithm_param) / 90.0;
				double colour = Upp::clamp(character * 0.6 + alg_colour * 0.4, 0.0, 1.0);
				double drive = 1.0 + tone * 0.75 + feedback * 0.25;
				double shaped = Upp::clamp(processed * drive, -2.0, 2.0);
				processed = processed * (1.0 - mix) + shaped * mix * (0.8 + colour * 0.4);
			}

			if(GetParameterValue(mfx_slot.enable_param) > 0.5) {
				double mix = Upp::clamp(GetParameterValue(mfx_slot.mix_param) + lane_mod * 0.2 + envelope_state * 0.05, 0.0, 1.0);
				double time = GetParameterValue(mfx_slot.tone_param);
				double character = GetParameterValue(mfx_slot.character_param);
				double bloom = processed * (0.6 + time * 0.4);
				double shimmer = Upp::clamp(bloom + processed * character * 0.3, -2.0, 2.0);
				processed = processed * (1.0 - mix) + shimmer * mix;
			}

			if(GetParameterValue(tfx_slot.enable_param) > 0.5) {
				double mix = Upp::clamp(GetParameterValue(tfx_slot.mix_param) + macro_sum * 0.2 + envelope_state * 0.1, 0.0, 1.0);
				double time = GetParameterValue(tfx_slot.tone_param);
				double feedback = GetParameterValue(tfx_slot.feedback_param);
				double tail = processed * (0.7 + time * 0.5);
				double halo = Upp::clamp(tail + feedback * 0.6, -2.0, 2.0);
				processed = processed * (1.0 - mix) + halo * mix;
			}

			double global_mix = Upp::clamp(scene_balance * 0.5 + morph * 0.35 + macro_link * 0.15 + lane_mod * 0.05, 0.0, 1.0);
			double envelope_mix = Upp::clamp(envelope_state * 0.1, 0.0, 0.3);
			global_mix = Upp::clamp(global_mix + envelope_mix, 0.0, 1.0);

			out[i] = (float)(sample * (1.0 - global_mix) + processed * global_mix);
		}
	}
}

void ZenCoreFxRack::SetupSlots() {
	ifx_slots.Clear();
	static const char* ids[] = { "A", "B", "C" };
	for(int i = 0; i < kIfxSlotCount; ++i) {
		RackSlot slot;
		slot.id = ids[i];
		slot.node_id = Format("IFX.%s", ids[i]);
		ifx_slots.Add(pick(slot));
	}

	mfx_slot = RackSlot();
	mfx_slot.id = "MFX";
	mfx_slot.node_id = "MFX";
	tfx_slot = RackSlot();
	tfx_slot.id = "TFX";
	tfx_slot.node_id = "TFX";
}

void ZenCoreFxRack::SetupMotionDesigner() {
	motion_lanes.Clear();
	for(int i = 0; i < kMotionLaneCount; ++i) {
		MotionLane lane;
		lane.id = Format("L%d", i + 1);
		lane.node_id = Format("Motion.%d", i + 1);
		motion_lanes.Add(pick(lane));
	}
}

void ZenCoreFxRack::SetupMacroControls() {
	macro_controls.Clear();
	for(int i = 0; i < kMacroCount; ++i) {
		MacroControl macro;
		macro.id = Format("M%d", i + 1);
		macro.node_id = Format("Macro.%d", i + 1);
		macro_controls.Add(pick(macro));
	}
}

void ZenCoreFxRack::RegisterParameters() {
	PluginSDK::ParameterSet& params = Parameters();

	morph_param = AddParameter(params, "scene_morph", "Scene Morph", 0.0, 1.0, 0.0);
	scene_balance_param = AddParameter(params, "scene_balance", "Scene Balance", 0.0, 1.0, 0.5);
	macro_link_param = AddParameter(params, "macro_link_depth", "Macro Link Depth", 0.0, 1.0, 0.5);

	envelope_attack_param = AddParameter(params, "env_attack", "Envelope Attack", 0.0, 1.0, 0.25);
	envelope_release_param = AddParameter(params, "env_release", "Envelope Release", 0.0, 1.0, 0.4);
	envelope_sensitivity_param = AddParameter(params, "env_sensitivity", "Envelope Sensitivity", 0.0, 1.0, 0.5);

	const Vector<am::DSP::ZenCoreAlgorithm>& catalogue = am::DSP::ZenCoreMFXCatalogue::List();
	double max_algorithm_index = catalogue.IsEmpty() ? 0.0 : (double)(catalogue.GetCount() - 1);
	for(RackSlot& slot : ifx_slots) {
		slot.enable_param = AddParameter(params, Format("slot%s_enable", slot.id), Format("Slot %s Enable", slot.id), 0.0, 1.0, 1.0);
		slot.algorithm_param = AddParameter(params, Format("slot%s_algorithm", slot.id), Format("Slot %s Algorithm", slot.id), 0.0, max_algorithm_index, 0.0, false);
		slot.mix_param = AddParameter(params, Format("slot%s_mix", slot.id), Format("Slot %s Mix", slot.id), 0.0, 1.0, 0.5);
		slot.tone_param = AddParameter(params, Format("slot%s_time", slot.id), Format("Slot %s Time", slot.id), 0.0, 1.0, 0.4);
		slot.feedback_param = AddParameter(params, Format("slot%s_feedback", slot.id), Format("Slot %s Feedback", slot.id), 0.0, 1.0, 0.2);
		slot.character_param = AddParameter(params, Format("slot%s_character", slot.id), Format("Slot %s Character", slot.id), 0.0, 1.0, 0.3);
	}

	mfx_slot.enable_param = AddParameter(params, "mfx_enable", "MFX Enable", 0.0, 1.0, 1.0);
	mfx_slot.algorithm_param = AddParameter(params, "mfx_algorithm", "MFX Algorithm", 0.0, max_algorithm_index, 5.0, false);
	mfx_slot.mix_param = AddParameter(params, "mfx_mix", "MFX Mix", 0.0, 1.0, 0.4);
	mfx_slot.tone_param = AddParameter(params, "mfx_time", "MFX Time", 0.0, 1.0, 0.5);
	mfx_slot.feedback_param = AddParameter(params, "mfx_feedback", "MFX Feedback", 0.0, 1.0, 0.25);
	mfx_slot.character_param = AddParameter(params, "mfx_character", "MFX Character", 0.0, 1.0, 0.35);

	tfx_slot.enable_param = AddParameter(params, "tfx_enable", "TFX Enable", 0.0, 1.0, 1.0);
	tfx_slot.algorithm_param = AddParameter(params, "tfx_algorithm", "TFX Algorithm", 0.0, max_algorithm_index, 8.0, false);
	tfx_slot.mix_param = AddParameter(params, "tfx_mix", "TFX Mix", 0.0, 1.0, 0.5);
	tfx_slot.tone_param = AddParameter(params, "tfx_time", "TFX Time", 0.0, 1.0, 0.6);
	tfx_slot.feedback_param = AddParameter(params, "tfx_feedback", "TFX Feedback", 0.0, 1.0, 0.35);
	tfx_slot.character_param = AddParameter(params, "tfx_character", "TFX Character", 0.0, 1.0, 0.4);

	for(MotionLane& lane : motion_lanes) {
		lane.rate_param = AddParameter(params, Format("motion%s_rate", lane.id), Format("Motion %s Rate", lane.id), 0.0, 1.0, 0.25);
		lane.depth_param = AddParameter(params, Format("motion%s_depth", lane.id), Format("Motion %s Depth", lane.id), 0.0, 1.0, 0.0);
		lane.probability_param = AddParameter(params, Format("motion%s_probability", lane.id), Format("Motion %s Probability", lane.id), 0.0, 1.0, 1.0);
	}

	for(MacroControl& macro : macro_controls)
		macro.param = AddParameter(params, Format("macro%s_amount", macro.id), Format("Macro %s Amount", macro.id), 0.0, 1.0, 0.0);
}

void ZenCoreFxRack::BuildRouting() {
	routing = PluginSDK::RoutingMap();
	routing.Add("Input", "Pre");
	String previous = "Pre";

	if(ifx_slots.IsEmpty()) {
		routing.Add(previous, mfx_slot.node_id);
		previous = mfx_slot.node_id;
	} else {
		for(const RackSlot& slot : ifx_slots) {
			routing.Add(previous, slot.node_id);
			previous = slot.node_id;
		}
		routing.Add(previous, mfx_slot.node_id);
		previous = mfx_slot.node_id;
	}

	routing.Add(previous, tfx_slot.node_id);
	routing.Add(tfx_slot.node_id, "Output");
	routing.Add("Input", "Output");
}

void ZenCoreFxRack::BuildGraph() {
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

	add_node("Input", "Input", "IO");
	add_node("Pre", "Pre", "FX");
	for(RackSlot& slot : ifx_slots)
		slot.node_index = add_node(slot.node_id, Format("Slot %s", slot.id), "FX");
	mfx_slot.node_index = add_node(mfx_slot.node_id, "MFX", "FX");
	tfx_slot.node_index = add_node(tfx_slot.node_id, "TFX", "FX");
	add_node("Output", "Output", "IO");
	add_node("MotionDesigner", "Motion Designer", "Mod");
	add_node("MacroMorph", "Macro Morph", "Macro");
	add_node("MacroSurface", "Macro Surface", "Macro");
	add_node("EnvelopeFollower", "Envelope Follower", "Mod");

	for(MotionLane& lane : motion_lanes) {
		add_node(lane.node_id, Format("Motion %s", lane.id), "Mod");
		lane.control_edges.Clear();
		lane.control_edges.Add(add_control_edge("MotionDesigner", lane.node_id));
	}

	for(MacroControl& macro : macro_controls) {
		add_node(macro.node_id, Format("Macro %s", macro.id), "Macro");
		macro.control_edges.Clear();
		macro.control_edges.Add(add_control_edge("MacroSurface", macro.node_id));
	}

	input_to_pre_edge = add_audio_edge("Input", "Pre");
	dry_path_edge = add_audio_edge("Input", "Output");

	String previous = "Pre";
	if(ifx_slots.IsEmpty()) {
		mfx_slot.input_edge = add_audio_edge(previous, mfx_slot.node_id);
		previous = mfx_slot.node_id;
	} else {
		for(int i = 0; i < ifx_slots.GetCount(); ++i) {
			RackSlot& slot = ifx_slots[i];
			slot.control_edges.Clear();
			slot.input_edge = add_audio_edge(previous, slot.node_id);
			String next = (i + 1 < ifx_slots.GetCount()) ? ifx_slots[i + 1].node_id : mfx_slot.node_id;
			slot.output_edge = add_audio_edge(slot.node_id, next);
			previous = next;
		}
		mfx_slot.input_edge = ifx_slots.Top().output_edge;
	}

	mfx_slot.control_edges.Clear();
	mfx_slot.output_edge = add_audio_edge(mfx_slot.node_id, tfx_slot.node_id);
	tfx_slot.input_edge = mfx_slot.output_edge;

	tfx_slot.control_edges.Clear();
	tfx_slot.output_edge = add_audio_edge(tfx_slot.node_id, "Output");

	envelope_edge = add_control_edge("EnvelopeFollower", "MotionDesigner");

	for(RackSlot& slot : ifx_slots) {
		int env_edge = add_control_edge("EnvelopeFollower", slot.node_id);
		slot.control_edges.Add(env_edge);
		for(MotionLane& lane : motion_lanes) {
			int edge = add_control_edge(lane.node_id, slot.node_id);
			lane.control_edges.Add(edge);
			slot.control_edges.Add(edge);
		}
		for(MacroControl& macro : macro_controls) {
			int edge = add_control_edge(macro.node_id, slot.node_id);
			macro.control_edges.Add(edge);
			slot.control_edges.Add(edge);
		}
	}

	int env_mfx = add_control_edge("EnvelopeFollower", mfx_slot.node_id);
	mfx_slot.control_edges.Add(env_mfx);
	for(MotionLane& lane : motion_lanes) {
		int edge = add_control_edge(lane.node_id, mfx_slot.node_id);
		lane.control_edges.Add(edge);
		mfx_slot.control_edges.Add(edge);
	}
	for(MacroControl& macro : macro_controls) {
		int edge = add_control_edge(macro.node_id, mfx_slot.node_id);
		macro.control_edges.Add(edge);
		mfx_slot.control_edges.Add(edge);
	}

	int env_tfx = add_control_edge("EnvelopeFollower", tfx_slot.node_id);
	tfx_slot.control_edges.Add(env_tfx);
	for(MotionLane& lane : motion_lanes) {
		int edge = add_control_edge(lane.node_id, tfx_slot.node_id);
		lane.control_edges.Add(edge);
		tfx_slot.control_edges.Add(edge);
	}
	for(MacroControl& macro : macro_controls) {
		int edge = add_control_edge(macro.node_id, tfx_slot.node_id);
		macro.control_edges.Add(edge);
		tfx_slot.control_edges.Add(edge);
	}

	motion_bus_edge = add_control_edge("MotionDesigner", mfx_slot.node_id);
	macro_bus_edge = add_control_edge("MacroMorph", mfx_slot.node_id);
	RefreshAlgorithmMetadata();
}

void ZenCoreFxRack::UpdateGraphActivity() {
	PluginSDK::GraphVisualization& g = Graph();
	if(g.edges.IsEmpty())
		return;

	bool any_ifx_active = false;
	for(RackSlot& slot : ifx_slots) {
		bool enabled = GetParameterValue(slot.enable_param) > 0.5;
		any_ifx_active = any_ifx_active || enabled;
		if(slot.input_edge >= 0 && slot.input_edge < g.edges.GetCount())
			g.edges[slot.input_edge].active = enabled;
		if(slot.output_edge >= 0 && slot.output_edge < g.edges.GetCount())
			g.edges[slot.output_edge].active = enabled;
		for(int idx : slot.control_edges) {
			if(idx >= 0 && idx < g.edges.GetCount())
				g.edges[idx].active = enabled;
		}
	}

	bool mfx_enabled = GetParameterValue(mfx_slot.enable_param) > 0.5 || !any_ifx_active;
	if(mfx_slot.input_edge >= 0 && mfx_slot.input_edge < g.edges.GetCount())
		g.edges[mfx_slot.input_edge].active = mfx_enabled;
	if(mfx_slot.output_edge >= 0 && mfx_slot.output_edge < g.edges.GetCount())
		g.edges[mfx_slot.output_edge].active = mfx_enabled;
	for(int idx : mfx_slot.control_edges) {
		if(idx >= 0 && idx < g.edges.GetCount())
			g.edges[idx].active = mfx_enabled;
	}

	bool tfx_enabled = GetParameterValue(tfx_slot.enable_param) > 0.5;
	if(tfx_slot.input_edge >= 0 && tfx_slot.input_edge < g.edges.GetCount())
		g.edges[tfx_slot.input_edge].active = tfx_enabled;
	if(tfx_slot.output_edge >= 0 && tfx_slot.output_edge < g.edges.GetCount())
		g.edges[tfx_slot.output_edge].active = tfx_enabled;
	for(int idx : tfx_slot.control_edges) {
		if(idx >= 0 && idx < g.edges.GetCount())
			g.edges[idx].active = tfx_enabled;
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
	if(motion_bus_edge >= 0 && motion_bus_edge < g.edges.GetCount())
		g.edges[motion_bus_edge].active = any_motion;

	bool any_macro = false;
	for(MacroControl& macro : macro_controls) {
		bool macro_active = GetParameterValue(macro.param) > 0.001;
		any_macro = any_macro || macro_active;
		for(int idx : macro.control_edges) {
			if(idx >= 0 && idx < g.edges.GetCount())
				g.edges[idx].active = macro_active;
		}
	}
	if(macro_bus_edge >= 0 && macro_bus_edge < g.edges.GetCount())
		g.edges[macro_bus_edge].active = any_macro;

	if(envelope_edge >= 0 && envelope_edge < g.edges.GetCount())
		g.edges[envelope_edge].active = envelope_state > 0.0001;

	if(dry_path_edge >= 0 && dry_path_edge < g.edges.GetCount())
		g.edges[dry_path_edge].active = true;
	if(input_to_pre_edge >= 0 && input_to_pre_edge < g.edges.GetCount())
		g.edges[input_to_pre_edge].active = true;
}

void ZenCoreFxRack::AdvanceMotionLFO(double delta_seconds) {
	if(delta_seconds <= 0.0)
		return;

	for(MotionLane& lane : motion_lanes) {
		double rate = GetParameterValue(lane.rate_param);
		double depth = GetParameterValue(lane.depth_param);
		if(depth <= 0.0) {
			lane.last_value = 0.0;
			continue;
		}

		double frequency = Upp::clamp(rate, 0.0, 1.0) * 8.0;
		lane.phase += frequency * delta_seconds * kTwoPi;
		if(lane.phase > kTwoPi)
			lane.phase = std::fmod(lane.phase, kTwoPi);

		double probability = GetParameterValue(lane.probability_param);
		double raw = std::sin(lane.phase);
		lane.last_value = raw * depth * Upp::clamp(probability, 0.0, 1.0);
	}
}

void ZenCoreFxRack::UpdateEnvelopeFollower(const PluginSDK::ProcessContext& ctx) {
	if(!ctx.input.IsValid() || ctx.frames <= 0)
		return;

	double sum = 0.0;
	int total_samples = ctx.frames * Upp::Max(ctx.input.channel_count, 1);
	for(int ch = 0; ch < ctx.input.channel_count; ++ch) {
		const float* buffer = ctx.input.GetChannel(ch);
		if(!buffer)
			continue;
		for(int i = 0; i < ctx.frames; ++i)
			sum += std::abs(buffer[i]);
	}

	double average = total_samples > 0 ? sum / total_samples : 0.0;
	double sensitivity = GetParameterValue(envelope_sensitivity_param);
	double target = Upp::clamp(average * (0.5 + sensitivity * 2.0), 0.0, 4.0);

	double attack = Upp::clamp(GetParameterValue(envelope_attack_param), 0.0, 1.0);
	double release = Upp::clamp(GetParameterValue(envelope_release_param), 0.0, 1.0);
	double coeff = target > envelope_state ? std::pow(0.1, 1.0 - attack) : std::pow(0.1, 1.0 - release);
	envelope_state += (target - envelope_state) * (1.0 - coeff);
	envelope_state = Upp::clamp(envelope_state, 0.0, 4.0);
}

void ZenCoreFxRack::RefreshAlgorithmMetadata() {
	PluginSDK::GraphVisualization& g = Graph();
	const Vector<am::DSP::ZenCoreAlgorithm>& catalogue = am::DSP::ZenCoreMFXCatalogue::List();
	auto resolve_label = [&](bool combination, const String& name) {
		if(combination)
			return Format("%s (Combo)", name);
		return name;
	};
	auto update_slot = [&](RackSlot& slot) {
		double selector = slot.algorithm_param >= 0 ? GetParameterValue(slot.algorithm_param) : 0.0;
		if(!catalogue.IsEmpty()) {
			int index = Upp::clamp((int)std::round(selector), 0, catalogue.GetCount() - 1);
			slot.algorithm_index = index;
			const am::DSP::ZenCoreAlgorithm& algo = catalogue[index];
			slot.algorithm_label = resolve_label(algo.combination, algo.name);
		} else {
			slot.algorithm_index = 0;
			slot.algorithm_label = "Bypass";
		}
		if(slot.node_index >= 0 && slot.node_index < g.nodes.GetCount()) {
			String prefix = slot.id;
			if(slot.id.GetCount() == 1)
				prefix = Format("Slot %s", slot.id);
			g.nodes[slot.node_index].label = Format("%s — %s", prefix, slot.algorithm_label);
		}
	};
	for(RackSlot& slot : ifx_slots)
		update_slot(slot);
	update_slot(mfx_slot);
	update_slot(tfx_slot);
}

double ZenCoreFxRack::GetParameterValue(int index) const {
	if(index < 0)
		return 0.0;
	return Parameters().GetValue(index);
}

} // namespace Effects
