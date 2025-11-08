#include "Modulation.h"

namespace DSP {

// MotionSequencer implementation
MotionSequencer::MotionSequencer() : currentPosition(0.0), sequenceLength(16), isPlaying(false) {
    // Initialize with default values
}

void MotionSequencer::AddStep(const ParameterId& paramId, int step, double value, int duration) {
    // Find or create sequence for this parameter
    int seqIdx = -1;
    for (int i = 0; i < sequences.GetCount(); i++) {
        if (sequences[i].paramId == paramId) {
            seqIdx = i;
            break;
        }
    }
    
    if (seqIdx == -1) {
        // Create new sequence
        Sequence seq;
        seq.paramId = paramId;
        sequences.Add(seq);
        seqIdx = sequences.GetCount() - 1;
    }
    
    // Add the step
    sequences[seqIdx].steps.Add(Step(step, value, duration));
}

void MotionSequencer::SetPosition(double pos) {
    currentPosition = max(0.0, min(1.0, pos));
}

double MotionSequencer::GetCurrentValue(const ParameterId& paramId) const {
    for (const auto& seq : sequences) {
        if (seq.paramId == paramId) {
            // Find the step at the current position
            int currentStep = (int)(currentPosition * sequenceLength);
            
            // Linear interpolation between adjacent steps
            for (int i = 0; i < seq.steps.GetCount(); i++) {
                if (seq.steps[i].position <= currentStep && 
                    (i == seq.steps.GetCount() - 1 || seq.steps[i+1].position > currentStep)) {
                    
                    if (i == seq.steps.GetCount() - 1) {
                        return seq.steps[i].value;
                    }
                    
                    // Interpolate between this step and the next
                    int step1_pos = seq.steps[i].position;
                    int step2_pos = seq.steps[i+1].position;
                    double step1_val = seq.steps[i].value;
                    double step2_val = seq.steps[i+1].value;
                    
                    if (step2_pos > step1_pos) {
                        double ratio = (currentStep - step1_pos) / double(step2_pos - step1_pos);
                        return step1_val + ratio * (step2_val - step1_val);
                    } else {
                        return step1_val;
                    }
                }
            }
        }
    }
    return 0.0; // Default value if parameter not found
}

void MotionSequencer::Process() {
    // Update internal state based on playback
    if (isPlaying) {
        currentPosition += 0.01; // Simple increment for demo
        if (currentPosition > 1.0) {
            currentPosition = 0.0; // Loop
        }
    }
}

void MotionSequencer::Reset() {
    currentPosition = 0.0;
    isPlaying = false;
}

void MotionSequencer::SetSequenceLength(int steps) {
    sequenceLength = max(1, steps);
}

// SceneMorph implementation
SceneMorph::SceneMorph() : morphPosition(0.0) {
    // Initialize
}

void SceneMorph::SetScenes(const ParameterSet& scene1, const ParameterSet& scene2) {
    this->scene1 = scene1;
    this->scene2 = scene2;
}

void SceneMorph::SetMorphPosition(double pos) {
    morphPosition = max(0.0, min(1.0, pos));
}

ParameterSet SceneMorph::GetMorphedParameters() const {
    ParameterSet result = scene1; // Start with scene1
    
    // Interpolate values from both scenes
    Vector<ParameterId> ids = scene1.GetParameterIds();
    for (const auto& id : ids) {
        double val1 = scene1.Get(id);
        double val2 = scene2.Get(id);
        double interpolated = val1 + morphPosition * (val2 - val1);
        result.Set(id, interpolated);
    }
    
    return result;
}

void SceneMorph::Process() {
    // In a real implementation, this would handle smooth transitions
}

void SceneMorph::Reset() {
    morphPosition = 0.0;
}

// StepSequencer implementation
StepSequencer::StepSequencer() : currentStep(0), numSteps(16), running(false) {
    // Initialize with 16 steps by default
}

void StepSequencer::SetStep(const ParameterId& paramId, int step, double value) {
    // Find or create parameter steps
    int paramIdx = -1;
    for (int i = 0; i < parameterSteps.GetCount(); i++) {
        if (parameterSteps[i].paramId == paramId) {
            paramIdx = i;
            break;
        }
    }
    
    if (paramIdx == -1) {
        // Create new parameter steps
        ParameterStep ps;
        ps.paramId = paramId;
        ps.steps.SetCount(numSteps);
        parameterSteps.Add(ps);
        paramIdx = parameterSteps.GetCount() - 1;
    }
    
    // Ensure the steps vector is large enough
    if (step >= parameterSteps[paramIdx].steps.GetCount()) {
        parameterSteps[paramIdx].steps.SetCount(step + 1);
    }
    
    parameterSteps[paramIdx].steps[step] = value;
}

double StepSequencer::GetStepValue(const ParameterId& paramId, int step) const {
    for (const auto& ps : parameterSteps) {
        if (ps.paramId == paramId && step < ps.steps.GetCount()) {
            return ps.steps[step];
        }
    }
    return 0.0;
}

void StepSequencer::SetCurrentStep(int step) {
    currentStep = max(0, min(numSteps - 1, step));
}

void StepSequencer::NextStep() {
    currentStep = (currentStep + 1) % numSteps;
}

void StepSequencer::SetNumSteps(int steps) {
    numSteps = max(1, steps);
    
    // Resize all parameter step vectors
    for (auto& ps : parameterSteps) {
        ps.steps.SetCount(numSteps);
    }
}

void StepSequencer::Process() {
    // In a real implementation, this would be called at tempo-synced intervals
}

void StepSequencer::Reset() {
    currentStep = 0;
    running = false;
}

// ModuleSwitcher implementation
ModuleSwitcher::ModuleSwitcher() : activeModuleIndex(0) {
    // Initialize
}

void ModuleSwitcher::AddModule(const String& name, ParameterSet& params) {
    Module module;
    module.name = name;
    module.params = params;
    modules.Add(module);
}

bool ModuleSwitcher::SwitchToModule(const String& name) {
    for (int i = 0; i < modules.GetCount(); i++) {
        if (modules[i].name == name) {
            activeModuleIndex = i;
            return true;
        }
    }
    return false;
}

String ModuleSwitcher::GetActiveModule() const {
    if (activeModuleIndex >= 0 && activeModuleIndex < modules.GetCount()) {
        return modules[activeModuleIndex].name;
    }
    return "";
}

Vector<String> ModuleSwitcher::GetModuleNames() const {
    Vector<String> names;
    for (const auto& module : modules) {
        names.Add(module.name);
    }
    return names;
}

ParameterSet& ModuleSwitcher::GetActiveParameters() {
    if (activeModuleIndex >= 0 && activeModuleIndex < modules.GetCount()) {
        return modules[activeModuleIndex].params;
    }
    return modules[0].params; // Return first module if out of bounds
}

void ModuleSwitcher::Reset() {
    activeModuleIndex = 0;
}

// MacroController implementation
MacroController::MacroController() : macroValue(0.0) {
    // Initialize
}

void MacroController::AddParameter(const ParameterId& paramId, double weight) {
    MacroParam mp;
    mp.id = paramId;
    mp.weight = weight;
    parameters.Add(mp);
}

void MacroController::SetValue(double value) {
    macroValue = max(0.0, min(1.0, value));
}

void MacroController::Process(ParameterSet& params) {
    // Update all controlled parameters based on macro value
    for (const auto& mp : parameters) {
        double currentVal = params.Get(mp.id);
        double minVal = params.GetMin(mp.id);
        double maxVal = params.GetMax(mp.id);
        
        // Calculate new value based on macro position and weight
        double newValue = minVal + macroValue * (maxVal - minVal);
        newValue = currentVal + mp.weight * (newValue - currentVal);
        
        params.Set(mp.id, newValue);
    }
}

void MacroController::Reset() {
    macroValue = 0.0;
}

} // namespace DSP