#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <ProjectMgmt/ProjectMgmt.h>
#include <ProjectMgmt/Commands.h>
#include <ProjectMgmt/History.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test ProjectMgmt functionality
    {
        LOG("Testing ProjectMgmt functionality...");
        
        // Test basic project operations
        Project project;
        assert(project.GetTitle().IsEmpty());
        
        project.SetTitle("Test Project");
        assert(project.GetTitle() == "Test Project");
        
        LOG("Project title test passed");
    }

    // Test CommandManager functionality
    {
        LOG("Testing CommandManager functionality...");
        
        CommandManager cmdMgr;
        assert(cmdMgr.GetCommandCount() == 0);
        
        // Add a test command
        CommandID testCmd = CommandID::ForName("TestCommand");
        cmdMgr.RegisterCommand(testCmd, "Test Command", "Test command description");
        assert(cmdMgr.GetCommandCount() == 1);
        
        LOG("CommandManager test passed");
    }

    // Test History/Undo functionality
    {
        LOG("Testing History functionality...");
        
        History history;
        assert(history.CanUndo() == false);
        assert(history.CanRedo() == false);
        
        // Add a command to history
        CommandID testCmd = CommandID::ForName("TestCommand");
        history.PushCommand(testCmd, "Test command executed");
        assert(history.CanUndo() == true);
        
        LOG("History test passed");
    }
    
    LOG("All ProjectMgmt tests passed!");
}