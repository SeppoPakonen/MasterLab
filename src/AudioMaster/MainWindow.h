#ifndef _AudioMaster_MainWindow_h_
#define _AudioMaster_MainWindow_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h>
#include <AudioFX/AudioFX.h>
#include <AudioGraph/AudioGraph.h>
#include <Browser/Browser.h>
#include <HelpAbout/HelpAbout.h>
#include <Math/Math.h>
#include <MIDI/MIDI.h>
#include <ProjectMgmt/ProjectMgmt.h>
#include <ProjectWindow/ProjectWindow.h>
#include <ProjectSetup/ProjectSetup.h>
#include <ScoresEngine/ScoresEngine.h>
#include <Tooling/Tooling.h>
#include <TransportPrefs/TransportPrefs.h>
#include <TransportUI/TransportUI.h>
#include <Video/Video.h>
#include <VSTHost/VstHostPrefs.h>
#include <Windowing/Windowing.h>
#include <MediaPool/MediaPool.h>
#include <ExportAudioMixdown/ExportAudioMixdown.h>
#include <FileIO/FileIO.h>
#include <Devices/Devices.h>
#include <Editors/Editors.h>
#include <AudioMaster/AudioMaster.h>
#include <PluginSDK/PluginSDK.h>
#include <SubWindowCtrl/SubWindowCtrl.h>
// #include <ProjectWindow/ProjectWindowHost.h>
// #include <MediaPool/PoolWindow.h>
using namespace Upp;

// Forward declarations
class MainView;
class SubWindow;

class MainWindow : public TopWindow {
	
public:
	typedef MainWindow CLASSNAME;
	MainWindow();
	void SetView(int type);
	void RefreshTitle();
	void InitView(MainView& v, Ptr<SubWindow>& win);
	
private:
	void Menu(Bar& bar);
	void OnFile(Bar& bar);
	void OnEdit(Bar& bar);
	void OnProject(Bar& bar);
	void OnAudio(Bar& bar);
	void OnMIDI(Bar& bar);
	void OnScores(Bar& bar);
	void OnMedia(Bar& bar);
	void OnTransport(Bar& bar);
	void OnDevices(Bar& bar);
	void OnWindow(Bar& bar);
	void OnHelp(Bar& bar);

	void OnMasteringView();
	void OnMultiChannelView();
	void OnMixerView();
	void OnAnalysisView();
	void OnCombinedView();
	void OnPostView();
	void OnPostGraphView();
	
	// File menu functions
	void OnNewProject();
	void OnNewLibrary();
	void OnOpen();
	void OnOpenLibrary();
	void OnClose();
	void OnSave();
	void OnSaveAs();
	void OnBackupProject();
	void OnSaveAsTemplate();
	void OnSaveLibrary();
	void OnRevert();
	void OnImportAudioFile();
	void OnImportVideoFile();
	void OnImportAudioFromVideo();
	void OnImportMIDIFile();
	void OnImportTrackArchive();
	void OnImportTempoTrack();
	void OnImportMusicXML();
	void OnImportOMF();
	void OnExportMIDIFile();
	void OnExportMIDILoop();
	void OnExportAudioMixdown();
	void OnExportSelectedTracks();
	void OnExportTempoTrack();
	void OnExportScores();
	void OnExportMusicXML();
	void OnExportOMF();
	void OnReplaceAudioInVideo();
	void OnCleanup();
	void OnPreferences();
	void OnKeyCommands();
	void OnQuit();
	
