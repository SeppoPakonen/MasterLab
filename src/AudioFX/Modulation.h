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
    void AddStep(const AudioFX::ParameterId& paramId, int step, double value, int duration = 1);

    // Set the playback position (0.0 to 1.0)
    void SetPosition(double pos);

    // Get the current value for a parameter at the current position
    double GetCurrentValue(const AudioFX::ParameterId& paramId) const;

    // Process the sequencer for the current time
    void Process();

    // Reset the sequencer
    void Reset();

    // Set sequence length in steps
    void SetSequenceLength(int steps);

private:
    struct Step : Moveable<Step> {
        int position;
        double value;
        int duration;

        Step() : position(0), value(0.0), duration(1) {}  // Added default constructor
        Step(int pos, double val, int dur) : position(pos), value(val), duration(dur) {}
        
        // Support for U++ container operations
        void  operator<<=(const Step& s) { position = s.position; value = s.value; duration = s.duration; }
        bool  operator==(const Step& b) const { return position == b.position && value == b.value && duration == b.duration; }
        bool  operator!=(const Step& b) const { return !(*this == b); }
        int   Compare(const Step& b) const { return position - b.position; }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(Step& s) { *this = pick(s); }
    };

    struct Sequence : Moveable<Sequence> {
        AudioFX::ParameterId paramId;
        Vector<Step> steps;
        
        Sequence() {}
        Sequence(const AudioFX::ParameterId& id) : paramId(id) {}
        
        // Support for U++ container operations
        void  operator<<=(const Sequence& s) { paramId = s.paramId; steps <<= s.steps; }
        bool  operator==(const Sequence& b) const { return paramId == b.paramId && steps == b.steps; }
        bool  operator!=(const Sequence& b) const { return !(*this == b); }
        int   Compare(const Sequence& b) const { return paramId.Compare(b.paramId); }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(Sequence& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("paramId", paramId)("steps", steps);
        }
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
    void SetScenes(const AudioFX::ParameterSet& scene1, const AudioFX::ParameterSet& scene2);

    // Set the morph position (0.0 = scene1, 1.0 = scene2)
    void SetMorphPosition(double pos);

    // Get the interpolated parameter set
    AudioFX::ParameterSet GetMorphedParameters() const;

    // Process morphing
    void Process();

    // Reset to initial state
    void Reset();

private:
    AudioFX::ParameterSet scene1, scene2;
    double morphPosition;
};

// Step sequencer for creating rhythmic parameter changes
class StepSequencer {
public:
    StepSequencer();

    // Set a step value for a parameter
    void SetStep(const AudioFX::ParameterId& paramId, int step, double value);

    // Get the value for a parameter at the specified step
    double GetStepValue(const AudioFX::ParameterId& paramId, int step) const;

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
    struct ParameterStep : Moveable<ParameterStep> {
        AudioFX::ParameterId paramId;
        Vector<double> steps;
        
        ParameterStep() {}
        ParameterStep(const AudioFX::ParameterId& id) : paramId(id) {}
        
        // Support for U++ container operations
        void  operator<<=(const ParameterStep& s) { paramId = s.paramId; steps <<= s.steps; }
        bool  operator==(const ParameterStep& b) const { return paramId == b.paramId && steps == b.steps; }
        bool  operator!=(const ParameterStep& b) const { return !(*this == b); }
        int   Compare(const ParameterStep& b) const { return paramId.Compare(b.paramId); }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(ParameterStep& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("paramId", paramId)("steps", steps);
        }
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
    void AddModule(const String& name, AudioFX::ParameterSet& params);

    // Switch to a specific module by name
    bool SwitchToModule(const String& name);

    // Get the currently active module
    String GetActiveModule() const;

    // Get available module names
    Vector<String> GetModuleNames() const;

    // Process the active module's parameters
    AudioFX::ParameterSet& GetActiveParameters();

    // Reset to first module
    void Reset();

private:
    struct Module : Moveable<Module> {
        String name;
        AudioFX::ParameterSet params;
        
        Module() {}
        Module(const String& n) : name(n) {}
        
        // Support for U++ container operations
        void  operator<<=(const Module& s) { name = s.name; }
        bool  operator==(const Module& b) const { return name == b.name; }
        bool  operator!=(const Module& b) const { return !(*this == b); }
        int   Compare(const Module& b) const { return name.Compare(b.name); }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(Module& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("name", name);
        }
    };

    Vector<Module> modules;
    int activeModuleIndex;
};

// Macro controller for controlling multiple parameters with a single control
class MacroController {
public:
    MacroController();

    // Add a parameter to this macro with a weight
    void AddParameter(const AudioFX::ParameterId& paramId, double weight = 1.0);

    // Set the macro value (0.0 to 1.0)
    void SetValue(double value);

    // Get the macro value
    double GetValue() const { return macroValue; }

    // Update parameters based on current macro value
    void Process(AudioFX::ParameterSet& params);

    // Reset to initial state
    void Reset();

private:
    struct MacroParam : Moveable<MacroParam> {
        AudioFX::ParameterId id;
        double weight;
        
        MacroParam() : weight(1.0) {}
        MacroParam(const AudioFX::ParameterId& i, double w) : id(i), weight(w) {}
        
        // Support for U++ container operations
        void  operator<<=(const MacroParam& s) { id = s.id; weight = s.weight; }
        bool  operator==(const MacroParam& b) const { return id == b.id && weight == b.weight; }
        bool  operator!=(const MacroParam& b) const { return !(*this == b); }
        int   Compare(const MacroParam& b) const { return id.Compare(b.id); }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(MacroParam& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("id", id)("weight", weight);
        }
    };

    Vector<MacroParam> parameters;
    double macroValue;
};

} // namespace DSP

#endif

