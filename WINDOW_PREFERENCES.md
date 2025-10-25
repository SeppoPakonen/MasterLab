# Preferences
You open this menu via menubar: File -> Preferences...


## Content
- Main area: 100% horizontally, 80%, vertically: horizontal split (33% for TreeCtrl, 66% for view placeholder)
- Preference Presets: 100% horizontally, 16% vertically: Droplist for presets, Buttons { Store ; Rename ; Delete }; Option("Store marked preferences only")
- Buttons: 100% horizontally, 20px vertically: LEFT ALIGNED {Help } ; RIGHT_ALIGNED {Defaults ; Apply ; OK ; Cancel }


## Preference TreeCtrl content:
- Appearance
	- General
	- Meters
	- Work Area
- Editing
	- Audio
	- Controls
	- MIDI
	- Project & Mixer
	- Tool Modifiers
	- Tools
	- Video
- Event Display
	- Audio
	- MIDI
	- Rulers
	- Video
- General
	- MIDI
		- MIDI File
		- MIDI Filter
- MediaBay
- Record
	- Audio
		- Broadcast Wave
	- MIDI
- Scores
	- Colors for Additional Meanings
	- Editing
	- Note Layer
- Transport
	- Scrub
- VST
	- Plugins
	- Metering
	- Control Room
- VariAudio

### View content

#### Appearance
Empty

#### Appearance/General
- Preview image of mixer
- Interface Adjustments
	- Slider & Label("Saturation")
	- Slider & Label("Brightness")
	- Slider & Label("Button Brightness")


#### Appearance/Meters
- 100% vertically, 33% horizontally: VU-Meter
	- it has vertically moveable markers with color: they set the (faded) color at that vertical position of VU-meter
		- by clicking the marker user may edit the color (it sets the colorwheel and links it to the marker)
	- colors {100% : Wine red ; 75% Light Yellow ; 30% Light Green; 0% Light Blue}
- 100% vertically, 66% horizontally: Color editor

#### Appearance/Work Area
This allows changing linearly between dark and light themes. First slider affacts all color rects, but rest affects only their corresponding color rect.

These values affects the main view, where sound clips and midi clips resides. It has a grid in background etc. Colors of lines of grid can be edited here. Also background color etc.

These seem to edit also sequencer colors etc. Piano-roll color values

- Project Window
	- small color-rect; horz slider; Label("Work Area Brightness")
	- small color-rect; horz slider; Label("Cycle Intensity")
	- small color-rect; horz slider; Label("Horizontal Grid Intensity")
	- small color-rect; horz slider; Label("Vertical Grid Level 1")
	- small color-rect; horz slider; Label("Vertical Grid Level 2")
	- small color-rect; horz slider; Label("Vertical Grid Level 3")
- Edit Window
	- small color-rect; horz slider; Label("Horizontal Grid Intensity")
	- small color-rect; horz slider; Label("Vertical Grid Level 1")
	- small color-rect; horz slider; Label("Vertical Grid Level 2")
	- small color-rect; horz slider; Label("Vertical Grid Level 3")
- Key Editor
	- small color-rect; horz slider; Label("Black Note Grid Intensity")
- Drum Editor
	- small color-rect; horz slider; Label("Active Drum Lane Intensity")
	

#### Editing
- List of one liners
	- Droplist {Musical ; Time Linear ; Follow Transport Main Display } ; Label("Default Track Time Type")
	- Option(default=false); Label("Auto Select Events under Cursor")
	- Option(default=false); Label("Cycle Follows Range Selection")
	- Option(default=false); Label("Delete Overlaps")
	- Option(default=true); Label("Link Editors")
	- Option(default=false); Label("Parts Get Track Names")
	- Droplist { Position ; Size ; Position + Size ; Other ; Position + Other ; Size + Other ; (x)Position + Size + Other } ; Label("Lock Event Attributes")
	- Option(default=false); Label("Quick Zoom")
	- Option(default=false); Label("Use Up/Down Navigation Commands for Selecting Tracks only")
	- Option(default=false); Label("Track Selection Follows Event Selection")
	- Option(default=true); Label("Automation follows Events")
	- EditIntSpinNotNull(default="200 ms"); Label("Drag Delay")



