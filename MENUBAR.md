File sub-menu entries:
- New Project
- New Library
- Open...
- Open Library
- Close
- <separator>
- Save
- Save As
- Back up Project
- Save as Template
- Save Library...
- Revert
- <separator>
- Import { Audio File... ; Video File... ; Audio from Video File...; MIDI File...; Track Archive...; Tempo Track...; MusicXML...; OMF... }
- Export { MIDI File... ; MIDI Loop... ; Audio Mixdown...; Selected Tracks...; Tempo Track...; Scores...; MusicXML...; OMF...}
- Replace Audio in Video File...
- Cleanup...
- <Separator>
- Preferences...
- Key Commands...
- <Separator>
- Recent Projects { [list of recent project file names]}
- <Separator>
- Quit

Edit sub-menu entries:
- Undo
- Redo
- History...
- <separator>
- Cut
- Copy
- Paste
- Paste at Origin
- Delete
- Split at Cursor
- Split Loop
- Range { Global Copy ; Cut Time ; Delete Time ; Paste Time ; Paste Time at Origin ; Split ; Crop ; Insert Silence }
- <separator>
- Select {All ; None ; Invert ; In Loop ; From Start to Cursor ; From Cursor to End ; Equal Pich - all Octaves ; Equal Pitch - same Octave ; Select Controllers in Note Range ; All on Selected Tracks ; Select Event ; Left Selection Side to Cursor ; Right Selection Side to Cursor}
- <separator>
- Duplicate
- Repeat...
- Fill Loop
- Move to {Cursor ; Origin ; Front ; Back}
- Convert to Real Copy
- Group
- Ungroup
- Lock...
- Unlock
- Mute
- Unmute
- Project Logical Editor...
- Process Project Logical Editor {
    Examples {
        - Colorize small MIDI parts
        - Delete Volume Automation
        - English to Finnish conversion
        - Move selected events by 1000 bars
        - Randomize Start Position for MIDI Parts by 10 Ticks
        - Select MIDI Parts named Drum
        - Toggle Folder open state if name contains MIDI
    };
    Naming {
        - Add a Date to selected MIDI + Audio Tracks
        - Rename and Renumber Audiotracks
    };
    Parts + Events {
        Delete Events beyond Song cursor
        Delete Timesignatures
        Delete all Automation beyond cursor
        Delete empty parts
        Delete muted MIDI parts
        Delete muted elements
        Delete small Part and Events
        Quantize 16th if selected
        Quantize 8th if selected
        Quantize Start by 480 ticks if unquantized
        Select if exactly matching cycle
        Select if not on the beat
        Set length to one bar if less than one bar
        Shift events by 2 frames
        Shift selected events by 2 frames
        Trim selected Automation by 10%
    };
    Tracks {
        Delete MIDI Tracks
        Delete all Automation Tracks
        Delete empty tracks
        Delete muted tracks
        Toggle Folder open state
        Toggle Inserts Bypass for MIDI
        Toggle Mut eMIDI Tracks
        Toggle Mute, if name contains voc
        Toggle lanes activitiesUnmute all muted MIDI tracks
    };
    Init
}
- (x) Automation follow Events
- Auto Select Events under Cursor
- Enlarge Selected Track
- <separator>
- Zoom {Zoom In ; Zoom Out ; Zoom ull ; Zoom to Selection ; Zoom to Selection (Horiz.) ; Zoom to Event ; <sep> ; Zoom In Vertically ; Zoom Out Vetically ; Zoom In Tracks ; Zoom Out Tracks ; Zoom Selected Tracks ; <sep> ; Undo Zoom ; Redo Zoom}


Project sub-menu items:
- Add Track { Audio ; Instrument ; MIDI ; <sep> ; Arranger ; FX Channel ; Folder ; Group Channel ; Marker ; Ruler ; Signature  ;Tempo ; Transpose ; Video ; <sep> ; Browse Sounds...}
- <separator>
- Duplicate Tracks
- Remove Selected Tracks
- Remove Empty Tracks
- <separator>
- Track Folding { Toggle Selected Track ; Fold Tracks ; Unfold Tracks Flip Fold States ; <sep> Show All Used Automation ; Hide All Automation }
- <separator>
- Pool
- Markers
- Tempo Track
- Browser
- Automation panel
- Beat Calculator...
- Se Timecode at Cursor
- Notepad
- <separator>
- Project Setup...
- Auto Fades Settings...


