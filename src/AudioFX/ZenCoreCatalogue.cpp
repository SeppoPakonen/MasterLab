#include "AudioFX.h"

namespace am {
namespace DSP {

namespace {

Vector<ZenCoreAlgorithm>& AlgorithmStore() {
	static Vector<ZenCoreAlgorithm> algorithms;
	if(algorithms.IsEmpty()) {
		algorithms.Add({ "chorus_juno", "JUNO Chorus", "Modulation", false });
		algorithms.Add({ "chorus_dimension", "Dimension D", "Modulation", false });
		algorithms.Add({ "phaser_sbf325", "SBF-325 Phaser", "Modulation", false });
		algorithms.Add({ "ensemble_jx", "JX Ensemble", "Modulation", false });
		algorithms.Add({ "flanger_bbd", "BBD Flanger", "Modulation", false });
		algorithms.Add({ "delay_dimen", "Stereo Delay", "Delay", false });
		algorithms.Add({ "delay_tape", "Tape Echo", "Delay", false });
		algorithms.Add({ "delay_reverse", "Reverse Delay", "Delay", false });
		algorithms.Add({ "reverb_room", "Room Reverb", "Reverb", false });
		algorithms.Add({ "reverb_hall", "Hall Reverb", "Reverb", false });
		algorithms.Add({ "reverb_plate", "Plate Reverb", "Reverb", false });
		algorithms.Add({ "amp_jc120", "JC-120 Amp", "Amp", false });
		algorithms.Add({ "amp_stack", "Metal Stack", "Amp", false });
		algorithms.Add({ "cab_sim", "Cabinet Simulator", "Amp", false });
		algorithms.Add({ "compressor_vca", "VCA Compressor", "Dynamics", false });
		algorithms.Add({ "compressor_multiband", "Multiband Comp", "Dynamics", false });
		algorithms.Add({ "limiter_isotropic", "ISP Limiter", "Dynamics", false });
		algorithms.Add({ "eq_4band", "4-Band EQ", "EQ", false });
		algorithms.Add({ "eq_parametric", "Parametric EQ", "EQ", false });
		algorithms.Add({ "bitcrusher", "Bit Crusher", "Lo-Fi", false });
		algorithms.Add({ "ring_mod", "Ring Modulator", "Special", false });
		algorithms.Add({ "pitch_shift", "Pitch Shifter", "Pitch", false });
		algorithms.Add({ "pitch_formant", "Formant Shift", "Pitch", false });
		algorithms.Add({ "filter_vintage", "Vintage Filter", "Filter", false });
		algorithms.Add({ "filter_mod", "Mod Filter", "Filter", false });
		algorithms.Add({ "combination_amp_delay", "Amp → Delay", "Combination", true });
		algorithms.Add({ "combination_enhancer_chorus", "Enhancer → Chorus", "Combination", true });
		algorithms.Add({ "combination_bitcrush_delay", "Crush → Delay", "Combination", true });
		algorithms.Add({ "combination_comp_eq", "Comp → EQ", "Combination", true });
		algorithms.Add({ "combination_filter_delay", "Filter → Delay", "Combination", true });
		algorithms.Add({ "combination_pitch_verb", "Pitch → Reverb", "Combination", true });
		algorithms.Add({ "lofi_sampler", "Sampler Lo-Fi", "Lo-Fi", false });
		algorithms.Add({ "stereo_imager", "Stereo Imager", "Utility", false });
		algorithms.Add({ "vocoder", "Vocoder", "Special", false });
		algorithms.Add({ "harmonic_exciter", "Harmonic Exciter", "Harmonic", false });
		algorithms.Add({ "transient_shaper", "Transient Shaper", "Dynamics", false });
		algorithms.Add({ "guitar_multi", "Guitar Multi-FX", "Combination", true });
		algorithms.Add({ "chorus_triple", "Triple Chorus", "Modulation", false });
		algorithms.Add({ "dimension_wide", "Dimension Wide", "Modulation", false });
		algorithms.Add({ "rotary", "Rotary Speaker", "Modulation", false });
		algorithms.Add({ "tremolo_pan", "Tremolo/Pan", "Modulation", false });
		algorithms.Add({ "delay_dual", "Dual Delay", "Delay", false });
		algorithms.Add({ "delay_multi_tap", "Multi-tap Delay", "Delay", false });
		algorithms.Add({ "reverb_shimmer", "Shimmer Reverb", "Reverb", false });
		algorithms.Add({ "reverb_spring", "Spring Reverb", "Reverb", false });
		algorithms.Add({ "comp_bus", "Bus Compressor", "Dynamics", false });
		algorithms.Add({ "comp_vintage", "Vintage Compressor", "Dynamics", false });
		algorithms.Add({ "filter_sequenced", "Sequenced Filter", "Filter", false });
		algorithms.Add({ "filter_step", "Step Filter", "Filter", false });
		algorithms.Add({ "glitch_chop", "Glitch Chop", "Special", false });
		algorithms.Add({ "beat_repeater", "Beat Repeater", "Special", false });
		algorithms.Add({ "combination_comp_delay", "Comp → Delay", "Combination", true });
	}
	return algorithms;
}

} // namespace

const Vector<ZenCoreAlgorithm>& ZenCoreMFXCatalogue::List() {
	return AlgorithmStore();
}

const ZenCoreAlgorithm* ZenCoreMFXCatalogue::FindById(const String& id) {
	if(id.IsEmpty())
		return nullptr;
	const Vector<ZenCoreAlgorithm>& list = AlgorithmStore();
	for(const ZenCoreAlgorithm& algo : list) {
		if(algo.id == id)
			return &algo;
	}
	return nullptr;
}

const ZenCoreAlgorithm* ZenCoreMFXCatalogue::FindByIndex(int index) {
	const Vector<ZenCoreAlgorithm>& list = AlgorithmStore();
	if(index < 0 || index >= list.GetCount())
		return nullptr;
	return &list[index];
}

} // namespace DSP
} // namespace am
