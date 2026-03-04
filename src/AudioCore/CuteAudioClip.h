#ifndef _AudioCore_CuteAudioClip_h_
#define _AudioCore_CuteAudioClip_h_

class CuteAudioPeak;
class CuteTrack;
class CuteDocument;
class CuteXmlElement;

class CuteClip {};

class CuteAudioClip : public CuteClip {
public:
	class Key;
	class Data;
	typedef VectorMap<String, Data*> Hash;

	CuteAudioClip(CuteTrack* track);
	CuteAudioClip(const CuteAudioClip& clip);
	~CuteAudioClip();

	void SetTimeStretch(float time_stretch);
	float GetTimeStretch() const;
	void SetPitchShift(float pitch_shift);
	float GetPitchShift() const;
	void SetStretcherFlags(unsigned int stretcher_flags);
	unsigned int GetStretcherFlags() const;
	void SetStretcherFlag(unsigned int stretcher_flag, bool is_on);
	bool IsStretcherFlag(unsigned int stretcher_flag) const;
	unsigned int GetOverlap() const;
	void Open();
	bool OpenAudioFile(const String& file_name, int mode = 0);
	CuteAudioBuffer* GetBuffer() const;
	void Write(float** buffer, unsigned int frames, unsigned short channels = 0, unsigned int offset = 0);
	void Seek(unsigned long frame);
	void Reset(bool looping);
	void SetLoop(unsigned long loop_start, unsigned long loop_end);
	void Close();
	void Process(unsigned long frame_start, unsigned long frame_end);
	void ProcessExport(unsigned long frame_start, unsigned long frame_end);
	String ToolTip() const;
	bool ClipExport(unsigned long offset = 0, unsigned long length = 0) const;
	void InsertHashKey();
	void UpdateHashKey();
	void RemoveHashKey();
	void UnlinkHashData();
	void RelinkHashData();
	bool IsHashLinked() const;
	static void ClearHashTable();

protected:
	bool LoadClipElement(CuteDocument* document, CuteXmlElement* element);
	bool SaveClipElement(CuteDocument* document, CuteXmlElement* element);
	void CloseAudioFile();
	bool IsOverlap(unsigned int overlap_size) const;
	void UpdateFractGains(CuteAudioBuffer* buffer);

private:
	CuteTrack* track = nullptr;
	CuteAudioPeak* peak = nullptr;
	Data* data = nullptr;
	float time_stretch = 1.0f;
	float pitch_shift = 1.0f;
	unsigned int stretcher_flags = 0;
	unsigned int overlap = 0;
};

class CuteAudioClip::Data {
public:
	Data(CuteAudioBufferThread* sync_thread, unsigned short channels);
	~Data();

	CuteAudioBuffer* GetBuffer() const;
	void Write(float** buffer, unsigned int frames, unsigned short channels, unsigned int offset);
	void SyncExport();
	void Seek(unsigned long frame);
	void Reset(bool looping);
	void SetLoop(unsigned long loop_start, unsigned long loop_end);
	void Attach(CuteAudioClip* clip);
	void Detach(CuteAudioClip* clip);
	unsigned short GetCount() const;
	const Vector<CuteAudioClip*>& GetClips() const;
	void Clear();

private:
	One<CuteAudioBuffer> buffer;
	Vector<CuteAudioClip*> clips;
};

#endif