Audio sub-menu items:
- Process { Envelope ; Fade In ; Fade Out ; Gain ; Merge Clipboard ; Noise GAte ; Normalize ; Phase Reverse ; Pitch Shift ; Remove DC Offset ; Resample ; Reverse ; Silence ; Stereo Flip ; Time Stretch }
- Plug-ins { [list of system plugins (VST, LV2, LADSPA, CLAP)]}
- Spectrum Analyzer
- Statistics
- Hitpoints {Calculate Hitpoints ; Create Audio Slices from Hitpoints ; Create Groove Qunatizze from Hitpoints ; Create Markers from Hitpoints ; Divide Audio Events at Hitpoints ; Remove Hitpoints}
- Realtime Processing {Create Warp Tabs from Hitpoints ; Quantize Audio ; Flatten ; Unstretch Audio}
- Advanced {Detecht Silence ; Event or Range as Region ; EVents from REgions ; Set Tempo From Event ; Close Gaps ; Stretch to Project Tempo ; Delete Overlaps}
- Events t o PArt
- Dissolve Part
- Snap Point to Cursor
- Bounce Selection
- Find Selected in Pool
- Update Origin
- <separator>
- Crossfade
- Remove Fades
- Open Fade Editor(s)
- Adjust Fades to Range
- Fade In to Cursor
- Fade Out to Cursor
- Remove Volume Curve
- <separator>
- Offline Process History...
- Freeze Edits...


MIDI sub-menu items:
- Open Key Editor
- Open Score Editor
- Open Drum Editor
- Open List Editor
- Open In-Place Editor
- <separator>
- Over Quantize
- Iterative Quantize
- Quantize Setup...
- Advanced Quantize {Quantize Lengths ; Quantize Ends ; Undo Quantize ; Freeze Quantize ; Part to Groove }
- <separator>
- Transpose...
- Merge MIDI in Loop...
- Freeze MIDI Modifiers
- Dissolve Part
- Bounce Selection
- O-Note Conversion
- Repeat Loop
- Functions {Legato ; Fixed Lengths ; Delete Doubles ; Delete Controllers ; Delete Continuous Controllers ; Delete Notes... ; Restrict Polyphony ; Pedals to Note Length ; Delete Overlaps (mono) ; Delete Overlaps (poly) ; Velocity... ; Fixed Velocity ; Thin Out Data ; Extract MIDI Automation ; Reverse ; Merge Tempo from Tapping }
- <separator>
- Logical Editor...
- Logical Presets {
    Added for Version 3 {
        Add Note [+12], if Mod/Wheel is above 64
        Delete SMF Events
        Delete all Controllers in Cycle RAnge
        Delete each 5th note
        Kill Notes on C-Major
        Scale down Velocity in Sustain Range
        Select all Events beyond Cursor
        Select all Events in Cycle Range
        Shift Key C1 Transpose by 24
        Shift Notes by 12 Ticks beyond Cursor
        Transform Notes after D#3 or C#3
        Transpose EventsInSistainRange
    };
    experimental {
        add volume 0 to end of note
        delete black keys
        downbeat accent (4, -4)
        extract volume and pan
        filter off beats
        insert mid ivolume for velocity
    };
    standard set 1 {
        delete muted
        delete short notes
        double tempo
        fixed velocity 100
        half tempo
        push back -4
        push forward +4
        random notes (c3 to c5)
        random velocity (60 to 100)
    };
    standard set 2 {
        del patch changes
        del velocity below 30
        del velocity below 35
        del velocity below 40
        del velocity below 45
        del.aftertouch
        extract note (c3 60)
        high notes to channel 1
        low notes to channel 2
        set notes to fixed pitch (c3)
        transpose +12
        transpose -12
    };
}
- Drum Map Setup...
- Insert Velocities...
- VST Expression Setup...
- CC Automation Setup...
- <separator>
- Reset


