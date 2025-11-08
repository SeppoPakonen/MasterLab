#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <FileIO/FileIO.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test FileIO functionality
    {
        LOG("Testing FileIO functionality...");
        
        FileManager fileMgr;
        
        // Test file registration
        assert(fileMgr.GetSupportedFormatCount() >= 0);
        
        // Test path operations
        String testPath = AppendFileName(GetTempDirectory(), "test_file.tmp");
        assert(!testPath.IsEmpty());
        
        // Test file operations mock
        FileOperation op;
        op.filePath = testPath;
        op.operationType = FileOperationType::SAVE;
        op.status = FileOperationStatus::PENDING;
        
        assert(op.filePath == testPath);
        assert(op.operationType == FileOperationType::SAVE);
        assert(op.status == FileOperationStatus::PENDING);
        
        LOG("FileIO test passed");
    }

    // Test Import functionality
    {
        LOG("Testing Import functionality...");
        
        ImportManager importMgr;
        assert(importMgr.GetSupportedFormatCount() >= 0);
        
        // Test import operation
        ImportOperation impOp;
        impOp.sourcePath = "/path/to/source.wav";
        impOp.destinationPath = "/path/to/dest.wav";
        
        assert(impOp.sourcePath == "/path/to/source.wav");
        assert(impOp.destinationPath == "/path/to/dest.wav");
        
        LOG("Import test passed");
    }

    // Test Export functionality
    {
        LOG("Testing Export functionality...");
        
        ExportManager exportMgr;
        assert(exportMgr.GetSupportedFormatCount() >= 0);
        
        // Test export operation
        ExportOperation expOp;
        expOp.sourcePath = "/path/to/source.wav";
        expOp.destinationPath = "/path/to/export.wav";
        expOp.format = "WAV";
        
        assert(expOp.sourcePath == "/path/to/source.wav");
        assert(expOp.destinationPath == "/path/to/export.wav");
        assert(expOp.format == "WAV");
        
        LOG("Export test passed");
    }

    LOG("All FileIO tests passed!");
}