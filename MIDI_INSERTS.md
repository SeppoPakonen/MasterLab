# MIDI Inserts

## Stub Package Overview
- `midi_inserts/Arpache5` — Real-time arpeggiator with configurable play order, step size, and note length.
- `midi_inserts/ArpacheSX` — Advanced polyphonic arpeggiator with Classic and Sequence modes sharing pattern data with StepDesigner.
- `midi_inserts/AutoLFO` — Tempo-synchronised MIDI LFO generator for CC automation.
- `midi_inserts/BeatDesigner` — Drum-oriented step sequencer with velocity lanes and pattern presets.
- `midi_inserts/Chorder` — Chord trigger/layer insert with preset voicings and play styles.
- `midi_inserts/MidiCompressor` — Velocity/length compressor for MIDI notes.
- `midi_inserts/ContextGate` — Context-aware gate with polyphonic and monophonic modes.
- `midi_inserts/Density` — Density/velocity redistribution tool for beat emphasis.
- `midi_inserts/MidiController` — Eight-lane controller router with per-row toggles.
- `midi_inserts/MidiEcho` — Echo/delay generator with velocity, pitch, and length decay.
- `midi_inserts/MidiModifiers` — Compact transform grid for transpose, velocity, range, and randomisation tasks.
- `midi_inserts/MidiMonitor` — Diagnostic monitor capturing filtered MIDI events.
- `midi_inserts/MicroTuner` — Pitch-class tuning insert for cent-level adjustments.
- `midi_inserts/NoteToCC` — Converts note velocity to controller messages.
- `midi_inserts/Quantizer` — Real-time timing quantiser with swing, strength, and delay.
- `midi_inserts/StepDesigner` — Melodic step sequencer with CC lanes and pattern banks.
- `midi_inserts/TrackControl` — GS/XG macro controller panel with effect selectors.
- `midi_inserts/Transformer` — Rule-based logical editor for filtering, transforming, or inserting events.

## Feature Snapshot & Shared Infrastructure
- Arpache family reuses `MidiGraph::InputCollector`, `MidiGraph::LatchBuffer`, `MidiGraph::OrderResolver`, and `MidiGraph::ClockDividerNode` for unified chord capture and timing.
- BeatDesigner/StepDesigner/ArpacheSX sequence lanes share `MidiSequencer::StepGrid`, `MidiSequencer::AutomationLane`, `MidiSequencer::PatternMemory`, and `MidiGraph::PatternScheduler` for pattern editing.
- Harmony-related inserts (Chorder, ArpacheSX, MicroTuner) pull from `MidiHarmony::ChordPresetLibrary`, `MidiHarmony::VoicingEngine`, and `MidiPitch::TuningTable` to ensure presets align across tools.
- Dynamics-focused inserts (MidiCompressor, Density, MidiModifiers) rely on `MidiDynamics::VelocityCurve`, `MidiDynamics::GainStage`, and `MidiRandom::DeterministicStream` for consistent velocity shaping/humanisation.
- Controller utilities (MidiController, TrackControl, AutoLFO, NoteToCC) centralise routing via `MidiRouting::ControllerMatrix` and metadata from `MidiRouting::ControllerLibrary`.
- Transformer presets and MidiModifiers grids share the `MidiLogic::RuleEngine` primitives; full preset text now lives under `scripts/midi_inserts/transformer/` for reuse.


## Reference software

### Arpache 5

Jonkin lainen arpeggiator ohjelma.

#### GUI

Play order (DropList):
- Normal
- Invert
- Up Only
- Down Only
- Random
- User

Step Size: 1/16 default. Sisältää tyypilliset murto-osa nuotit.
Length: 1/16 default
Key Range: 12 (notes)


### Arpache SX
Jonkinlainen advanced arpeggiator ohjelma. Polyfoninen. Kuin Arpache 5 mutta monimutkaisempi.

#### GUI
Classic ja Sequence välilehdet.


### Auto LFO

#### GUI
Waveform (DropList): Sine // tyypillinen lista
WaveLength: 1/4 // tyypillinen lista)
Controler Type: 10. // joku tyypillinen MIDI lista, 0 on BankSel MSB
Density: {29 PPQ - small ; 119 PPQ - medium ; 239 PPQ - large }
Value range MIN: 0
Value range MAX: 127

