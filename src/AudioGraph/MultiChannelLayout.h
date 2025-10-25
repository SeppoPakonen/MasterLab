#ifndef _AudioGraph_MultiChannelLayout_h_
#define _AudioGraph_MultiChannelLayout_h_

// Note: Requires AudioCore/AudioCore.h - included via main header in .cpp files

namespace am {
struct MultiChannelLayout {
    ChannelSet channels; // which channels traverse a link
};
}

#endif
namespace am {
struct MultiChannelLayout {
    ChannelSet channels; // which channels traverse a link
};
}