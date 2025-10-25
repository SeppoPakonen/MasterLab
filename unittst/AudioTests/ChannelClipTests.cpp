#include <Core/Core.h>
#include "../src/AudioCore/Channel.h"
#include "../src/AudioCore/Clip.h"
#include "../src/AudioCore/AudioTypes.h"

CONSOLE_APP_MAIN {
    using namespace Upp;
    using namespace am;
    
    Channel channel;
    
    // Add some clips to the channel
    Clip clip1;
    clip1.filepath = "test1.wav";
    clip1.start_frame = 0;
    clip1.length_frames = 48000; // 1 second at 48kHz
    clip1.meta.name = "Test Clip 1";
    channel.clips.Add(clip1);
    
    Clip clip2;
    clip2.filepath = "test2.wav";
    clip2.start_frame = 48000;  // Starts after clip1
    clip2.length_frames = 24000; // 0.5 seconds
    clip2.meta.name = "Test Clip 2";
    channel.clips.Add(clip2);
    
    // Verify we have 2 clips
    RLOG("Number of clips in channel: " << channel.clips.GetCount());
    
    LOG("Channel clip test completed successfully");
}