Scores sub-menu items:
- Open Selection
- Open Layout
- <separator>
- Page Mode
- <separator>
- Settings...
- <separator>
- Group/Ungroup Notes
- Convert to Grace Note
- Build N-Tuplet...
- Inser Slur
- Hide/Show
- Flip
- <separator>
- Align Elements { Left ;Right ; Top ; Bottom; Center Vertically ; Center Horizontally ; Dynamics}
- <separator>
- Make Chord Symbols
- Make Guitar Symbols
- <separator>
- Functions { Merge All Staves ; Extract Voices ; Explode ; <sep> ; Scores Notes to MIDI ; Lyrics From Clipboard ; Text From Clipboard ; <sep> Find and Replace... ; Force Update}
- <separator>
- Auto Layout...
- Reset Layout...
- Advanced Layout {Number of Bars ; <sep> ; Display Markers ; Marker Track to Form}


Media sub-menu items:
- Open Pool Window
- <separator>
- Open MediaBay
- Open Loop Browser
- Open Sound Browser
- <separator>
- Import Medium...
- Import Audio CD...
- Import Pool...
- Export Pool...
- <separator>
- Find Missing Files...
- Remove Missing Files
- Reconstruct
- Convert Files...
- Conform Files...
- Extract Audio from Video File
- Generate Thumbnail Cache
- <separator>
- Create Folder
- Empty Trash
- Remove Unused Media
- Prepare Archive...
- Set Pool Record Folder
- <separator>
- Minimize File
- New Version
- Insert into Project {At Cursor ; At Left Locator ; At Origin}
- Select in Project
- Search Media...


Transport Sub-menu Items:
- (x) Transport Panel
- <separator>
- Locators to Selection
- Locate Selection
- Locate Selection End
- Locate Next Marker
- Locat ePrevious Marker
- Locate Next Event
- Locat ePrevious Event
- <separator>
- Post-roll from Selection Start
- Post-roll from Selection End
- Pre-roll to Selection Start
- Pre-roll to Selction End
- Play from Selection Start
- Play from Selection End
- Play until Selection Start
- Play until Selection End
- Play until Next Marker
- Play Selection Range
- Loop Selection
- <separator>
- Use Pre-roll
- Use Post-roll
- Start Record at Left Locator
- <separator>
- Metronome Setup...
- Metronome On
- Precount On
- <separator>
- Project Synchronization Setup...
- Use External Sync
- <separator>
- Retrospective Record


Device sub-menu items:
- Control Room Mixer
- Control Room Overview
- MIDI Device Manager
- MMC MAster
- Mixer
- Mixer 2
- Mixer 3
- Plug-in Information
- Remaining Record Time Display
- Time Display
- VST Connections
- VST Instruments
- VST Performance
- Video Window
- VIrtual Keyboard
- <separator>
- FL Studio ReWire
- Melodyne ReWire
- Waves ReWire
- <separator>
- Show Panel
- <separator>
- Device Setup...


Window sub-menu items:
- Minimize
- Maximize
- <separator>
- Close All
- Minimize All
- Restore All
- <separator>
- Workspaces {Lock Active Workspace ; New Workspace ; Organize ; <sep> ; [List of workspaces]}
- Windows...
- <separator>
- Transport
- <a filename == project file window>
- <a filename == library file>


Help sub-menu items:
- MasterLab on the Web {Visit MasterLab website ; Visit MasterLab github page}
- <separator>
- Registration
- <separator>
- Credits and Copyrights {[list of copyright holders]}
- About MasterLab


Those "..." postfixes reveals if it is a single function call or if it requires some sort of additional popup-window or something else more complicated.
That {} is sub-sub-menu, with ; to separate entries, and with <sep> marking a separator.
() or (x) means that it is visuable toggleable.
? in front of item means that it is not enabled by default and is non-clickable. The logic for enabling is still unclear for now.

