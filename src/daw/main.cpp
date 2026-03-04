#include "daw.h"

#ifdef flagMAIN
GUI_APP_MAIN {
	StdLogSetup(LOG_COUT | LOG_FILE);

	const Vector<String>& args = CommandLine();
	String test_script;
	for(int i = 0; i < args.GetCount(); i++) {
		if(args[i] == "--test" && i + 1 < args.GetCount()) {
			test_script = args[i + 1];
			break;
		}
	}

	if(!test_script.IsEmpty()) {
		One<MainWindow> main;
		main.Create();
		main->Open();

		PyVM vm;
		RegisterAutomationBindings(vm);
		SetCurrentVM(&vm);

		try {
			String source = LoadFile(test_script);
			if(source.IsEmpty())
				throw Exc("Could not load test script: " + test_script);

			Vector<ProcMsg> errors;
			Tokenizer tokenizer;
			tokenizer.WhenMessage << [&](const ProcMsg& m) {
				if(m.severity == PROCMSG_ERROR)
					errors.Add(m);
			};
			tokenizer.SkipComments();
			tokenizer.SkipPythonComments(true);
			if(!tokenizer.Process(source, test_script)) {
				Cout() << "Tokenization failed:\n";
				for(const auto& e : errors)
					Cout() << e.line << ":" << e.col << ": " << e.msg << "\n";
				_exit(1);
			}
			tokenizer.NewlineToEndStatement();
			tokenizer.CombineTokens();

			PyCompiler compiler(tokenizer.GetTokens());
			Vector<PyIR> ir;
			compiler.Compile(ir);
			vm.SetIR(ir);

			Atomic exit_code;
			exit_code = -1;

			Thread test_thread;
			test_thread.Run([&] {
				try {
					vm.Run();
					exit_code = 0;
				}
				catch(const Exc& e) {
					if(e.Find("EXIT:0") >= 0)
						exit_code = 0;
					else {
						Cout() << "Test Error: " << e << "\n";
						exit_code = 1;
					}
				}
			});

			while(exit_code == -1) {
				Ctrl::ProcessEvents();
				Sleep(10);
			}
			_exit((int)exit_code);
		}
		catch(const Exc& e) {
			if(e.Find("EXIT:0") >= 0)
				_exit(0);
			Cout() << "Test Error: " << e << "\n";
			_exit(1);
		}
	}

	MainWindow().Run();
}
#endif
