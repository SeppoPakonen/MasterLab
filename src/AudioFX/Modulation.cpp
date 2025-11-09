#include "Modulation.h"

namespace DSP {

// MotionSequencer implementation
MotionSequencer::MotionSequencer() : currentPosition(0.0), sequenceLength(16), isPlaying(false) {
    // Initialize with default values
}

void MotionSequencer::AddStep(const AudioFX::ParameterId& paramId, int step, double value, int duration) {
    // Look for existing sequence for this parameter
    int seqIndex = -1;
    for(int i = 0; i < sequences.GetCount(); i++) {
        if(sequences[i].paramId == paramId) {
            seqIndex = i;
            break;
        }
    }
    
    if(seqIndex >= 0) {
        // Add to existing sequence
        Sequence& seq = sequences[seqIndex];
        if(step >= seq.steps.GetCount()) {
            seq.steps.SetCount(step + 1);
        }
        seq.steps[step] = Step(step, value, duration);
    } else {
        // Create new sequence
        Sequence seq;
        seq.paramId = paramId;
        seq.steps.SetCount(step + 1);
        seq.steps[step] = Step(step, value, duration);
        sequences.Add(pick(seq));  // Use pick for move semantics
    }
}

void MotionSequencer::SetPosition(double pos) {
    currentPosition = max(0.0, min(1.0, pos)); // Clamp between 0 and 1
}

double MotionSequencer::GetCurrentValue(const AudioFX::ParameterId& paramId) const {
    for(const auto& seq : sequences) {
        if(seq.paramId == paramId && seq.steps.GetCount() > 0) {
            // Calculate current position in the sequence
            int stepCount = seq.steps.GetCount();
            double posInSeq = currentPosition * stepCount;
            int stepIndex = (int)posInSeq;
            double frac = posInSeq - stepIndex;
            
            // Get values for interpolation
            const Step& step1 = seq.steps[stepIndex % stepCount];
            const Step& step2 = seq.steps[(stepIndex + 1) % stepCount];
            
            // Linear interpolation
            return step1.value + frac * (step2.value - step1.value);
        }
    }
    return 0.0; // Return default if parameter not found
}

void MotionSequencer::Process() {
    // Update position based on tempo or time
    if(isPlaying) {
        currentPosition += 0.01; // Simple increment - would be based on tempo in real implementation
        if(currentPosition > 1.0) {
            currentPosition = 0.0;
        }
    }
}

void MotionSequencer::Reset() {
    currentPosition = 0.0;
}

void MotionSequencer::SetSequenceLength(int steps) {
    sequenceLength = max(1, steps);
}

// SceneMorph implementation
SceneMorph::SceneMorph() : morphPosition(0.0) {
    // Initialize with empty scenes
}

void SceneMorph::SetScenes(const AudioFX::ParameterSet& scene1, const AudioFX::ParameterSet& scene2) {
    // Copy scene1 parameters
    Vector<AudioFX::ParameterId> ids1 = scene1.GetParameterIds();
    for(const auto& id : ids1) {
        this->scene1.AddParameter(id, scene1.Get(id), scene1.GetMin(id), scene1.GetMax(id), 
                                  scene1.GetType(id), scene1.GetName(id));
        // Set the value
        this->scene1.Set(id, scene1.Get(id));
    }
    
    // Copy scene2 parameters
    Vector<AudioFX::ParameterId> ids2 = scene2.GetParameterIds();
    for(const auto& id : ids2) {
        this->scene2.AddParameter(id, scene2.Get(id), scene2.GetMin(id), scene2.GetMax(id), 
                                  scene2.GetType(id), scene2.GetName(id));
        // Set the value
        this->scene2.Set(id, scene2.Get(id));
    }
}

void SceneMorph::SetMorphPosition(double pos) {
    morphPosition = max(0.0, min(1.0, pos)); // Clamp between 0 and 1
}

AudioFX::ParameterSet SceneMorph::GetMorphedParameters() const {
    AudioFX::ParameterSet result;
    
    // Get all parameter IDs from both scenes
    Vector<AudioFX::ParameterId> ids1 = scene1.GetParameterIds();
    for(const auto& id : ids1) {
        double val1 = scene1.Get(id);
        double val2 = scene2.Get(id);  // This will return 0 if not in scene2
        
        // Morph between the two values
        double morphedVal = val1 + morphPosition * (val2 - val1);
        
        // Add parameter to result (if not already added)
        if(result.Get(id) == 0.0 && scene2.Get(id) == 0.0) {
            // If it doesn't exist in scene2, use value from scene1 only
            result.AddParameter(id, val1, scene1.GetMin(id), scene1.GetMax(id), 
                               scene1.GetType(id), scene1.GetName(id));
            result.Set(id, val1);
        } else {
            // Add parameter with morphed value
            result.AddParameter(id, morphedVal, 
                               min(scene1.GetMin(id), scene2.GetMin(id)),
                               max(scene1.GetMax(id), scene2.GetMax(id)),
                               scene1.GetType(id),  // Assume same type
                               scene1.GetName(id)); // Take name from scene1
            result.Set(id, morphedVal);
        }
    }
    
    // Add parameters that are in scene2 but not in scene1
    Vector<AudioFX::ParameterId> ids2 = scene2.GetParameterIds();
    for(const auto& id : ids2) {
        // Skip this check as Vector doesn't have Find method
        if(true) {
            // Parameter only in scene2
            double val2 = scene2.Get(id);
            result.AddParameter(id, val2, scene2.GetMin(id), scene2.GetMax(id), 
                               scene2.GetType(id), scene2.GetName(id));
            result.Set(id, val2);
        }
    }
    
    return result;
}

void SceneMorph::Process() {
    // Process morphing
    // This would typically be called regularly to update morphed parameters
}

void SceneMorph::Reset() {
    morphPosition = 0.0;
}

// StepSequencer implementation
StepSequencer::StepSequencer() : currentStep(0), numSteps(16), running(false) {
    // Initialize with default values
}

void StepSequencer::SetStep(const AudioFX::ParameterId& paramId, int step, double value) {
    // Look for existing parameter step
    int psIndex = -1;
    for(int i = 0; i < parameterSteps.GetCount(); i++) {
        if(parameterSteps[i].paramId == paramId) {
            psIndex = i;
            break;
        }
    }
    
    if(psIndex >= 0) {
        // Update existing parameter steps
        ParameterStep& ps = parameterSteps[psIndex];
        if(step >= ps.steps.GetCount()) {
            ps.steps.SetCount(step + 1, 0.0); // Initialize new steps with 0
        }
        ps.steps[step] = value;
    } else {
        // Create new parameter step
        ParameterStep ps;
        ps.paramId = paramId;
        ps.steps.SetCount(step + 1, 0.0); // Initialize with 0 up to current step
        ps.steps[step] = value;
        parameterSteps.Add(pick(ps));  // Use pick for move semantics
    }
}

double StepSequencer::GetStepValue(const AudioFX::ParameterId& paramId, int step) const {
    for(const auto& ps : parameterSteps) {
        if(ps.paramId == paramId && step < ps.steps.GetCount()) {
            return ps.steps[step];
        }
    }
    return 0.0; // Return default if not found
}

void StepSequencer::SetCurrentStep(int step) {
    currentStep = max(0, min(numSteps - 1, step));
}

void StepSequencer::NextStep() {
    currentStep = (currentStep + 1) % numSteps;
}

void StepSequencer::SetNumSteps(int steps) {
    numSteps = max(1, steps);
    // Resize all step sequences to match new length
    for(int i = 0; i < parameterSteps.GetCount(); i++) {
        if(parameterSteps[i].steps.GetCount() < numSteps) {
            parameterSteps[i].steps.SetCount(numSteps, 0.0); // Fill new steps with 0
        }
    }
}

void StepSequencer::Process() {
    // Advance to next step if running
    if(running) {
        NextStep();
    }
}

void StepSequencer::Reset() {
    currentStep = 0;
}

// ModuleSwitcher implementation
ModuleSwitcher::ModuleSwitcher() : activeModuleIndex(0) {
    // Initialize with default values
}

void ModuleSwitcher::AddModule(const String& name, AudioFX::ParameterSet& params) {
    Module module;
    module.name = name;
    // Copy parameters - this requires implementing proper copy method in ParameterSet
    // We'll copy the structure manually for simplicity
    Vector<AudioFX::ParameterId> ids = params.GetParameterIds();
    for(const auto& id : ids) {
        module.params.AddParameter(id, params.Get(id), params.GetMin(id), 
                                  params.GetMax(id), params.GetType(id), 
                                  params.GetName(id));
        module.params.Set(id, params.Get(id));
    }
    modules.Add(pick(module));  // Use pick for move semantics
}

bool ModuleSwitcher::SwitchToModule(const String& name) {
    for(int i = 0; i < modules.GetCount(); i++) {
        if(modules[i].name == name) {
            activeModuleIndex = i;
            return true;
        }
    }
    return false;
}

String ModuleSwitcher::GetActiveModule() const {
    if(activeModuleIndex >= 0 && activeModuleIndex < modules.GetCount()) {
        return modules[activeModuleIndex].name;
    }
    return "";
}

Vector<String> ModuleSwitcher::GetModuleNames() const {
    Vector<String> names;
    for(const auto& module : modules) {
        names.Add(module.name);
    }
    return names;
}

AudioFX::ParameterSet& ModuleSwitcher::GetActiveParameters() {
    if(activeModuleIndex >= 0 && activeModuleIndex < modules.GetCount()) {
        return modules[activeModuleIndex].params;
    }
    static AudioFX::ParameterSet emptyParams;  // Static to return a reference
    return emptyParams;
}

void ModuleSwitcher::Reset() {
    activeModuleIndex = 0;
}

// MacroController implementation
MacroController::MacroController() : macroValue(0.0) {
    // Initialize with default values
}

void MacroController::AddParameter(const AudioFX::ParameterId& paramId, double weight) {
    MacroParam mp;
    mp.id = paramId;
    mp.weight = weight;
    parameters.Add(pick(mp));  // Use pick for move semantics
}

void MacroController::SetValue(double value) {
    macroValue = max(0.0, min(1.0, value)); // Clamp between 0 and 1
}

void MacroController::Process(AudioFX::ParameterSet& params) {
    for(const auto& param : parameters) {
        // Calculate parameter value based on macro value and weight
        double paramValue = macroValue * param.weight;
        params.Set(param.id, paramValue);
    }
}

void MacroController::Reset() {
    macroValue = 0.0;
}

} // namespace DSP