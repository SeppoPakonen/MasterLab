#ifndef _AudioMaster_CuteApplication_h_
#define _AudioMaster_CuteApplication_h_

// Main package header provides Core/Ctrl declarations.

class CuteApplication {
public:
	CuteApplication();
	~CuteApplication();

	void SetMainWidget(Ctrl* widget);
	Ctrl* GetMainWidget() const;
	bool SetupSingleInstance();
	void ClearServerState();
	void OnNewConnection();
	void OnReadyRead();
	int Run();

private:
	struct Data;
	One<Data> data;
};

int RunCuteApplication(const Vector<String>& args);

#endif