### Beat Designer
Jokin loop tyylinen drum sequencer. Keskellä on 16 (iskut) * 8 (soittimet) grid. 
Vasemmalla on soitinlista: Tom, Snare, jne. Niitä voi vaihtaa: klikkaus avaa context-valikon ja hiiren rulla vaihtaa seuraavaan.

Sisältää Slider widgettejä 3*position, 2*swing, johonkin tarkoitukseen. Ne vaikuttaa eri asioihin.

Alhaalla yhden oktaavin pianon koskettimet, ja 4 nappia 4 eri oktaavin valitsemiselle. En tiedä mitä tämä tekee.
Se ehkä vaihtaa luupin.


### Chorder

Presets:
- Guitar Chords {...}
- Jazz Chords {...}
- Octaves {Major chords for every A,B,C,D...}
- etc.

#### GUI
Suurin osa ikkunasta on vaakatasossa olevalle virtuaali keyboardille, ja sen päällä olevalle ajassa muuttuvalle piirtimelle.

Chords (DropList): {All Keys ; One Octave ; Global Key}
Playstyle (DropList): {Simultaneous ; fast up ; slow up ; fast down ; slow down ; fast random ; slow random }
Layers (DropList): {Velocity ; Interval ; Single Mode }

### Compressor
Kompressoi midi nuotteja. Sliderit: Treshold, Ratio, Gain


### Context Gate
Filtteroi midi inputtia.

#### GUI
Tabs: Poly Mode, Mono Mode.


##### Poly Mode
Switch: Polyphony gate / Chord gate
Key Range Limit (edit begin and end, in one slider).
Recognition (DropList): {Normal ; Simple }
Minimum Polyphone (EditIntSpin): 4
Auto Gate Time (EditInt): 6
Panic Reset (Button)
Learn Reset (Button)

##### Mono Mode
Switch: Channel gate / Velocity gate
Mono Channel (EditInt)
Minimum Velocity (EditInt)
Key Range Limit (edit begin and end, in one slider).
Auto Gate Time (EditInt): 6
Panic Reset (Button)
Learn Reset (Button)


### Density
This seems to be able to reduce or increase "density" of notes, whatever it means. My guesses are, with <100% it reduces velocity of some notes (those not further away from beat), and with >100% it increases velocity on beats and even repeats some notes.

There's only 1 slider in this GUI: default 100%, min 0%, max 400%.


### MIDI Controler

This has rows for 8 MIDI control notes and ToggleButtons for them. User chan choose any MIDI Control note for them (from CC 0 to CC 127). I don't know what on and off togglebuttons do. Maybe it let's them to go through or not?

#### GUI
8 Rows. Eech row has: ToggleButton(On ; Off) & DropList. Drop lists have values from CC 0 to CC 127 with texts, e.g. "CC 8 (Balance)"


### MIDI Echo
Tämä näyttää siltä, että se vain luo uusia nuotteja kaikuna. Tyypillisesti velocity on pienempi. Default arvossa myös pitch offset -1, eli että kaiku pudottaa virettä myös.

#### GUI
- Horz Splitter:
	- Velocity Offset (EditIntSlider): -4
	- Pitch Offset (EditIntSlider): -1
- Repeats (EditIntSlider): 5
- Beat Align (DropList): (PPQ) 1/32T // your typical options
- Horz Splitter
	- Delay (DropList): (PPQ) 1/16 // your typical options
	- Delay Decay (EditIntSlider, min 25%, max 175%)
- Horz Splitter
	- Length (DropList): (PPQ) 1/16 // your typical options
	- Length Decay (EditIntSlider, min 25%, max 100%)


### MIDI Modifiers

#### GUI
- Transpose ; (EditIntSlider, def 0, min -127, max 127)
- Velocity Shift ; (EditIntSlider, def 0, min -126, max 126)
- Velocity Compression ; (EditFraction, def 1/1)
- Length Compression ; (EditFraction, def 1/1)
- Grid 3 * 3
	- "Random"; "min"; "max"
	- DropList(OFF ; Position ; Pitch ; Velocity ; Length); EditIntSpin(def 0, min -120, max +120); EditIntSpin(def 0, min -120, max +120);
	- DropList(OFF ; Position ; Pitch ; Velocity ; Length); EditIntSpin(def 0, min -120, max +120); EditIntSpin(def 0, min -120, max +120);
