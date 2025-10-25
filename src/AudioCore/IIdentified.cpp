#include "IIdentified.h"
namespace am {
IIdentified::IIdentified() {
    id = Upp::String().Cat() << Upp::GetTickCount();
}
}