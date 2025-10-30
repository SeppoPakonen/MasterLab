// Helper to make types compatible with U++ containers
// Add this include to files with custom types that need to be U++ compatible

#include <Core/Core.h>

// Macro to make a struct/class compatible with U++ containers
#define UPP_COMPATIBLE_TYPE(type) \
    template<> \
    struct Upp::IsContainerDeepCopyFeature<type> { \
        typedef Upp::Feature<1> type; \
    };

// Alternative approach - define the trait directly in the namespace
#define DECLARE_UPP_COMPATIBLE(type) \
    namespace Upp { \
        template<> \
        struct IsContainerDeepCopyFeature<type> { \
            typedef Upp::Feature<1> value; \
        }; \
    }