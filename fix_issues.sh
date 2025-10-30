#!/bin/bash

# Fix Relocate function calls with missing third argument
find /common/active/sblo/Dev/MasterLab/src/ -name "*.cpp" -exec sed -i 's/Relocate(dst++, src++);/Relocate(dst++, src++, 1);/g' {} \;

# Fix Vector template issues
find /common/active/sblo/Dev/MasterLab/src/ -name "*.h" -exec sed -i 's/Vector</Upp::Vector</g' {} \;
find /common/active/sblo/Dev/MasterLab/src/ -name "*.cpp" -exec sed -i 's/Vector</Upp::Vector</g' {} \;

# Fix String type issues
find /common/active/sblo/Dev/MasterLab/src/ -name "*.h" -exec sed -i 's/String/Upp::String/g' {} \;
find /common/active/sblo/Dev/MasterLab/src/ -name "*.cpp" -exec sed -i 's/String/Upp::String/g' {} \;

# Fix AKImg namespace issues
sed -i 's/AKImg::plus/K_PLUS/g' /common/active/sblo/Dev/MasterLab/src/Preferences/KeyCommandsDlg.cpp
sed -i 's/AKImg::minus/K_MINUS/g' /common/active/sblo/Dev/MasterLab/src/Preferences/KeyCommandsDlg.cpp
sed -i 's/AKImg::magnifying_glass/K_MAGNIFYING_GLASS/g' /common/active/sblo/Dev/MasterLab/src/Preferences/KeyCommandsDlg.cpp
sed -i 's/AKImg::trashbin/K_TRASHBIN/g' /common/active/sblo/Dev/MasterLab/src/Preferences/KeyCommandsDlg.cpp

# Fix FindIndex method calls
find /common/active/sblo/Dev/MasterLab/src/ -name "*.cpp" -exec sed -i 's/\.FindIndex(/\.Find(/g' {} \;

# Fix GetHomeDirFile calls
sed -i 's/GetHomeDirFile()/GetHomeDirFile("")/g' /common/active/sblo/Dev/MasterLab/src/Devices/PluginManager.cpp

echo "All automated fixes applied."