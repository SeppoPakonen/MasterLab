#ifndef _VSTHost_CuteVst3Plugin_h_
#define _VSTHost_CuteVst3Plugin_h_

class CuteVst3Plugin : public CutePlugin {
public:
    CuteVst3Plugin();

    bool Activate() override;
    void Deactivate() override;
    void Process() override;
    bool OpenEditor() override;
    void CloseEditor() override;

private:
    bool active = false;
};

#endif
