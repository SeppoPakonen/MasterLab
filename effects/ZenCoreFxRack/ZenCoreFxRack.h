#ifndef _effects_zencorefxrack_zencorefxrack_h_
#define _effects_zencorefxrack_zencorefxrack_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ZenCoreFxRack : public PluginSDK::PluginProcessor {
public:
	typedef ZenCoreFxRack CLASSNAME;
	ZenCoreFxRack();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	static constexpr int kIfxSlotCount = 3;
	static constexpr int kMotionLaneCount = 3;
	static constexpr int kMacroCount = 4;

	struct RackSlot {
		String id;
		String node_id;
		int enable_param = -1;
		int algorithm_param = -1;
		int mix_param = -1;
		int tone_param = -1;
		int feedback_param = -1;
		int character_param = -1;
		Vector<int> control_edges;
		int input_edge = -1;
		int output_edge = -1;
	};

	struct MotionLane {
		String id;
		String node_id;
		int rate_param = -1;
		int depth_param = -1;
		int probability_param = -1;
		Vector<int> control_edges;
		double phase = 0.0;
		double last_value = 0.0;
	};

	struct MacroControl {
		String id;
		String node_id;
		int param = -1;
		Vector<int> control_edges;
	};

	void SetupSlots();
	void SetupMotionDesigner();
	void SetupMacroControls();
	void RegisterParameters();
	void BuildRouting();
	void BuildGraph();
	void UpdateGraphActivity();
	void AdvanceMotionLFO(double delta_seconds);
	void UpdateEnvelopeFollower(const PluginSDK::ProcessContext& ctx);
	double GetParameterValue(int index) const;

	Vector<RackSlot> ifx_slots;
	RackSlot mfx_slot;
	RackSlot tfx_slot;
	Vector<MotionLane> motion_lanes;
	Vector<MacroControl> macro_controls;

	int morph_param = -1;
	int scene_balance_param = -1;
	int macro_link_param = -1;
	int envelope_attack_param = -1;
	int envelope_release_param = -1;
	int envelope_sensitivity_param = -1;
	int input_to_pre_edge = -1;
	int dry_path_edge = -1;
	int envelope_edge = -1;
	int motion_bus_edge = -1;
	int macro_bus_edge = -1;
	double envelope_state = 0.0;

	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