- 
- Grid 3 * 3
	- "Range"; "min"; "max"
	- DropList(OFF ; Velocity Limit ; Velocity Filter ; Note Limit ; Note Filter); EditIntSpin(def 1, min 1, max 127); EditIntSpin(def 1, min 1, max 127);
	- DropList(OFF ; Velocity Limit ; Velocity Filter ; Note Limit ; Note Filter); EditIntSpin(def 1, min 1, max 127); EditIntSpin(def 1, min 1, max 127);
- Delay ms ; EditIntSpin(def 0, min 0, max 50)
- Scale ; DropList(No Scale ; {27 different scales like Major, Harmonic Minor, Melodic Minor, Blues , ... })
- Scale Note ; DropList(C ; C# ; D ... ; B)


### MIDI Monitor
Seems to allow seeing midi events as list, what comes to input. It allows limiting buffer size and exportin buffer to midi file. .
It's off by default and must be turned on manually

#### GUI
- top row
	- ToggleButton(icon=power, description=For enabling event recording); ToggleButton("Live Events"); ToggleButton("Playback Events");
- second top row
	- ToggleButton(icon=X, description=For clearing buffer); ToggleButton("Notes"); ToggleButton("Controller"); ToggleDropList("Single CC", {127 midi CC}, description=filter only these events)
	- ToggleButton("Polypressure"); ToggleButton("Aftertouch"); ToggleButton("Pitchbend");
	- ToggleButton("Program Change"); ToggleButton("SysEx"); ToggleButton("Realtime");
- large area for buffer
	- ArrayCtrl(columns={Status ; Value1 ; Value 2; Value 3; Channel ; Length; Position ; Comment})
- bottom row
	- DropList(100 events - small ; 1000 events - medium ; 10000 events - large )

	
	
### Micro Tuner
This allows tuning notes for some cent differences. It has 1 octave visible and it changes all octaves. It outputs modified notes. It passes trough all other notes unchanged than notes.

#### GUI
One octave of piano keys. Keys are horizontally next to each other. Both black and white keys. Inside keys there are vertical sliders. At the top of the slider is TransparentEditInt, which shows edited value, and allows writing it directly with keyboard.

Slider's default value is 0. Maximum 64 and minimum -64.


### Note To CC
I guess this takes any note and uses the velocity to write a new control signal with that velocity value. It has only 1 DropList, which shows values from CC 0 to CC 127 with text e.g. "CC 10 (Pan)".


### Quantizer
Runtime note quantization. Allows realtime mode for live usage.

#### GUI
- 4 rows
	- Quantize Note; DropList({1/16 ... and other typical values})
	- Swing; EditIntSlider(def 1%, min 1%, max 100%)
	- Strength; EditIntSlider(def 100%, min 1%, max 100%)
	- Delay; EditIntSlider(def 0 ms, min -50ms, max +50ms)
	- Realtime quantize; Option(def=false);

### StepDesigner
StepDesigner. Kind of basic. Could be more advanced, like editor in NI Massive VST instrument.

#### GUI
- top row
	- Button(icon=up, description=move notes octave up)
	- Button(icon=down, description=move notes octave down)
	- Button(icon=left, description=move notes left rolling over left limit to the position length-1)
	- Button(icon=right, description=move notes right rolling over right limit to the position 0)
	- Button("Reverse", description=Reverses notes in the grid so that position 0 moves to length-1)
	- DropList({saved presets});
	- Button(icon=save; description=saves current configuration as new presets and asks name)
	- Button(icon=remove; description=removes the selected preset in preset list)
	- EditIntSpin(def 16, min 1, max 32, description=Sets the length of the sequence as notes)
	- DropList({def 1/16, has other typical values}}, description=Sets the length of note as fractions)
