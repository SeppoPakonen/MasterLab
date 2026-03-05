#include "CuteCLI.h"

static String GetArg(const Vector<String>& args, int index, const String& def = String()) {
	return index >= 0 && index < args.GetCount() ? args[index] : def;
}

int CuteCli::ShowHelp() const {
	Cout() << "CuteCLI headless test harness\n";
	Cout() << "Commands:\n";
	Cout() << "  help\n";
	Cout() << "  create_project <output_dir> <project_name>\n";
	Cout() << "  test_midi_notes [polyphony]\n";
	Cout() << "  render_wav <output_wav> [seconds]\n";
	Cout() << "  smoke <output_dir>\n";
	return 0;
}

int CuteCli::CmdCreateProject(const Vector<String>& args) const {
	if(args.GetCount() < 3) {
		Cerr() << "create_project requires <output_dir> <project_name>\n";
		return 2;
	}

	String output_dir = NormalizePath(GetArg(args, 1));
	String project_name = GetArg(args, 2);

	if(!DirectoryExists(output_dir) && !RealizeDirectory(output_dir)) {
		Cerr() << "Failed to create directory: " << output_dir << "\n";
		return 1;
	}

	am::Project project;
	project.SetAutosave(true, 5.0, 20);
	project.SetMaxUndo(2048);

	String project_file = AppendFileName(output_dir, project_name + ".cuteproject.txt");
	FileOut out(project_file);
	if(!out) {
		Cerr() << "Failed to open project file: " << project_file << "\n";
		return 1;
	}

	out << "name=" << project_name << "\n";
	out << "autosave_enabled=" << (project.GetAutosaveEnabled() ? "1" : "0") << "\n";
	out << "autosave_minutes=" << project.GetAutosaveMinutes() << "\n";
	out << "autosave_max_backups=" << project.GetAutosaveMaxBackups() << "\n";
	out << "max_undo=" << project.GetMaxUndo() << "\n";
	out.Close();

	Cout() << "Created project: " << project_file << "\n";
	return 0;
}

int CuteCli::CmdTestMidiNotes(const Vector<String>& args) const {
	int polyphony = max(1, StrInt(GetArg(args, 1, "8")));

	am::Synth::VoiceManager vm;
	vm.Configure(polyphony);

	for(int i = 0; i < polyphony; ++i) {
		int note = 60 + (i % 12);
		double velocity = 0.5 + 0.5 * (double(i % 4) / 3.0);
		am::Synth::VoiceHandle* handle = vm.NoteOn(note, velocity);
		if(!handle) {
			Cerr() << "Failed NoteOn for note " << note << "\n";
			return 1;
		}
	}

	for(int i = 0; i < polyphony; ++i) {
		vm.NoteOff(60 + (i % 12));
	}

	vm.AllNotesOff();
	if(vm.GetActiveVoiceCount() != 0) {
		Cerr() << "VoiceManager still has active notes after AllNotesOff\n";
		return 1;
	}

	Cout() << "MIDI note simulation passed with polyphony=" << polyphony << "\n";
	return 0;
}

int CuteCli::CmdRenderWav(const Vector<String>& args) const {
	if(args.GetCount() < 2) {
		Cerr() << "render_wav requires <output_wav> [seconds]\n";
		return 2;
	}

	const String output_wav = NormalizePath(GetArg(args, 1));
	const double seconds = max(0.1, StrDbl(GetArg(args, 2, "2.0")));
	const int sample_rate = 48000;
	const int channels = 2;
	const int frames = int(seconds * sample_rate);

	am::AudioBuffer buffer;
	buffer.Resize(channels, frames);
	buffer.rate = sample_rate;

	for(int i = 0; i < frames; ++i) {
		double t = double(i) / double(sample_rate);
		float sample = (float)(0.25 * sin(2.0 * M_PI * 440.0 * t));
		for(int c = 0; c < channels; ++c)
			buffer.data[c][i] = sample;
	}

	const String out_dir = GetFileDirectory(output_wav);
	if(!IsNull(out_dir) && !DirectoryExists(out_dir) && !RealizeDirectory(out_dir)) {
		Cerr() << "Failed to create output directory: " << out_dir << "\n";
		return 1;
	}

	if(!am::WavFile::Save(output_wav, buffer, 16)) {
		Cerr() << "WAV render failed: " << output_wav << "\n";
		return 1;
	}

	Cout() << "Rendered WAV: " << output_wav << " (" << frames << " frames)\n";
	return 0;
}

int CuteCli::CmdSmoke(const Vector<String>& args) const {
	if(args.GetCount() < 2) {
		Cerr() << "smoke requires <output_dir>\n";
		return 2;
	}
	String output_dir = NormalizePath(GetArg(args, 1));

	Vector<String> create_args;
	create_args << "create_project" << output_dir << "smoke_project";
	int rc = CmdCreateProject(create_args);
	if(rc)
		return rc;

	Vector<String> midi_args;
	midi_args << "test_midi_notes" << "12";
	rc = CmdTestMidiNotes(midi_args);
	if(rc)
		return rc;

	Vector<String> render_args;
	render_args << "render_wav" << AppendFileName(output_dir, "smoke_render.wav") << "1.5";
	rc = CmdRenderWav(render_args);
	if(rc)
		return rc;

	Cout() << "Smoke test complete in: " << output_dir << "\n";
	return 0;
}

int CuteCli::Run(const Vector<String>& args) {
	if(args.IsEmpty())
		return ShowHelp();

	const String cmd = ToLower(args[0]);
	Vector<String> cmd_args;
	cmd_args << cmd;
	for(int i = 1; i < args.GetCount(); ++i)
		cmd_args << args[i];

	if(cmd == "help")
		return ShowHelp();
	if(cmd == "create_project")
		return CmdCreateProject(cmd_args);
	if(cmd == "test_midi_notes")
		return CmdTestMidiNotes(cmd_args);
	if(cmd == "render_wav")
		return CmdRenderWav(cmd_args);
	if(cmd == "smoke")
		return CmdSmoke(cmd_args);

	Cerr() << "Unknown command: " << cmd << "\n";
	return ShowHelp();
}

CONSOLE_APP_MAIN {
	CuteCli cli;
	SetExitCode(cli.Run(CommandLine()));
}
