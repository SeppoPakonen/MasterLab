#pragma once
#include <AudioCore/AudioCore.h>  // Use main header instead
namespace am {
struct Effect {
    virtual ~Effect() {}
    virtual void Prepare(SampleRate sr, int maxBlock) {}
    virtual void Process(AudioBuffer& io) = 0;
    virtual String Name() const = 0;
};
}