#### Editing/Audio
- List of items: LabelBoxes and One liners
	- LabelBox("Time Stretch Tool")
		- DropList(MPEX 4 ; (x)Realtime); Label("Algorithm");
	- Option(default=true); Label("Treat Muted Audio Events like Deleted");
	- Option(default=false); Label("Use Mouse Wheel for Event Volume and Fades");
	- Option(default=false); Label("Hitpoints have Q-Points");
	- LabelBox("On Import Audio Files")
		- DropList(Open Options Dialog ; Use Settings);
		- Option(default=false, enabled-if: "Use Settings"); Label("Copy Files to Working Directory");
		- Option(default=false, enabled-if: "Use Settings"); Label("Convert and Copy to Project If Needed");
		- Option(default=false, enabled-if: "Use Settings"); Label("Split multi-channel files");
	- DropList(Open Options Dialog ; Assume New Versions ; Assume Skipping);
	- Option(default=false); Label("Remove Regions/Markers on all Offline PRocesses");
	- Option(default=false); Label("Snap to Zero Crossing");


#### Editing/Controls
- List of one liners
	- DropList(Text Input on Left-Click ; Increment/Decrement on Left/Right-Click ; (x) Increment/Decrement on Left-Click and Drag); Label("Value Box/Time Control Mode");
	- DropList(Circular ; Relative Circular ; (x)Linear); Label("Knob Mode");
	- DropList(Jump (Control) ; Touch (Control) ; Ramp ; Relative); Label("Slider Mode");
	
#### Editing/MIDI
- List of one liners
	- Option(default=false); Label("Select Controllers in Note Range Use Extended Note Context");
	- EditIntSpinNotNull(default="0 Ticks"); Label("Legato Overlap")
	- Option(default=false); Label("Legato Mode Selected Only");
	- Option(default=false); Label("Split MIDI Events");
	- Option(default=false); Label("Split MIDI Controllers");

#### Editing/Project & Mixer
- List of one liners
	- Option(default=false); Label("Select Channel/Track on Solo")
	- Option(default=true); Label("Select Channel/Track on Edit Settings")
	- DropList(Disabled ; Channel ; Track ; (x)Channel and Track); Label("Scroll to selected ...");
	- DropList(Use Default Event Color ; Use Previous Track Color ; (x) Use Previous Track Color +1 ; Use LAst Applied Color ; Use Random Track Color); Label("Auto Track Color Mode");
	- Option(default=true); Label("Sync Project and Mixer Selection")
	- Option(default=true); Label("Enable Record on Selected Track")
	- Option(default=false); Label("Enable Solo on Selected Track")
	- Option(default=false); Label("Deep Track Folding")
	- Option(default=false); Label("Enlarge Selected Track")


#### Editing/Tool Modifiers
- vertical 75%, horizontal 100%: section with category list and key-value-list
	- horizontal 33%: ArrayCtrl("Categories"-column);
	- horizontal 33%: ArrayCtrl("Action", "Modifiers" -columns);
	- categories: key / value. Values are default values, and they can be empty.
		- AudioWarp Tool
			- Delete Tab: Shift
		- Color Tool
			- Popup Event Colors: Ctrl
			- Sample Event Color: Alt
		- Controls
			- Rest to Default Value: Ctrl
		- Define Audio Grid
			- Adjust Tempo: Ctrl
		- Drag & Drop
			- Constraint Direction: Ctrl
			- Copy: Alt
			- Shared Copy: Alt+Shift
		- Edit Pitch/Warp Tool
			- Absolute Pitch Snapping: (none)
			- No Pitch Snapping: Shift
			- Relative Pitch Snapping: Ctrl
		- Erase Tool
			- Delete later events: Alt
		- Glue Tool
			- Glue All Following Events: Alt
		- Info Line
			- All Events Same Value: Ctrl
		- Range Tool
			- Exclude Row: Ctrl
			- Select Full Vertical: Ctrl+Shift
		- Select Tool
			- Edit Velocity: Ctrl+Shift
			- Slip Event: Ctrl+Alt
			- Split Event: Alt
		- Size Objects
			- Common Objects: (none)
			- Disable Snapping: Ctrl
			- Repeat Event: Alt
			- Time Stretch: (none)
		- Split Tool
			- Split repeated: Alt
		- Time Warp Tool
			- Create or Erase: Shift
			- No Correction: Alt
		- Trim Tool
			- Constrain Direction: Ctrl
			- Trim Start: Alt
- vertical 25%, horizontal 100%: editor to assign value to key-value-list selection
	- EditString: updates realtime and shows pressed modiefier keys (ctrl, alt, shift, alt, etc.)
	- Button("Assign"): sets the value to what is visible in EditString
	- LabelBox("")
		- Label("Click the 'Assign' Button while Holding Down Modifier Keys")