	// Edit menu functions
	void OnUndo();
	void OnRedo();
	void OnHistory();
	void OnCut();
	void OnCopy();
	void OnPaste();
	void OnPasteAtOrigin();
	void OnDelete();
	void OnSplitAtCursor();
	void OnSplitLoop();
	void OnRangeGlobalCopy();
	void OnRangeCutTime();
	void OnRangeDeleteTime();
	void OnRangePasteTime();
	void OnRangePasteTimeAtOrigin();
	void OnRangeSplit();
	void OnRangeCrop();
	void OnRangePasteSilence();
	void OnSelectAll();
	void OnSelectNone();
	void OnSelectInvert();
	void OnSelectInLoop();
	void OnSelectFromStartToCursor();
	void OnSelectFromCursorToEnd();
	void OnSelectEqualPitchAllOctaves();
	void OnSelectEqualPitchSameOctave();
	void OnSelectControllersInNoteRange();
	void OnSelectAllOnSelectedTracks();
	void OnSelectEvent();
	void OnSelectLeftSelectionSideToCursor();
	void OnSelectRightSelectionSideToCursor();
	void OnDuplicate();
	void OnRepeat();
	void OnFillLoop();
	void OnMoveToCursor();
	void OnMoveToOrigin();
	void OnMoveToFront();
	void OnMoveToBack();
	void OnConvertToRealCopy();
	void OnGroup();
	void OnUngroup();
	void OnLock();
	void OnUnlock();
	void OnMute();
	void OnUnmute();
	void OnProjectLogicalEditor();
	void OnProcessColorizeSmallMIDIParts();
	void OnProcessDeleteVolumeAutomation();
	void OnProcessEnglishToFinnishConversion();
	void OnProcessMoveSelectedEventsBy1000Bars();
	void OnProcessRandomizeStartPosition();
	void OnProcessSelectMIDIPartsNamedDrum();
	void OnProcessToggleFolderMIDI();
	void OnProcessAddDateToSelected();
	void OnProcessRenameAndRenumberAudioTracks();
	void OnProcessDeleteEventsBeyondSongCursor();
	void OnProcessDeleteTimesignatures();
	void OnProcessDeleteAllAutomationBeyondCursor();
	void OnProcessDeleteEmptyParts();
	void OnProcessDeleteMutedMIDIParts();
	void OnProcessDeleteMutedElements();
	void OnProcessDeleteSmallPartsAndEvents();
	void OnProcessQuantize16th();
	void OnProcessQuantize8th();
	void OnProcessQuantizeStartBy480Ticks();
	void OnProcessSelectIfExactlyMatchingCycle();
	void OnProcessSelectIfNotOnTheBeat();
	void OnProcessSetLengthToOneBar();
	void OnProcessShiftEventsBy2Frames();
	void OnProcessShiftSelectedEventsBy2Frames();
	void OnProcessTrimSelectedAutomation();
	void OnProcessDeleteMIDITracks();
	void OnProcessDeleteAllAutomationTracks();
	void OnProcessDeleteEmptyTracks();
	void OnProcessDeleteMutedTracks();
	void OnProcessToggleFolderOpenState();
	void OnProcessToggleInsertsBypassMIDI();
	void OnProcessToggleMuteMIDITracks();
	void OnProcessToggleMuteIfNameContainsVoc();
	void OnProcessToggleLanesActivities();
	void OnProcessUnmuteAllMutedMIDITracks();
	void OnProcessInit();
	void OnToggleAutomationFollowEvents();
	void OnToggleAutoSelectEventsUnderCursor();
	void OnEnlargeSelectedTrack();
	
	// Dynamic check functions (for checkboxes)
	bool IsAutomationFollowEvents();
	bool IsAutoSelectEventsUnderCursor();
	void OnZoomIn();
	void OnZoomOut();
	void OnZoomFull();
	void OnZoomToSelection();
	void OnZoomToSelectionHoriz();
	void OnZoomToEvent();
	void OnZoomInVertically();
	void OnZoomOutVertically();
	void OnZoomInTracks();
	void OnZoomOutTracks();
	void OnZoomSelectedTracks();
	void OnUndoZoom();
	void OnRedoZoom();
	
	// Project menu functions
	void OnAddAudioTrack();
	void OnAddInstrumentTrack();
	void OnAddMIDITrack();
	void OnAddArrangerTrack();
	void OnAddFXChannel();
	void OnAddFolder();
	void OnAddGroupChannel();
	void OnAddMarker();
	void OnAddRuler();
	void OnAddSignature();
	void OnAddTempo();
	void OnAddTranspose();
	void OnAddVideo();
	void OnBrowseSounds();
	void OnDuplicateTracks();
	void OnRemoveSelectedTracks();
	void OnRemoveEmptyTracks();
	void OnToggleSelectedTrack();
	void OnFoldTracks();
	void OnUnfoldTracks();
	void OnFlipFoldStates();
	void OnShowAllUsedAutomation();
	void OnHideAllAutomation();
	void OnPool();
	void OnMarkers();
	void OnTempoTrack();
	void OnBrowser();
	void OnAutomationPanel();
	void OnBeatCalculator();
	void OnSetTimecodeAtCursor();
	void OnNotepad();
	void OnProjectSetup();
	void OnAutoFadesSettings();
	
