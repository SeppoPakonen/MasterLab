#!/usr/bin/env python3
import re
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
EFFECTS_MD = REPO / "EFFECTS.md"
INSTRUMENTS_MD = REPO / "INSTRUMENTS.md"

EFFECTS_SECTIONS = {
	"Antares Pitch & Vocal Suite (Antares)": "PitchVocalSuite",
	"Arturia Analog FX Inserts (Arturia)": "AnalogFxInserts",
	"KRISTAL ToneBooster Essentials (KRISTAL)": "ToneboosterEssentials",
	"Steinberg Dynamics & Level (Steinberg)": "DynamicsLevelSuite",
	"Steinberg Harmonic & Amp (Steinberg)": "HarmonicAmpSuite",
	"Steinberg Delay & Reverb (Steinberg)": "DelayReverbSuite",
	"Steinberg Modulation & Spatial (Steinberg)": "ModSpatialSuite",
	"Steinberg Filter & Sound Design (Steinberg)": "FilterDesignSuite",
	"Steinberg Pitch & Time (Steinberg)": "PitchTimeSuite",
	"Steinberg Analysis & Utility (Steinberg)": "AnalysisUtilitySuite",
	"Steinberg Restoration & Noise (Steinberg)": "RestorationNoiseSuite",
	"Waves Signature Series (Waves)": "SignatureChainSuite",
	"Waves Analog Channel & Console (Waves)": "AnalogConsoleSuite",
	"Waves Dynamics & Control (Waves)": "DynamicsControlSuite",
	"Waves Mastering & Linear Phase (Waves)": "MasteringLinearSuite",
	"Waves Reverb & Delay (Waves)": "ReverbDelaySuite",
	"Waves Modulation & Creative FX (Waves)": "ModCreativeSuite",
	"Waves Pitch & Vocal (Waves)": "PitchVocalCollection",
	"Waves Spatial & Surround (Waves)": "SpatialSurroundSuite",
	"Waves Guitar & Instrument (Waves)": "GuitarInstrumentSuite",
	"Waves Restoration & Noise (Waves)": "RestorationNoiseCollection",
	"Waves Metering & Analysis (Waves)": "MeteringAnalysisSuite",
	"Roland Zenology FX (Roland)": "ZenCoreFxRack",
	"APU Loudness Suite (APU)": "LoudnessControlSuite",
	"Cymatics Vocal Design (Cymatics)": "VocalDesignRack",
	"iZotope Voice & Mix Suite (iZotope)": "VoiceMixSuite",
	"Replay Neural Voice (Replay)": "NeuralVoiceChanger",
	"Synchro Arts Alignment (Synchro Arts)": "VocalAlignmentEngine",
	"Steinberg SpectraLayers FX (Steinberg)": "SpectralLayersFx",
	"KSHMR Essentials (Dharma Worldwide)": "EssentialMacroFx",
	"Celemony Melodyne (Celemony)": "PolyphonicPitchEditor",
	"Crave DSP Transient Control (Crave DSP)": "TransientEqDesigner",
	"FabFilter Timeless (FabFilter)": "TimelessDualDelay",
	"Sonible SmartReverb (Sonible)": "AdaptiveSmartReverb",
	"Sugar Bytes Effectrix (Sugar Bytes)": "SequenceFxEngine",
	"W.A. Production Kick Suite (W.A. Production)": "KickShapingSuite",
	"Native Instruments Guitar Rig (Native Instruments)": "ModularGuitarRig",
	"Waves AI Assistance & Collaboration (Waves)": "AiAssistSuite",
	"Waves Vocal & Live Utilities (Waves)": "VocalLiveUtilities",
	"Waves Harmonics & Dynamics (Waves)": "HarmonicsDynamicsSuite",
	"Waves Reverb & Ambience (Waves)": "ReverbAmbienceSuite",
	"Waves Spatial & Immersive (Waves)": "SpatialImmersiveSuite",
	"Waves Guitar & Instrument Platforms (Waves)": "GuitarInstrumentPlatforms"
}

INSTRUMENT_SECTIONS = {
	"Roland Zenology Workstation (Roland)": "ZenCoreWorkstation",
	"Roland JX-8P Model Expansion (Roland)": "ZenModelJX8P",
	"Roland JUNO-106 Model Expansion (Roland)": "ZenModelJUNO106",
	"Big Fish Audio Momentum (Big Fish Audio)": "MomentumLoopStation",
	"reFX Nexus Workstation (reFX)": "LayeredRompler",
	"Toontrack Songwriting Instruments (Toontrack)": "SongwriterInstrumentPack",
	"LennarDigital Sylenth1 (LennarDigital)": "VirtualAnalogStack",
	"TAL Sampler (Togu Audio Line)": "VintageSampler",
	"Native Instruments Core Synths (Native Instruments)": "CoreSynthCollection",
	"Waves Instrument Suite (Waves)": "StudioInstrumentSuite"
}