#### Editing/Tools
- List of one liners
	- Option(default=false); Label("Select Tool: Show Extra Info")
	- Option(default=true); Label("Warn before switching Display Domain (Timewarp Tool)")
	- Option(default=true); Label("Zoom Tool Standard Mode: Horizontal Zooming Only")
	- Option(default=true); Label("Popup Toolbox on right Click")
	- LabelBox("Cross Hair Cursor")
		- Option(default=true); Label("Enable")
		- Color selector(default=Black); Label("Line Color");
		- Color selector(default=White); Label("Mask Color");
		- Option(default=false); Label("Use Dotted Line")
		- EditIntSpinNotNull(default="3"); Label("Mask Widths")

#### Editing/Video
- List of one liners
	- Option(default=true); Label("Extract Audio on Import Video File")
	- Option(default=true); Label("Generate Thumbnail Cache on Import Video File")


#### Event Display
- List of one liners
	- Option(default=true); Label("Show Event Names")
	- Option(default=false); Label("Transparent Events")
	- Option(default=false); Label("Show Data on Small Track Heights")
	- Option(default=true); Label("Colorize Event Background")


#### Event Display / Audio
- List of one liners
	- Option(default=false); Label("Interpolate Audio Images")
	- DropList(Solid ; Framed ; (x) Solid and Framed); Label("Wave Image Style")
	- Option(default=true); Label("Show Event Volume Curves Always")
	- Option(default=true); Label("Fade Handles always on Top")
	- Option(default=false); Label("Thick Fade Lines")
	- Option(default=true); Label("Show Waveforms")
	- Option(default=false); Label("Background Color Modulation")


#### Event Display / MIDI
- List of one liners
	- DropList(Open Key Editor ; Open In-Place Editor ; Open Drum Editor ; Open List Editor ; Open Score Editor); Label("Default Edit Action")
	- DropList(No Data ; (x)Lines ; Scores ; Drums); Label("Part Data Mode")
	- Option(default=true); Label("Show Controllers")
	- Option(default=true); Label("Edit as Drums when Drum Map is assigned")
	- DropList(MIDI ; MIDI and Value ; DoR-Mi ; Classic ; Classic (German) ); Label("Note Name Style")


#### Event Display / MIDI
- List of one liners
	- Option(default=false); Label("Use Strong Colors")


#### Event Display / MIDI
- List of one liners
	- Option(default=true); Label("Show Video Thumbnails")
	- EditIntSpinNotNull(default="3 MB"); Label("Video Cache Size")


#### General
- List of one liners
	- DropList( English ; Finnish ; German ; French ; Spanish ; Italian ; Japanese ); Label("Language")
	- Option(default=true); Label("Auto Save")
	- EditIntSpinNotNull(default="15.0 min"); Label("Auto Save Interval")
	- EditIntSpinNotNull(default=10); Label("Maximum Backup Files")
	- Option(default=true); Label("Show Tips")
	- EditIntSpinNotNull(default=inf); Label("Maximum Undo")
	- Option(default=false); Label("Run Setup on Create New Project")
	- DropList( Do Nothing ; Open Last Project ; Open 'Default' Template ; Show Open Dialog ; Show Template Dialog ; Show Open Options Dialog); Label("On Startup")
	- Option(default=false); Label("Usage Profile")


#### MIDI
- List of one liners and LabelBoxes with one liners
	- Option(default=true); Label("MIDI Thru Active")
	- Option(default=false); Label("Reset on Stop")
	- EditIntSpinNotNull(default="-2 Ticks"); Label("Length Adjustment")
	- LabelBox("Chase Events")
		- Option(default=true); Label("Note")
		- Option(default=true); Label("Poly  Pressure")
		- Option(default=true); Label("Controller")
		- Option(default=true); Label("Chase not limited to Part Boundaries")
		- Option(default=true); Label("Program Change")
		- Option(default=true); Label("Aftertouch")
		- Option(default=true); Label("Pitchbend")
		- Option(default=false); Label("SysEx")
	- Label("MIDI Display Resolution 1/16 ="); EditIntSpinNotNull(default="120 Ticks"); Label("PPQBase: 480")
	- Option(default=false); Label("Insert Reset Events after Record")
	- Option(default=false); Label("Audition through MIDI Inserts/Sends")
	- EditIntSpinNotNull(default="250 ms"); Label("MIDI Max. Feedback in ms")


