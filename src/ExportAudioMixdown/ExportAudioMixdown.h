#ifndef _ExportAudioMixdown_ExportAudioMixdown_h_
#define _ExportAudioMixdown_ExportAudioMixdown_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

struct ExportChannel : public Moveable<ExportChannel> {
	String id;
	String label;
	Vector<ExportChannel> children;
	bool selected = false;
	
	// Add explicit copy constructor and assignment operator
	ExportChannel() = default;
	ExportChannel(const ExportChannel& other) 
		: id(other.id), label(other.label), children(), selected(other.selected) {
		// Deep copy children vector
		children.Reserve(other.children.GetCount());
		for(int i = 0; i < other.children.GetCount(); i++) {
			children.Add() = other.children[i];
		}
	}
	
	ExportChannel& operator=(const ExportChannel& other) {
		if(this != &other) {
			id = other.id;
			label = other.label;
			selected = other.selected;
			// Deep copy children vector
			children.Clear();
			children.Reserve(other.children.GetCount());
			for(int i = 0; i < other.children.GetCount(); i++) {
				children.Add() = other.children[i];
			}
		}
		return *this;
	}
};

struct ExportRequest {
	String filename;
	String directory;
	String fileType;
	Vector<String> channels;
	ValueMap codecSettings;
	int sampleRate = 44100;
	int bitDepth = 24;
	bool monoExport = false;
	bool realTimeExport = false;
	bool splitChannels = false;
	bool updateDisplay = false;
	bool addToPool = true;
	bool createAudioTrack = false;
	bool closeAfterExport = false;
};

class ChannelTreePane : public ParentCtrl {
public:
	typedef ChannelTreePane CLASSNAME;
	ChannelTreePane();

	void SetChannels(const Vector<ExportChannel>& roots);
	Vector<String> GatherSelection() const;
	void Clear();
	void Layout() override;

private:
	struct Row : public ParentCtrl {
		typedef Row CLASSNAME;
		Row();
		void Configure(const ExportChannel& channel, int depth);
		bool IsSelected() const { return select.Get(); }
		void SetSelected(bool sel) { select.Set(sel); }
		const String& Id() const { return channelId; }
		void Layout() override;

	private:
		Option select;
		Label text;
		String channelId;
		int indent = 0;
	};

	void AppendChannel(const ExportChannel& channel, int depth);
	void LayoutRows();

	Array<One<Row>> rows;
};

class CodecOptionsPane : public ParentCtrl {
public:
	typedef CodecOptionsPane CLASSNAME;
	CodecOptionsPane();

	void SetCodec(const String& codecId);
	void GetCodecSettings(ValueMap& settings) const;
	void SetCodecSettings(const ValueMap& settings);
	Event<> WhenEditID3;

private:
	void InitPanels();
	void ShowPanel(ParentCtrl& panel);
	void ConfigureWavePanel();
	void ConfigureMp3Panel();

	String activeCodec;
	ParentCtrl wavPanel;
	ParentCtrl mp3Panel;
	ParentCtrl placeholderPanel;
	Label placeholderLabel;
	Option wavInsertBroadcast;
	Option wavDisableExtensible;
	Option wavInsertIXML;
	DropList mp3BitRate;
	DropList mp3SampleRate;
	Option mp3HighQuality;
	Option mp3InsertID3;
	Button mp3EditID3;
};

class ID3TagDialog : public TopWindow {
public:
	typedef ID3TagDialog CLASSNAME;
	ID3TagDialog();

	void SetTags(const ValueMap& tags);
	ValueMap GetTags() const;

private:
	EditString title;
	EditString artist;
	EditString album;
	EditString year;
	EditString genre;
	EditString comment;
	Button okButton;
	Button cancelButton;
	void SetupLayout();
	void OnOK();
	void OnCancel();
};

class ExportProgressDialog : public TopWindow {
public:
	typedef ExportProgressDialog CLASSNAME;
	ExportProgressDialog();

	void SetProgress(int percent);
	Event<> WhenCancel;

private:
	ProgressIndicator progress;
	Button cancelButton;
	void OnCancel();
};

class ExportAudioMixdownDialog : public TopWindow {
public:
	typedef ExportAudioMixdownDialog CLASSNAME;
	ExportAudioMixdownDialog();

	void SetChannels(const Vector<ExportChannel>& channels);
	void SetFileTypes(const Vector<String>& types);
	void SetSampleRates(const Vector<int>& rates);
	void SetBitDepths(const Vector<int>& depths);
	void SetDefaultPath(const String& path);
	void SetDefaultFilename(const String& name);
	void SetCodecSettings(const ValueMap& settings);
	ExportRequest CollectRequest() const;

	Event<const ExportRequest&> WhenExport;
	Event<> WhenBrowsePath;
	Event<> WhenDialogClose;
	Event<ValueMap&> WhenEditID3;
	Event<> WhenBatchExport;

private:
	void BuildLayout();
	void OnExport();
	void OnCloseDialog();
	void OnBrowsePath();
	void OnFileTypeChanged();
	void OnEditID3();
	void OnBatchExport();

	Splitter contentSplit;
	ParentCtrl leftPane;
	ChannelTreePane channelPane;
	ParentCtrl configPane;
	Button batchExportButton;
	EditString filenameEdit;
	EditString pathEdit;
	Button browseButton;
	DropList fileType;
	CodecOptionsPane codecPane;
	DropList sampleRate;
	DropList bitDepth;
	Option monoExport;
	Option realTimeExport;
	Option splitChannels;
	Option updateDisplay;
	Option addToPool;
	Option createAudioTrack;
	Option closeAfterExport;
	Button exportButton;
	Button closeButton;
	ExportProgressDialog progressDialog;
	ID3TagDialog id3Dialog;
};

}

#endif