def parse_sections(path):
	sections = {}
	current = None
	table_buffer = []

	def flush_table():
		nonlocal table_buffer, current
		if not current or not table_buffer:
			table_buffer = []
			return
		table = parse_table(table_buffer)
		if table:
			current.setdefault("tables", []).append(table)
		table_buffer = []

	with path.open("r", encoding="utf-8") as fh:
		for raw_line in fh:
			line = raw_line.rstrip("\n")
			if line.startswith("## "):
				flush_table()
				title = line[3:].strip()
				current = {"title": title, "description": [], "tables": []}
				sections[title] = current
				continue
			if line.startswith("### "):
				flush_table()
				title = line[4:].strip()
				current = {"title": title, "description": [], "tables": []}
				sections[title] = current
				continue
			if current is None:
				continue
			if line.startswith("|"):
				table_buffer.append(line)
				continue
			if table_buffer:
				flush_table()
			stripped = line.strip()
			if stripped:
				current["description"].append(stripped)
	flush_table()
	return sections


def parse_table(lines):
	if len(lines) < 3:
		return []
	header = [col.strip() for col in lines[0].strip("|").split("|")]
	rows = []
	for line in lines[2:]:
		if not line.startswith("|"):
			continue
		cells = [cell.strip() for cell in line.strip("|").split("|")]
		if len(cells) != len(header):
			continue
		row = {}
		for key, value in zip(header, cells):
			row[key] = value.replace("<br>", "\n")
		rows.append(row)
	return rows


def vendor_and_name(title):
	vendor = None
	match = re.search(r"\(([^)]+)\)", title)
	if match:
		vendor = match.group(1).strip()
	base = title.split("(")[0].strip()
	if vendor and base.lower().startswith(vendor.lower()):
		base = base[len(vendor):].strip(" -")
	return vendor, base if base else title


def camel_to_header(name):
	parts = re.findall(r"[A-Z][a-z0-9]*|[0-9]+", name)
	return " ".join(parts) if parts else name