#### MIDI / MIDI File
- list of labelboxes
	- LabelBox("Export Options")
		- Option(default=false); Label("Export Inspector Patch")
		- Option(default=false); Label("Export Inspector Volume/Pan")
		- Option(default=false); Label("Export Automation")
		- Option(default=true); Label("Export Inserts")
		- Option(default=false); Label("Export Sends")
		- Option(default=true); Label("Export Marker")
		- Option(default=false); Label("Export as Type 0")
		- EditIntSpinNotNull(default=480); Label("Export Resolution")
		- Option(default=false); Label("Export Locator Range")
		- Option(default=false); Label("Export includes Delay")
	- LabelBox("ImportOptions")
		- Option(default=false); Label("Extract First Patch")
		- Option(default=false); Label("Extract First Volume/Pan")
		- Option(default=false); Label("Import Controller as Automation Tracks")
		- Option(default=false); Label("Import to Left Locator")
		- Option(default=true); Label("Import Marker")
		- Option(default=false); Label("Import dropped File as single Part")
		- Option(default=true); Label("Ignore Master Track Events on Merge")
		- Option(default=true); Label("Auto Dissolve Format 0")
		- Option(default=true); Label("Import To Instrument Tracks")
		


#### MIDI / MIDI Filter
- vertical splitter in whole area
	- horizontal splitter
		- LabelBox(Record). // List of one-liners
			- Option(default=false); Label("Note")
			- Option(default=false); Label("Poly Pressure")
			- Option(default=false); Label("Controller")
			- Option(default=false); Label("Program/Patch")
			- Option(default=false); Label("Aftertouch")
			- Option(default=false); Label("Pitchbend")
			- Option(default=true); Label("SysEx")
		- LabelBox(Thru). // List of one-liners
			- Option(default=false); Label("Note")
			- Option(default=false); Label("Poly Pressure")
			- Option(default=false); Label("Controller")
			- Option(default=false); Label("Program/Patch")
			- Option(default=false); Label("Aftertouch")
			- Option(default=false); Label("Pitchbend")
			- Option(default=true); Label("SysEx")
	- horizontal splitter
		- LabelBox(Channels)
			- 16 ToggleButton:s in 4x4 grid. Maybe use 4 vertical splitters and 4 horizontal splitters
				- ToggleButton([1:16]) // Every button has a own number between 1..16
		- LabelBox(Controller) // list of oneliners
			- EditIntSpinNotNull(default="CC 0 (BankSelMSB)"); // These seems to be MIDI commands. Pressing + sets it to "CC 1 (Modulation)"
			- Button(Add) ; Button(Remove)
			- ArrayCtrl(Header is hidden, 1 unnamed column) // default contain is 1 item: "CC 123 (AllNoteOff)

		
#### MediaBay
- List of one liners
	- EditIntSpinNotNull(default=100000); Label("Maximum Number of Results in Viewer")
	- Option(default=false); Label("Allow Editing in Viewer")
	- Option(default=true); Label("Stop scanning folders when closing MediaBay")
	- Option(default=false); Label("Show File Extensions")
	

#### Record
empty


#### Record / Audio
- List of one liners
	- EditDoubleSpinNotNull(default=1.00); Label("Audio Pre-Record Seconds")
	- Option(default=true); Label("Create Audio Images During Record")
	- DropList( Create Regions ; Create Events ; Creat Events + Regions ); Label("Audio Cycle Record Mode")


#### Record / Audio / Broadcast Wave
- List of one liners
	- EditString(default="MasterLab"); Label("Descriptor")
	- EditString(default="MasterLab"); Label("Author")
	- EditString(default=""); Label("Reference")


#### Record / MIDI
- List of one liners
	- Option(default=true); Label("Snap MIDI Parts to Bars")
	- Option(default=true); Label("Solo Record in MIDI Editors")
	- EditIntSpinNotNull(default=""); Label("MIDI Record Catch Range in ms")
	- Option(default=true); Label("Retrospective Record")
	- EditIntSpinNotNull(default="10000 Events"); Label("Retrospective Record Buffer Size")
	- DropList( None ; Controller ; All ); Label("Replace Recording in Editors")


#### Scores




	- Option(default=false); Label("")
	- Option(default=true); Label("")
	- EditIntSpinNotNull(default=""); Label("")
	- EditString(default=""); Label("")
	- DropList( ); Label("")

In DropList widgets, ";" character separates options and option with (x) is default (if set, otherwise first).
