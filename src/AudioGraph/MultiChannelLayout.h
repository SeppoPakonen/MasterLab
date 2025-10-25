#pragma once
#include "../AudioCore/AudioTypes.h"
namespace am {
struct MultiChannelLayout {
    ChannelSet channels; // which channels traverse a link
};
}