	// Audio menu functions
	void OnProcessEnvelope();
	void OnProcessFadeIn();
	void OnProcessFadeOut();
	void OnProcessGain();
	void OnProcessMergeClipboard();
	void OnProcessNoiseGate();
	void OnProcessNormalize();
	void OnProcessPhaseReverse();
	void OnProcessPitchShift();
	void OnProcessRemoveDCOffset();
	void OnProcessResample();
	void OnProcessReverse();
	void OnProcessSilence();
	void OnProcessStereoFlip();
	void OnProcessTimeStretch();
	void OnSpectrumAnalyzer();
	void OnStatistics();
	void OnCalculateHitpoints();
	void OnCreateAudioSlicesFromHitpoints();
	void OnCreateGrooveQuantizeFromHitpoints();
	void OnCreateMarkersFromHitpoints();
	void OnDivideAudioEventsAtHitpoints();
	void OnRemoveHitpoints();
	void OnCreateWarpTabsFromHitpoints();
	void OnQuantizeAudio();
	void OnFlatten();
	void OnUnstretchAudio();
	void OnDetectSilence();
	void OnEventOrRangeAsRegion();
	void OnEventsFromRegions();
	void OnSetTempoFromEvent();
	void OnCloseGaps();
	void OnStretchToProjectTempo();
	void OnDeleteOverlaps();
	void OnEventsToPart();
	void OnDissolvePart();
	void OnSnapPointToCursor();
	void OnBounceSelection();
	void OnFindSelectedInPool();
	void OnUpdateOrigin();
	void OnCrossfade();
	void OnRemoveFades();
	void OnOpenFadeEditor();
	void OnAdjustFadesToRange();
	void OnFadeInToCursor();
	void OnFadeOutToCursor();
	void OnRemoveVolumeCurve();
	void OnOfflineProcessHistory();
	void OnFreezeEdits();
	
	// MIDI menu functions
	void OnOpenKeyEditor();
	void OnOpenScoreEditor();
	void OnOpenDrumEditor();
	void OnOpenListEditor();
	void OnOpenInPlaceEditor();
	void OnOverQuantize();
	void OnIterativeQuantize();
	void OnQuantizeSetup();
	void OnQuantizeLengths();
	void OnQuantizeEnds();
	void OnUndoQuantize();
	void OnFreezeQuantize();
	void OnPartToGroove();
	void OnTranspose();
	void OnMergeMIDIInLoop();
	void OnFreezeMIDIModifiers();
	void OnONoteConversion();
	void OnRepeatLoop();
	void OnLegato();
	void OnFixedLengths();
	void OnDeleteDoubles();
	void OnDeleteControllers();
	void OnDeleteContinuousControllers();
	void OnDeleteNotes();
	void OnRestrictPolyphony();
	void OnPedalsToNoteLength();
	void OnDeleteOverlapsMono();
	void OnDeleteOverlapsPoly();
	void OnVelocity();
	void OnFixedVelocity();
	void OnThinOutData();
	void OnExtractMIDIAutomation();
	void OnReverse();
	void OnMergeTempoFromTapping();
	void OnLogicalEditor();
	void OnAddNoteIfModAbove64();
	void OnDeleteSMFEvents();
	void OnDeleteAllControllersInCycleRange();
	void OnDeleteEach5thNote();
	void OnKillNotesOnCMajor();
	void OnScaleDownVelocityInSustainRange();
	void OnSelectAllEventsBeyondCursor();
	void OnSelectAllEventsInCycleRange();
	void OnShiftKeyC1TransposeBy24();
	void OnShiftNotesBy12TicksBeyondCursor();
	void OnTransformNotesAfterDSharp3();
	void OnTransposeEventsInSustainRange();
	void OnAddVolume0ToEndOfNote();
	void OnDeleteBlackKeys();
	void OnDownbeatAccent();
	void OnExtractVolumeAndPan();
	void OnFilterOffBeats();
	void OnInsertMidIVolumeForVelocity();
	void OnDeleteMuted();
	void OnDeleteShortNotes();
	void OnDoubleTempo();
	void OnFixedVelocity100();
	void OnHalfTempo();
	void OnPushBack4();
	void OnPushForward4();
	void OnRandomNotes();
	void OnRandomVelocity();
	void OnDelPatchChanges();
	void OnDelVelocityBelow30();
	void OnDelVelocityBelow35();
	void OnDelVelocityBelow40();
	void OnDelVelocityBelow45();
	void OnDelAftertouch();
	void OnExtractNote();
	void OnHighNotesToChannel1();
	void OnLowNotesToChannel2();
	void OnSetNotesToFixedPitch();
	void OnTransposePlus12();
	void OnTransposeMinus12();
	void OnDrumMapSetup();
	void OnInsertVelocities();
	void OnVSTExpressionSetup();
	void OnCCAutomationSetup();
	void OnReset();
	
	// Scores menu functions
	void OnOpenSelection();
	void OnOpenLayout();
	void OnPageMode();
	void OnSettings();
	void OnGroupUngroupNotes();
	void OnConvertToGraceNote();
	void OnBuildNTuplet();
	void OnInsertSlur();
	void OnHideShow();
	void OnFlip();
	void OnAlignLeft();
	void OnAlignRight();
	void OnAlignTop();
	void OnAlignBottom();
	void OnAlignCenterVertically();
	void OnAlignCenterHorizontally();
	void OnAlignDynamics();
	void OnMakeChordSymbols();
	void OnMakeGuitarSymbols();
	void OnMergeAllStaves();
	void OnExtractVoices();
	void OnExplode();
	void OnScoresNotesToMIDI();
	void OnLyricsFromClipboard();
	void OnTextFromClipboard();
	void OnFindAndReplace();
	void OnForceUpdate();
	void OnAutoLayout();
	void OnResetLayout();
	void OnAdvancedLayoutNumberOfBars();
	void OnAdvancedLayoutDisplayMarkers();
	void OnAdvancedLayoutMarkerTrackToForm();
	