- Main view
	- a grid of 12*32. 12 notes and 32 maximum length (not used completely necessarily). Highlights every 8th column for clarity.
		- user writes notes, and notes are filled rectangles. The color depends on the velocity of the lower velocity slider which changes color at that column.
	- below the grid, are sliders for CC value (velocity is set by default, but is changeable). The horizontal X position corresponds to the grid column.
		- the value is 64 by default and can be between 0 and 127. Color for the full column at value 127 is yello, and for value 64 is red, and for value 0 is dark red. The color fades between those anchor values.
- bottom row
	- DropList({Velocity; Gate ; User1 - CC 71 (Harmonic); User2 - CC 74 (Brightness)}); 
	- Button("Setup", description=opens popup window which allows selection from any CC 0 - CC 127 values to both User1 and User2 values);
	- Pattern; EditIntSpin(def 1, min 1, max 200, description=Selects between loops (inside the preset) which changes all the notes and CC values);
	- Button("Copy")
	- Button("Paste")
	- Button("Random")
	- Button("Reset")


### Track Control
I am not sure what GS1, XG1 and XG2 are, bot they seem to allow editing some advanced synth settings. It's like they were some MIDI extensions... but I dont know.

#### GUI

- 3 tabs: GS 1 ; XG 1 ; XG 2
	- GS 1
		- Button("Reset") // Sets default values, it's like a preset: Send1=64; CutOff=127, Express=127
		- Button("Off") // Sets "off" values, it's like a preset: Send1=0; CutOff=64, Express=0
		- Send 1; EditIntSlider(def 64, min 0, max 127)
		- Send 2; EditIntSlider(def 0, min 0, max 127)
		- Send 3; EditIntSlider(def 0, min 0, max 127)
		- Attack; EditIntSlider(def 64, min 0, max 127)
		- Decay; EditIntSlider(def 64, min 0, max 127)
		- Release; EditIntSlider(def 64, min 0, max 127)
		- CutOff; EditIntSlider(def 127, min 0, max 127)
		- Resonance; EditIntSlider(def 64, min 0, max 127)
		- Express; EditIntSlider(def 127, min 0, max 127)
		- Channel Press; EditIntSlider(def 0, min 0, max 127)
		- Breath; EditIntSlider(def 0, min 0, max 127)
		- Modulation; EditIntSlider(def 0, min 0, max 127)
	- XG 1
		- Button("Reset") // Sets default values, it's like a preset
		- Button("Off") // Sets "off" values, it's like a preset: sets all 0
		- Send 1; EditIntSlider(def 64, min 0, max 127)
		- Send 2; EditIntSlider(def 0, min 0, max 127)
		- Send 3; EditIntSlider(def 0, min 0, max 127)
		- Attack; EditIntSlider(def 64, min 0, max 127)
		- Decay; EditIntSlider(def 64, min 0, max 127)
		- Harm. Cont.; EditIntSlider(def 64, min 0, max 127)
		- Bright; EditIntSlider(def 64, min 0, max 127)
		- CutOff; EditIntSlider(def 127, min 0, max 127)
		- Resonance; EditIntSlider(def 64, min 0, max 127)
	- XG 2
		- Button("Reset") // Sets default values, it's like a preset
		- Button("Off") // Sets "off" values, it's like a preset: sets all off
		- Effect 1; DropList({Hall1, Hall2, Room1, Room2, Room3, Stage1, Stage2, Plate})
		- Effect 2; DropList({Chorus1, Chorus2, Chorus3, Celeste1, Celeste2, Celeste3, Flanger1, Flanger2})
		- Effect 3; DropList({Delay LCR; Delay LR; Echo; Cross Delay; ER; Gate Reverb; Reverse	Gate; THRU; Symphonic; Rotary Speaker; Tremolo; Auto Pan; Phae1; Distortion; Overdrive; Amp Simulator; 3-Band EQ; 2-Band EQ; Auto Wah})
		- Reset; Option(def=false)
		- Master Volume; EditIntSpin(def 0, min 0, max 127)

		
		

### Transformer
So this allows scripting. Presets of this MIDI Insert were in MenuBar and shortcut key list also. So if you create a preset, you will see it there.
It doesn't allow writing a script as text, but it could be possible, and frankly, easier.

