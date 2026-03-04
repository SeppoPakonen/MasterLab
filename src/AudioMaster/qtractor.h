#ifndef _AudioMaster_qtractor_h_
#define _AudioMaster_qtractor_h_

// Main package header provides Core/Ctrl declarations.

struct CuteBootConfig;

class qtractorApplication {
public:
	qtractorApplication();
	~qtractorApplication();

	void setMainWidget(Ctrl* widget);
	Ctrl* mainWidget() const;
	bool setup();
	void clearServer();
	void newConnectionSlot();
	void readyReadSlot();
	int Run();

private:
	struct Data;
	One<Data> data;
};

int qtractor_main(const Vector<String>& args);

#endif