	// Media menu functions
	void OnOpenPoolWindow();
	void OnOpenMediaBay();
	void OnOpenLoopBrowser();
	void OnOpenSoundBrowser();
	void OnImportMedium();
	void OnImportAudioCD();
	void OnImportPool();
	void OnExportPool();
	void OnFindMissingFiles();
	void OnRemoveMissingFiles();
	void OnReconstruct();
	void OnConvertFiles();
	void OnConformFiles();
	void OnExtractAudioFromVideoFile();
	void OnGenerateThumbnailCache();
	void OnCreateFolder();
	void OnEmptyTrash();
	void OnRemoveUnusedMedia();
	void OnPrepareArchive();
	void OnSetPoolRecordFolder();
	void OnMinimizeFile();
	void OnNewVersion();
	void OnInsertIntoProject();
	void OnInsertAtCursor();
	void OnInsertAtLeftLocator();
	void OnInsertAtOrigin();
	void OnSelectInProject();
	void OnSearchMedia();
	
	// Transport menu functions
	void OnToggleTransportPanel();
	bool IsTransportPanel();
	void OnLocatorsToSelection();
	void OnLocateSelection();
	void OnLocateSelectionEnd();
	void OnLocateNextMarker();
	void OnLocatePreviousMarker();
	void OnLocateNextEvent();
	void OnLocatePreviousEvent();
	void OnPostRollFromSelectionStart();
	void OnPostRollFromSelectionEnd();
	void OnPreRollToSelectionStart();
	void OnPreRollToSelectionEnd();
	void OnPlayFromSelectionStart();
	void OnPlayFromSelectionEnd();
	void OnPlayUntilSelectionStart();
	void OnPlayUntilSelectionEnd();
	void OnPlayUntilNextMarker();
	void OnPlaySelectionRange();
	void OnLoopSelection();
	void OnUsePreRoll();
	void OnUsePostRoll();
	void OnStartRecordAtLeftLocator();
	void OnMetronomeSetup();
	void OnMetronomeOn();
	void OnPrecountOn();
	void OnProjectSyncSetup();
	void OnUseExternalSync();
	void OnRetrospectiveRecord();
	
	// Devices menu functions
	void OnControlRoomMixer();
	void OnControlRoomOverview();
	void OnMIDIDeviceManager();
	void OnMMCMaster();
	void OnMixer();
	void OnMixer2();
	void OnMixer3();
	void OnPluginInformation();
	void OnRemainingRecordTimeDisplay();
	void OnTimeDisplay();
	void OnVSTConnections();
	void OnVSTInstruments();
	void OnVSTPerformance();
	void OnVideoWindow();
	void OnVirtualKeyboard();
	void OnFLStudioReWire();
	void OnMelodyneReWire();
	void OnWavesReWire();
	void OnShowPanel();
	void OnDeviceSetup();
	
	// Window menu functions
	void OnMinimize();
	void OnMaximize();
	void OnCloseAll();
	void OnMinimizeAll();
	void OnRestoreAll();
	void OnLockActiveWorkspace();
	void OnNewWorkspace();
	void OnOrganize();
	void OnWindows();
	void OnTransportWindow();
	void OnProjectFileWindow();
	void OnLibraryFileWindow();
	
	// Help menu functions
	void OnVisitMasterLabWebsite();
	void OnVisitMasterLabGithub();
	void OnRegistration();
	void OnAboutMasterLab();

	MenuBar menu;
	StatusBar status;
	SubWindows workspace;
	Ptr<Ctrl> currentView;
	
	// View instances
	MasteringView masteringView;
	MultiChannelView multiChannelView;
	MixerView mixerView;
	AnalysisView analysisView;
	CombinedView combinedView;
	PostViewWrapper postView;
	PostGraphViewWrapper postGraphView;
	
	// SubWindow instances to view
	Ptr<SubWindow> masteringWin;
	Ptr<SubWindow> multiChannelWin;
	Ptr<SubWindow> mixerWin;
	Ptr<SubWindow> analysisWin;
	Ptr<SubWindow> combinedWin;
	Ptr<SubWindow> postWin;
	Ptr<SubWindow> postGraphWin;

	One<am::PoolWindow> poolWindow;
	One<am::ProjectWindowHost> projectWindowHost;
	One<am::ExportAudioMixdownDialog> exportAudioMixdown;
	One<am::ProjectSetupDialog> projectSetup;

};

#endif
