#ifndef _AudioGraph_Port_h_
#define _AudioGraph_Port_h_

// Note: Requires MultiChannelLayout.h (from same package) - available via main header in .cpp files

namespace am {
	
enum class PortDir { In, Out };
struct Port {
    String name;
    PortDir dir = PortDir::In;
    MultiChannelLayout layout;
};

}

#endif
