#ifndef _VSTConnections_CuteAudioIOMatrixForm_h_
#define _VSTConnections_CuteAudioIOMatrixForm_h_

namespace VSTConnections {

class CuteAudioIOMatrixForm : public ParentCtrl {
public:
    class TableWidget;
    class TableCell;
    class RadioButton;
    typedef CuteAudioIOMatrixForm CLASSNAME;

    CuteAudioIOMatrixForm();
    void SetChannels(int input_channels, int output_channels);
    int GetInputChannels() const;
    int GetOutputChannels() const;
    void SetMatrix(const Vector<int>& matrix);
    const Vector<int>& GetMatrix() const;
    void RefreshMatrix();
    const Vector<int>& GetGroups() const;
    void InputChannelsChanged(int index);
    void OutputChannelsChanged(int index);
    void Accept();
    void Reject();

private:
    int input_channels = 0;
    int output_channels = 0;
    Vector<int> groups;
    Vector<int> matrix;
};

class CuteAudioIOMatrixForm::TableWidget : public ArrayCtrl {
public:
    typedef TableWidget CLASSNAME;
    TableWidget();
    void SetForm(CuteAudioIOMatrixForm* form);
    CuteAudioIOMatrixForm* GetForm() const;
    bool IsDirty() const;
    void ToggleCell(int row, int col);

private:
    Ptr<CuteAudioIOMatrixForm> form;
    int dirty = 0;
};

}

#endif
