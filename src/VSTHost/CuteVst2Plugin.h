#ifndef _VSTHost_CuteVst2Plugin_h_
#define _VSTHost_CuteVst2Plugin_h_

class CuteVst2Plugin : public CutePlugin {
public:
    CuteVst2Plugin();

    bool Activate() override;
    void Deactivate() override;
    void Process() override;
    bool OpenEditor() override;
    void CloseEditor() override;

private:
    bool active = false;
};

#endif