The Filter script has visually "(" before the list and ")" at the end, which means, that the Filter Target ArrayCtrl is a logical expression. Every row has changeable operator. That means, that filter function is kinda like "(row_1 && row2 || (row3 && row4))".

#### Filter target list
- Value	1
- Value	2
- Channel
- Type
- Property
- Value	3
- Last Event

#### Condition list
- Equal
- Unequal
- All Types

#### Filter Parameter 1 list
##### For Filter target: Value 1
Notes e.g. C#-2, G8
##### For Filter target: Value 2
Integer 0-127
##### For Filter target: Channel
Integer 1-16
##### For Filter target: Type
- Note
- Poly Pressure
- Controller
- Program Change
- Aftertouch
- Pitchbend
- SysEx
- SMF Event
##### For Filter target: Property
- Event is muted
- Event is selected
##### For Filter target: Value 3
Integer 0-127
##### For Filter target: Last Event
- Value 1
- Value 2
- MIDI Status
- Channel
- Eventcounter
- Note is playing

#### Filter Parameter 2 list
##### For Filter target: Last Event
Integer 0-255

#### Action target list
- Value	1
- Value	2
- Channel
- Type
- Value	3

#### Operation list
##### For Action Target: Value 1
- Add
- Subtract
- Multiply by
- Divide by
- Round	by
- Set Random Values between
- Set to fixed value
- Set relative Random Values between
- Use Value 2
##### For Action Target: Value 2 & Value 3
- Add
- Subtract
- Multiply by
- Divide by
- Round	by
- Set Random Values between
- Set to fixed value
- Set relative Random Values between
- Use Value 1
- Mirror
##### For Action Target: Channel
- Add
- Subtract
- Set to fixed value
- Set relative Random Values between
##### For Action Target: Type
- Set to fixed value

#### Action Parameter 1
##### For Action Target: Value 1 & Value 2 & Value 3
Integer 0-127
##### For Action Target: Channel
Integer 0-15
##### For Action Target: Type
- Note
- Poly Pressure
- Controller
- Program Change
- Aftertouch
- Pitchbend


#### GUI
- vertical splitter
	- ArrayCtrl(columns={"("; Filter Target ; Condition ; Parameter 1 ; Parameter 2; Qualifiers; ")"; Boolean Operator}, description=rules for matching input midi events)
		- once you have a row, you may click any grid value, and it opens a DropList (or context menu) for selecting the value
		- this has ToolBar, which has buttons for Add and Remove rows
	- ArrayCtrl(columns={Action Target ; Operation ; Parameter 1 ; Parameter 2})
		- you modify values by clicking grid position and it opens context menu with values
		- this has ToolBar, which has buttons for Add and Remove rows
- bottom row
	- Function; DropList({Delete; Transform ; Insert; Insert Exclusive})

	
#### Presets

Preset definitions have been exported to `scripts/midi_inserts/transformer/` as individual `.md` files for reuse in tooling and automation:

- `added_for_version_3/` — Add Note [+12], if Mod/Wheel is above 64; Delete all Controllers in Cycle Range; Delete each 5th note; Delete SMF Events; Kill Notes on C-Major; Scale down Velocity in Sustain Range; Select all Events beyond Cursor; Select all Events in Cycle Range; Shift Key C1 Transpose by 24; Shift Notes by 12 Ticks beyond Cursor; Transform Notes after D#3 or C#3; Transpose EventsInSistainRange.
- `experimental/` — add volume 0 to end of note; delete black keys; downbeat accent (4/4); extract volume and pan; filter off beats; insert mid iVolume for velocity.
- `standard_set_1/` — delete muted; delete short notes; double tempo; fixed velocity 100; half tempo; push back -4; push forward +4; random notes (c3 to c5); random velocity (60 to 100).
- `standard_set_2/` — del.aftertouch; del patch changes; del velocity below 30; del velocity below 35; del velocity below 40; del velocity below 45; extract note (c3 60); high notes to channel 1; low notes to channel 2; set notes to fixed pitch (c3); transpose -12; transpose +12.

Each preset file preserves the original logical-editor syntax so scripts can be imported or processed programmatically without reformatting.
