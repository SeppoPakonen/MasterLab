#include "VSTConnections.h"

namespace VSTConnections {

CuteAudioIOMatrixForm::CuteAudioIOMatrixForm() {
}

void CuteAudioIOMatrixForm::SetChannels(int input_channels, int output_channels) {
    this->input_channels = input_channels;
    this->output_channels = output_channels;
}

int CuteAudioIOMatrixForm::GetInputChannels() const { return input_channels; }
int CuteAudioIOMatrixForm::GetOutputChannels() const { return output_channels; }
void CuteAudioIOMatrixForm::SetMatrix(const Vector<int>& matrix) { this->matrix = matrix; }
const Vector<int>& CuteAudioIOMatrixForm::GetMatrix() const { return matrix; }
void CuteAudioIOMatrixForm::RefreshMatrix() {}
const Vector<int>& CuteAudioIOMatrixForm::GetGroups() const { return groups; }
void CuteAudioIOMatrixForm::InputChannelsChanged(int index) { input_channels = index; }
void CuteAudioIOMatrixForm::OutputChannelsChanged(int index) { output_channels = index; }
void CuteAudioIOMatrixForm::Accept() {}
void CuteAudioIOMatrixForm::Reject() {}

CuteAudioIOMatrixForm::TableWidget::TableWidget() {}
void CuteAudioIOMatrixForm::TableWidget::SetForm(CuteAudioIOMatrixForm* form) { this->form = form; }
CuteAudioIOMatrixForm* CuteAudioIOMatrixForm::TableWidget::GetForm() const { return form; }
bool CuteAudioIOMatrixForm::TableWidget::IsDirty() const { return dirty != 0; }
void CuteAudioIOMatrixForm::TableWidget::ToggleCell(int row, int col) { (void)row; (void)col; dirty++; }

}