def write_stub(directory, class_name, display_name, data, is_effect):
	directory.mkdir(parents=True, exist_ok=True)
	agent_path = directory / "AGENTS.md"
	header_path = directory / f"{class_name}.h"
	source_path = directory / f"{class_name}.cpp"
	upp_path = directory / f"{class_name}.upp"

	vendor, base_display = vendor_and_name(data["title"])
	if display_name is None:
		display_name = camel_to_header(class_name)
	title = f"# {display_name} {'Effect' if is_effect else 'Instrument'} Stub"

	lines = [title, ""]
	lines.append("## Reference")
	lines.append(f"- Inspired by: {base_display}")
	lines.append(f"- Vendor: {vendor or 'Independent'}")
	src_column = "Referenced plug-ins" if any("Referenced plug-ins" in row for table in data["tables"] for row in table) else "Referenced instruments"
	referenced = []
	for table in data["tables"]:
		for row in table:
			if src_column in row:
				referenced.append(row[src_column])
	if referenced:
		lines.append(f"- Source catalog: {', '.join(referenced)}")

	if data["description"]:
		lines.append("")
		lines.append("## Summary")
		lines.append("\n".join(data["description"]))

	lines.append("")
	lines.append("## Implementation Plan")

	for table in data["tables"]:
		for row in table:
			group_name = row.get("Group") or camel_to_header(class_name)
			lines.append(f"### {group_name}")
			lines.append(f"- Category: {row.get('Category', 'n/a')}")
			sidechain = row.get("Sidechain") or row.get("Side chain") or "n/a"
			lines.append(f"- Sidechain: {sidechain}")
			blueprint = row.get("Generic blueprint") or row.get("Goal") or ""
			if blueprint:
				lines.append(f"- Processing blueprint: {blueprint}")
			key_features = [item.strip() for item in (row.get("Key features") or "").split("\n") if item.strip()]
			if key_features:
				lines.append("- Key features:")
				for feat in key_features:
					lines.append(f"  - {feat}")
			core_classes = [item.strip() for item in (row.get("Core classes") or "").split("\n") if item.strip()]
			if core_classes:
				lines.append("- Core building blocks:")
				for cls in core_classes:
					lines.append(f"  - {cls}")
			signal = row.get("Signal flow") or row.get("Voice graph") or ""
			if signal:
				lines.append(f"- Signal/voice flow: {signal}")
			lines.append("- TODO:")
			lines.append("  - Wire PluginSDK parameter/route scaffolding to match the modules above")
			lines.append("  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint")
			lines.append("")

	agent_path.write_text("\n".join(lines).rstrip() + "\n", encoding="utf-8")

	namespace = "Effects" if is_effect else "Instruments"
	base_class = "PluginSDK::PluginProcessor" if is_effect else "PluginSDK::InstrumentProcessor"

	header_guard = f"_{'effects' if is_effect else 'instruments'}_{class_name.lower()}_{class_name.lower()}_h_"
	header_lines = [
		f"#ifndef {header_guard}",
		f"#define {header_guard}",
		"",
		"#include <PluginSDK/PluginSDK.h>",
		"",
		f"namespace {namespace} {{",
		"",
		f"class {class_name} : public {base_class} {{",
		"public:",
		f"\ttypedef {class_name} CLASSNAME;",
		f"\t{class_name}();",
		"",
		"\tvoid Prepare(const PluginSDK::AudioConfig& cfg) override;",
		"\tvoid Process(PluginSDK::ProcessContext& ctx) override;",
		"\tvoid Reset() override;",
	]

	if not is_effect:
		header_lines.extend([
			"\tvoid NoteOn(const PluginSDK::NoteEvent& evt) override;",
			"\tvoid NoteOff(const PluginSDK::NoteEvent& evt) override;",
			"\tvoid AllNotesOff() override;",
		])

	header_lines.extend([
		"",
		"private:",
		"\tPluginSDK::RoutingMap routing;",
		"};",
		"",
		f"}} // namespace {namespace}",
		"",
		"#endif",
	])

	header_path.write_text("\n".join(header_lines) + "\n", encoding="utf-8")

	source_lines = [
		f"#include \"{class_name}.h\"",
		"",
		f"namespace {namespace} {{",
		"",
		f"{class_name}::{class_name}() {{",
		"\t// TODO: Register parameters and initialise routing map",
		"}",
		"",
		f"void {class_name}::Prepare(const PluginSDK::AudioConfig& cfg) {{",
		"\tPluginSDK::PluginProcessor::Prepare(cfg);",
		"\t(void)cfg;",
		"\t// TODO: Allocate resources based on cfg",
		"}",
		"",
		f"void {class_name}::Reset() {{",
		"\tPluginSDK::PluginProcessor::Reset();",
		"\t// TODO: Reset internal state",
		"}",
		"",
		f"void {class_name}::Process(PluginSDK::ProcessContext& ctx) {{",
		"\t(void)ctx;",
		"\t// TODO: Implement processing graph described in AGENTS.md",
		"}",
	]

	if not is_effect:
		source_lines.extend([
			"",
			f"void {class_name}::NoteOn(const PluginSDK::NoteEvent& evt) {{",
			"\tPluginSDK::InstrumentProcessor::NoteOn(evt);",
			"\t// TODO: Dispatch note-on to voice manager",
			"}",
			"",
			f"void {class_name}::NoteOff(const PluginSDK::NoteEvent& evt) {{",
			"\tPluginSDK::InstrumentProcessor::NoteOff(evt);",
			"\t// TODO: Dispatch note-off to voice manager",
			"}",
			"",
			f"void {class_name}::AllNotesOff() {{",
			"\tPluginSDK::InstrumentProcessor::AllNotesOff();",
			"\t// TODO: Reset envelopes/voices",
			"}",
		])

	source_lines.extend([
		"",
		f"}} // namespace {namespace}",
		""
	])

	source_path.write_text("\n".join(source_lines), encoding="utf-8")

	upp_lines = [
		"uses",
		"\tPluginSDK;",
		"",
		"file",
		"\tAGENTS.md,",
		f"\t{class_name}.h,",
		f"\t{class_name}.cpp;",
	]
	upp_path.write_text("\n".join(upp_lines) + "\n", encoding="utf-8")


def main():
	effects_sections = parse_sections(EFFECTS_MD)
	instrument_sections = parse_sections(INSTRUMENTS_MD)

	effects_root = REPO / "effects"
	instruments_root = REPO / "instruments"
	effects_root.mkdir(exist_ok=True)
	instruments_root.mkdir(exist_ok=True)

	for title, class_name in EFFECTS_SECTIONS.items():
		if title not in effects_sections:
			continue
		data = effects_sections[title]
		display = camel_to_header(class_name)
		write_stub(effects_root / class_name, class_name, display, data, is_effect=True)

	for title, class_name in INSTRUMENT_SECTIONS.items():
		if title not in instrument_sections:
			continue
		data = instrument_sections[title]
		display = camel_to_header(class_name)
		write_stub(instruments_root / class_name, class_name, display, data, is_effect=False)


if __name__ == "__main__":
	main()
