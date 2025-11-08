#ifndef _AudioFX_Modulation_h_
#define _AudioFX_Modulation_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "ParameterSet.h"
#include "ModMatrix.h"

using namespace Upp;

namespace DSP {

// Motion sequencer for creating dynamic parameter changes
class MotionSequencer {
public:
    MotionSequencer();
    
    // Add a step to the sequence for a specific parameter
    void AddStep(const ParameterId& paramId, int step, double value, int duration = 1);
    
    // Set the playback position (0.0 to 1.0)
    void SetPosition(double pos);
    
    // Get the current value for a parameter at the current position
    double GetCurrentValue(const ParameterId& paramId) const;
    
    // Process the sequencer for the current time
    void Process();
    
    // Reset the sequencer
    void Reset();
    
    // Set sequence length in steps
    void SetSequenceLength(int steps);
    
private:
    struct Step {
        int position;
        double value;
        int duration;
        
        Step(int pos, double val, int dur) : position(pos), value(val), duration(dur) {}
    };
    
    struct Sequence {
        ParameterId paramId;
        Vector<Step> steps;
    };
    
    Vector<Sequence> sequences;
    double currentPosition;
    int sequenceLength;
    bool isPlaying;
};

// Scene morphing for smooth transitions between parameter sets
class SceneMorph {
public:
    SceneMorph();
    
    // Set the two scenes to morph between
    void SetScenes(const ParameterSet& scene1, const ParameterSet& scene2);
    
    // Set the morph position (0.0 = scene1, 1.0 = scene2)
    void SetMorphPosition(double pos);
    
    // Get the interpolated parameter set
    ParameterSet GetMorphedParameters() const;
    
    // Process morphing
    void Process();
    
    // Reset to initial state
    void Reset();
    
private:
    ParameterSet scene1, scene2;
    double morphPosition;
};

// Step sequencer for creating rhythmic parameter changes
class StepSequencer {
public:
    StepSequencer();
    
    // Set a step value for a parameter
    void SetStep(const ParameterId& paramId, int step, double value);
    
    // Get the value for a parameter at the specified step
    double GetStepValue(const ParameterId& paramId, int step) const;
    
    // Set the current step
    void SetCurrentStep(int step);
    
    // Advance to the next step
    void NextStep();
    
    // Get the number of steps in the sequence
    int GetNumSteps() const { return numSteps; }
    
    // Set the number of steps in the sequence
    void SetNumSteps(int steps);
    
    // Process the sequencer
    void Process();
    
    // Reset to step 0
    void Reset();
    
private:
    struct ParameterStep {
        ParameterId paramId;
        Vector<double> steps;
    };
    
    Vector<ParameterStep> parameterSteps;
    int currentStep;
    int numSteps;
    bool running;
};

// Module switcher for toggling between different processing modules
class ModuleSwitcher {
public:
    ModuleSwitcher();
    
    // Add a module with a name
    void AddModule(const String& name, ParameterSet& params);
    
    // Switch to a specific module by name
    bool SwitchToModule(const String& name);
    
    // Get the currently active module
    String GetActiveModule() const;
    
    // Get available module names
    Vector<String> GetModuleNames() const;
    
    // Process the active module's parameters
    ParameterSet& GetActiveParameters();
    
    // Reset to first module
    void Reset();
    
private:
    struct Module {
        String name;
        ParameterSet params;
    };
    
    Vector<Module> modules;
    int activeModuleIndex;
};

// Macro controller for controlling multiple parameters with a single control
class MacroController {
public:
    MacroController();
    
    // Add a parameter to this macro with a weight
    void AddParameter(const ParameterId& paramId, double weight = 1.0);
    
    // Set the macro value (0.0 to 1.0)
    void SetValue(double value);
    
    // Get the macro value
    double GetValue() const { return macroValue; }
    
    // Update parameters based on current macro value
    void Process(ParameterSet& params);
    
    // Reset to initial state
    void Reset();
    
private:
    struct MacroParam {
        ParameterId id;
        double weight;
    };
    
    Vector<MacroParam> parameters;
    double macroValue;
};

} // namespace DSP

#endif