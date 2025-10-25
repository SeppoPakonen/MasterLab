#pragma once
#include "MultiChannelLayout.h"
namespace am {
enum class PortDir { In, Out };
struct Port {
    String name;
    PortDir dir = PortDir::In;
    MultiChannelLayout layout;
};
}