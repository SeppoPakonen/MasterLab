#include "ExportAudioMixdown.h"
#include <Core/App.h>

namespace am {

// --- ChannelTreePane ------------------------------------------------------

ChannelTreePane::Row::Row() {
	Add(select);
	Add(text);
	SetMinSize(Size(0, 24));
}

void ChannelTreePane::Row::Configure(const ExportChannel& channel, int depth) {
	indent = depth * 18;
	select.SetLabel(String());
	select.Set(channel.selected);
	channelId = channel.id;
	text.SetText(channel.label);
	Layout();
}

void ChannelTreePane::Row::Layout() {
	Size sz = GetSize();
	int selectSize = 18;
	select.SetRect(indent + 4, (sz.cy - selectSize) / 2, selectSize, selectSize);
	text.SetRect(indent + 28, 0, sz.cx - (indent + 32), sz.cy);
}

ChannelTreePane::ChannelTreePane() {
	SetFrame(ThinInsetFrame());
}

void ChannelTreePane::Clear() {
	for(auto& rowSlot : rows) {
		if(rowSlot)
			Remove();
	}
	rows.Clear();
	Refresh();
}

void ChannelTreePane::SetChannels(const Vector<ExportChannel>& roots) {
	Clear();
	for(const ExportChannel& channel : roots)
		AppendChannel(channel, 0);
	Refresh();
}

void ChannelTreePane::AppendChannel(const ExportChannel& channel, int depth) {
	One<Row>& slot = rows.Add();
	Row& row = slot.Create<Row>();
	row.Configure(channel, depth);
	Add(row);
	for(const ExportChannel& child : channel.children)
		AppendChannel(child, depth + 1);
}

void ChannelTreePane::LayoutRows() {
	int y = 0;
	Size sz = GetSize();
	for(auto& rowSlot : rows) {
		Row& row = *rowSlot;
		row.SetRect(RectC(0, y, sz.cx, 24));
		y += 24;
	}
}

Vector<String> ChannelTreePane::GatherSelection() const {
	Vector<String> result;
	for(const One<Row>& rowSlot : rows) {
		const Row& row = *rowSlot;
		if(row.IsSelected())
			result.Add(row.Id());
	}
	return result;
}

void ChannelTreePane::Layout() {
	ParentCtrl::Layout();
	LayoutRows();
}

// --- CodecOptionsPane -----------------------------------------------------

CodecOptionsPane::CodecOptionsPane() {
	InitPanels();
	SetCodec("Wave File");
}

void CodecOptionsPane::InitPanels() {
	Add(wavPanel.SizePos());
	Add(mp3Panel.SizePos());
	Add(placeholderPanel.SizePos());

	ConfigureWavePanel();
	ConfigureMp3Panel();

	placeholderPanel.SetFrame(ThinInsetFrame());
	placeholderLabel.SetText("No codec options required.");
	placeholderPanel.Add(placeholderLabel.HCenterPos(200).VCenterPos(24));

	ShowPanel(placeholderPanel);
}

void CodecOptionsPane::ConfigureWavePanel() {
	wavPanel.SetFrame(ThinInsetFrame());
	wavInsertBroadcast.SetLabel("Insert Broadcast WAV chunk");
	wavDisableExtensible.SetLabel("Don't use WAV extensible format");
	wavInsertIXML.SetLabel("Insert iXML chunk");

	wavPanel.Add(wavInsertBroadcast.TopPos(6, 24).LeftPos(8, 240));
	wavPanel.Add(wavDisableExtensible.TopPos(34, 24).LeftPos(8, 240));
	wavPanel.Add(wavInsertIXML.TopPos(62, 24).LeftPos(8, 240));
}

void CodecOptionsPane::ConfigureMp3Panel() {
	mp3Panel.SetFrame(ThinInsetFrame());

	mp3BitRate.Add("128 kbps");
	mp3BitRate.Add("160 kbps");
	mp3BitRate.Add("192 kbps");
	mp3BitRate.Add("256 kbps");
	mp3BitRate.Add("320 kbps");
	mp3BitRate.SetIndex(2);

	mp3SampleRate.Add("44.1 kHz");
	mp3SampleRate.Add("48 kHz");
	mp3SampleRate.Add("32 kHz");
	mp3SampleRate.SetIndex(0);

	mp3HighQuality.SetLabel("High quality mode");
	mp3InsertID3.SetLabel("Insert ID3 tag");

	mp3EditID3.SetLabel("Edit ID3 tag...");
	mp3EditID3.WhenAction = [this] {
		WhenEditID3();
	};

	Label bitrateLabel;
	bitrateLabel.SetLabel("Bit rate:");
	mp3Panel.Add(bitrateLabel.TopPos(6, 20).LeftPos(8, 90));
	mp3Panel.Add(mp3BitRate.TopPos(6, 20).LeftPos(106, 120));
	Label samplerateLabel;
	samplerateLabel.SetLabel("Sample rate:");
	mp3Panel.Add(samplerateLabel.TopPos(34, 20).LeftPos(8, 90));
	mp3Panel.Add(mp3SampleRate.TopPos(34, 20).LeftPos(106, 120));
	mp3Panel.Add(mp3HighQuality.TopPos(62, 24).LeftPos(8, 200));
	mp3Panel.Add(mp3InsertID3.TopPos(90, 24).LeftPos(8, 200));
	mp3Panel.Add(mp3EditID3.TopPos(122, 24).LeftPos(8, 150));

	mp3InsertID3.Set(true);
}

void CodecOptionsPane::ShowPanel(ParentCtrl& panel) {
	wavPanel.Hide();
	mp3Panel.Hide();
	placeholderPanel.Hide();
	panel.Show();
}

void CodecOptionsPane::SetCodec(const String& codecId) {
	String id = ToLower(codecId);
	activeCodec = codecId;
	if(id.Find("mp3") >= 0) {
		ShowPanel(mp3Panel);
	}
	else if(id.Find("wave") >= 0 || id.Find("wav") >= 0) {
		ShowPanel(wavPanel);
	}
	else {
		ShowPanel(placeholderPanel);
	}
}

void CodecOptionsPane::GetCodecSettings(ValueMap& settings) const {
	settings.Clear();
	settings("codec") = activeCodec;
	settings("wavInsertBroadcast") = (bool)wavInsertBroadcast.Get();
	settings("wavDisableExtensible") = (bool)wavDisableExtensible.Get();
	settings("wavInsertIXML") = (bool)wavInsertIXML.Get();
	settings("mp3BitRate") = mp3BitRate.GetData();
	settings("mp3SampleRate") = mp3SampleRate.GetData();
	settings("mp3HighQuality") = (bool)mp3HighQuality.Get();
	settings("mp3InsertID3") = (bool)mp3InsertID3.Get();
}

void CodecOptionsPane::SetCodecSettings(const ValueMap& settings) {
	if(settings.Find("wavInsertBroadcast") >= 0)
		wavInsertBroadcast.Set(const_cast<ValueMap&>(settings).Get("wavInsertBroadcast", false));
	if(settings.Find("wavDisableExtensible") >= 0)
		wavDisableExtensible.Set(const_cast<ValueMap&>(settings).Get("wavDisableExtensible", false));
	if(settings.Find("wavInsertIXML") >= 0)
		wavInsertIXML.Set(const_cast<ValueMap&>(settings).Get("wavInsertIXML", false));
	if(settings.Find("mp3BitRate") >= 0)
		mp3BitRate.SetData(const_cast<ValueMap&>(settings).Get("mp3BitRate", 128));
	if(settings.Find("mp3SampleRate") >= 0)
		mp3SampleRate.SetData(const_cast<ValueMap&>(settings).Get("mp3SampleRate", 44100));
	if(settings.Find("mp3HighQuality") >= 0)
		mp3HighQuality.Set(const_cast<ValueMap&>(settings).Get("mp3HighQuality", false));
	if(settings.Find("mp3InsertID3") >= 0)
		mp3InsertID3.Set(const_cast<ValueMap&>(settings).Get("mp3InsertID3", false));
}

// --- ID3TagDialog ---------------------------------------------------------

ID3TagDialog::ID3TagDialog() {
	Title("Edit ID3 Tag");
	Sizeable().Zoomable(false);
	MinimizeBox(false);
	MaximizeBox(false);
	SetupLayout();
}

void ID3TagDialog::SetupLayout() {
	Label titleLabel;
	titleLabel.SetLabel("Title:");
	Add(titleLabel.TopPos(8, 20).LeftPos(8, 80));
	Add(title.TopPos(8, 20).LeftPos(96, 200));

	Label artistLabel;
	artistLabel.SetLabel("Artist:");
	Add(artistLabel.TopPos(36, 20).LeftPos(8, 80));
	Add(artist.TopPos(36, 20).LeftPos(96, 200));

	Label albumLabel;
	albumLabel.SetLabel("Album:");
	Add(albumLabel.TopPos(64, 20).LeftPos(8, 80));
	Add(album.TopPos(64, 20).LeftPos(96, 200));

	Label yearLabel;
	yearLabel.SetLabel("Year:");
	Add(yearLabel.TopPos(92, 20).LeftPos(8, 80));
	Add(year.TopPos(92, 20).LeftPos(96, 80));

	Label genreLabel;
	genreLabel.SetLabel("Genre:");
	Add(genreLabel.TopPos(120, 20).LeftPos(8, 80));
	Add(genre.TopPos(120, 20).LeftPos(96, 200));

	Label commentLabel;
	commentLabel.SetLabel("Comment:");
	Add(commentLabel.TopPos(148, 20).LeftPos(8, 80));
	Add(comment.TopPos(148, 60).LeftPos(96, 200));

	okButton.SetLabel("OK");
	okButton.WhenAction = THISBACK(OnOK);
	Add(okButton.BottomPos(8, 24).RightPos(88, 80));

	cancelButton.SetLabel("Cancel");
	cancelButton.WhenAction = THISBACK(OnCancel);
	Add(cancelButton.BottomPos(8, 24).RightPos(8, 80));

	SetRect(Size(320, 240));
}

void ID3TagDialog::OnOK() {
	Close();
}

void ID3TagDialog::OnCancel() {
	title.Clear();
	artist.Clear();
	album.Clear();
	year.Clear();
	genre.Clear();
	comment.Clear();
	Close();
}

void ID3TagDialog::SetTags(const ValueMap& tags) {
	title.SetData(const_cast<ValueMap&>(tags).Get("Title", String()));
	artist.SetData(const_cast<ValueMap&>(tags).Get("Artist", String()));
	album.SetData(const_cast<ValueMap&>(tags).Get("Album", String()));
	year.SetData(const_cast<ValueMap&>(tags).Get("Year", String()));
	genre.SetData(const_cast<ValueMap&>(tags).Get("Genre", String()));
	comment.SetData(const_cast<ValueMap&>(tags).Get("Comment", String()));
}

ValueMap ID3TagDialog::GetTags() const {
	ValueMap tags;
	tags("Title") = title.GetData();
	tags("Artist") = artist.GetData();
	tags("Album") = album.GetData();
	tags("Year") = year.GetData();
	tags("Genre") = genre.GetData();
	tags("Comment") = comment.GetData();
	return tags;
}

// --- ExportProgressDialog -------------------------------------------------

ExportProgressDialog::ExportProgressDialog() {
	Title("Exporting...");
	Size(360, 120);
	MinimizeBox(false);
	MaximizeBox(false);
	progress.SetTotal(100);
	progress.Set(0);
	Add(progress.TopPos(20, 24).HSizePos(20, 20));
	cancelButton.SetLabel("Cancel");
	cancelButton.WhenAction = THISBACK(OnCancel);
	Add(cancelButton.BottomPos(20, 24).RightPos(20, 100));
}

void ExportProgressDialog::SetProgress(int percent) {
	progress.Set(percent);
}

void ExportProgressDialog::OnCancel() {
	WhenCancel();
}

// --- ExportAudioMixdownDialog --------------------------------------------

ExportAudioMixdownDialog::ExportAudioMixdownDialog() {
	Title("Export Audio Mixdown");
	Sizeable().Zoomable();
	BuildLayout();
	fileType.WhenAction = THISBACK(OnFileTypeChanged);
	browseButton.WhenAction = THISBACK(OnBrowsePath);
	exportButton.WhenAction = THISBACK(OnExport);
	closeButton.WhenAction = THISBACK(OnCloseDialog);
	batchExportButton.WhenAction = THISBACK(OnBatchExport);
	codecPane.WhenEditID3 = THISBACK(OnEditID3);

	SetFileTypes({"Wave File", "AIFF File", "MPEG1 Layer 3 File", "Ogg Vorbis File", "Windows Media Audio File", "Wave64 File"});
	SetSampleRates({32000, 44100, 48000, 88200, 96000});
	SetBitDepths({16, 24, 32});
	SetDefaultPath(Upp::ConfigFile("Home"));
	SetDefaultFilename("Mixdown");

	monoExport.SetLabel("Mono Export");
	realTimeExport.SetLabel("Real-Time Export");
	splitChannels.SetLabel("Split Channels");
	updateDisplay.SetLabel("Update Display");
	addToPool.SetLabel("Pool");
	addToPool.Set(true);
	createAudioTrack.SetLabel("Audio Track");
	closeAfterExport.SetLabel("Close dialog after export");
}

void ExportAudioMixdownDialog::BuildLayout() {
	Add(contentSplit.SizePos());

	contentSplit.Horz(leftPane, configPane);
	contentSplit.SetPos(2600);

	leftPane.Add(batchExportButton.TopPos(0, 28).HSizePos());
	batchExportButton.SetLabel("Channel Batch Export");
	leftPane.Add(channelPane.VSizePos(28, 0).HSizePos());

	Label filenameLabel;
	filenameLabel.SetText("Filename:");
	configPane.Add(filenameLabel.TopPos(0, 20).LeftPos(0, 100));
	configPane.Add(filenameEdit.TopPos(0, 20).LeftPos(104, 220));

	Label pathLabel;
	pathLabel.SetText("Path:");
	configPane.Add(pathLabel.TopPos(28, 20).LeftPos(0, 100));
	configPane.Add(pathEdit.TopPos(28, 20).LeftPos(104, 220));
	browseButton.SetLabel("Browse...");
	configPane.Add(browseButton.TopPos(28, 20).RightPos(0, 100));

	Label fileTypeLabel;
	fileTypeLabel.SetText("File Type:");
	configPane.Add(fileTypeLabel.TopPos(56, 20).LeftPos(0, 100));
	configPane.Add(fileType.TopPos(56, 20).LeftPos(104, 220));

	configPane.Add(codecPane.TopPos(84, 150).HSizePos());

	Label sampleRateLabel;
	sampleRateLabel.SetText("Sample Rate:");
	configPane.Add(sampleRateLabel.TopPos(242, 20).LeftPos(0, 100));
	configPane.Add(sampleRate.TopPos(242, 20).LeftPos(104, 140));

	Label bitDepthLabel;
	bitDepthLabel.SetText("Bit Depth:");
	configPane.Add(bitDepthLabel.TopPos(270, 20).LeftPos(0, 100));
	configPane.Add(bitDepth.TopPos(270, 20).LeftPos(104, 140));

	configPane.Add(monoExport.TopPos(302, 20).LeftPos(0, 180));
	configPane.Add(realTimeExport.TopPos(330, 20).LeftPos(0, 180));
	configPane.Add(splitChannels.TopPos(358, 20).LeftPos(0, 180));
	configPane.Add(updateDisplay.TopPos(386, 20).LeftPos(0, 180));

	configPane.Add(addToPool.TopPos(414, 20).LeftPos(0, 180));
	configPane.Add(createAudioTrack.TopPos(442, 20).LeftPos(0, 180));
	configPane.Add(closeAfterExport.TopPos(470, 20).LeftPos(0, 220));

	exportButton.SetLabel("Export");
	configPane.Add(exportButton.BottomPos(0, 28).RightPos(0, 100));

	closeButton.SetLabel("Close");
	configPane.Add(closeButton.BottomPos(0, 28).RightPos(108, 100));
}

void ExportAudioMixdownDialog::SetChannels(const Vector<ExportChannel>& channels) {
	channelPane.SetChannels(channels);
}

void ExportAudioMixdownDialog::SetFileTypes(const Vector<String>& types) {
	fileType.Clear();
	for(const String& type : types)
		fileType.Add(type);
	if(!types.IsEmpty())
		fileType.SetIndex(0);
}

void ExportAudioMixdownDialog::SetSampleRates(const Vector<int>& rates) {
	sampleRate.Clear();
	for(int rate : rates) {
		double khz = rate / 1000.0;
		sampleRate.Add(rate, Format("%.1f kHz", khz));
	}
	if(!rates.IsEmpty()) {
		int index = rates.GetCount() > 1 ? 1 : 0;
		sampleRate.SetData(rates[index]);
	}
}

void ExportAudioMixdownDialog::SetBitDepths(const Vector<int>& depths) {
	bitDepth.Clear();
	for(int depth : depths)
		bitDepth.Add(depth, Format("%d-bit", depth));
	if(!depths.IsEmpty()) {
		int index = depths.GetCount() > 1 ? 1 : 0;
		bitDepth.SetData(depths[index]);
	}
}

void ExportAudioMixdownDialog::SetDefaultPath(const String& path) {
	pathEdit.SetData(path);
}

void ExportAudioMixdownDialog::SetDefaultFilename(const String& name) {
	filenameEdit.SetData(name);
}

void ExportAudioMixdownDialog::SetCodecSettings(const ValueMap& settings) {
	codecPane.SetCodecSettings(settings);
}

ExportRequest ExportAudioMixdownDialog::CollectRequest() const {
	ExportRequest req;
	req.filename = filenameEdit.GetData();
	req.directory = pathEdit.GetData();
	req.fileType = ~fileType;
	req.channels = channelPane.GatherSelection();
	codecPane.GetCodecSettings(req.codecSettings);
	Value sr = sampleRate.GetData();
	req.sampleRate = IsNull(sr) ? 44100 : (int)sr;
	Value bd = bitDepth.GetData();
	req.bitDepth = IsNull(bd) ? 24 : (int)bd;
	req.monoExport = monoExport.Get();
	req.realTimeExport = realTimeExport.Get();
	req.splitChannels = splitChannels.Get();
	req.updateDisplay = updateDisplay.Get();
	req.addToPool = addToPool.Get();
	req.createAudioTrack = createAudioTrack.Get();
	req.closeAfterExport = closeAfterExport.Get();
	return req;
}

void ExportAudioMixdownDialog::OnExport() {
	ExportRequest req = CollectRequest();
	WhenExport(req);
}

void ExportAudioMixdownDialog::OnCloseDialog() {
	Close();
	WhenDialogClose();
}

void ExportAudioMixdownDialog::OnBrowsePath() {
	WhenBrowsePath();
}

void ExportAudioMixdownDialog::OnFileTypeChanged() {
	codecPane.SetCodec(~fileType);
}

void ExportAudioMixdownDialog::OnEditID3() {
	ValueMap tags;
	WhenEditID3(tags);
	id3Dialog.SetTags(tags);
	id3Dialog.Open();
}

void ExportAudioMixdownDialog::OnBatchExport() {
	WhenBatchExport();
}

}
