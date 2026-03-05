#include "Cute.h"

#ifdef flagMAIN
GUI_APP_MAIN {
    const Vector<String>& args = CommandLine();
    int exit_code = RunCuteApplication(args);
    if(exit_code != 0)
        Exit(exit_code);
}
#endif
