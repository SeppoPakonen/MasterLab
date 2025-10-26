#ifndef _instruments_zencoreworkstation_zencoreworkstation_h_
#define _instruments_zencoreworkstation_zencoreworkstation_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class ZenCoreWorkstation : public PluginSDK::InstrumentProcessor {
public:
	typedef ZenCoreWorkstation CLASSNAME;
	ZenCoreWorkstation();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;
	void NoteOn(const PluginSDK::NoteEvent& evt) override;
	void NoteOff(const PluginSDK::NoteEvent& evt) override;
	void AllNotesOff() override;

private:
	static constexpr int kPartialCount = 4;
	static constexpr int kDrumPadCount = 16;
	static constexpr int kMotionLaneCount = 3;
	static constexpr int kMacroCount = 4;

	struct PartialSlot {
		String id;
		String node_id;
		String ifx_node_id;
		int to_mfx_edge = -1;
		int enable_param = -1;
		int level_param = -1;
		int cutoff_param = -1;
		int resonance_param = -1;
		int coarse_param = -1;
		int fine_param = -1;
		int ifx_send_param = -1;
		int tone_edge = -1;
		int ifx_edge = -1;
		Vector<int> control_edges;
	};

	struct DrumLane {
		String id;
		int level_param = -1;
		int pan_param = -1;
		int attack_param = -1;
		int decay_param = -1;
		int release_param = -1;
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

	struct SceneMacro {
		String id;
		String node_id;
		int param = -1;
		Vector<int> control_edges;
	};

	struct VoiceState {
		int note = -1;
		double velocity = 0.0;
		Vector<double> partial_gains;
		double morph_position = 0.0;
		bool releasing = false;
	};

	void SetupPartials();
	void SetupDrumLanes();
	void SetupMotionDesigner();
	void SetupSceneMacros();
	void RegisterParameters();
	void BuildRouting();
	void BuildGraph();
	void UpdateGraphActivity();
	void AdvanceMotionLanes(double delta_seconds);
	void RefreshVoiceGains();
	double GetParameterValue(int index) const;

	Vector<PartialSlot> partials;
	Vector<DrumLane> drum_lanes;
	Vector<MotionLane> motion_lanes;
	Vector<SceneMacro> scene_macros;
	Vector<VoiceState> active_voices;

	int morph_param = -1;
	int scene_blend_param = -1;
	int engine_mode_param = -1;
	int drum_edge = -1;
	int drum_to_mfx_edge = -1;
	int motion_drive_edge = -1;
	int macro_drive_edge = -1;

	PluginSDK::RoutingMap routing;
};

} // namespace Instruments

#endif
