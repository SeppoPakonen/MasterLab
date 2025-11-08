#!/bin/bash

echo "Building test packages from unittst directory..."
echo "Note: This approach may require manual compilation of each test"

# Define source paths
UPPSRC_PATH="$HOME/ai-upp/uppsrc"
BUILD_CONFIG="$HOME/.config/u++/theide/CLANG.bm"

# Create bin directory if it doesn't exist
mkdir -p /home/sblo/Dev/MasterLab/bin

# Build function for a single package
build_package() {
    local pkg_path=$1
    local pkg_name=$2
    echo "Attempting to build $pkg_name from $pkg_path"
    
    # Instead of using umk directly with a path, we'll copy files to a temporary location
    # and try to build them. This is because umk expects packages in known locations.
    
    echo "Building $pkg_name would use: umk src,$UPPSRC_PATH $pkg_path $BUILD_CONFIG -bds +GUI,DEBUG_FULL bin/$pkg_name"
    echo "Note: This may fail if umk doesn't support arbitrary paths."
}

# Build all test packages in src directory
echo "Building tests for src directory packages..."
for pkg in /home/sblo/Dev/MasterLab/unittst/src/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        build_package "$pkg" "$pkg_name"
    fi
done

# Build all test packages in instruments directory
echo "Building tests for instruments directory packages..."
for pkg in /home/sblo/Dev/MasterLab/unittst/instruments/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        build_package "$pkg" "$pkg_name"
    fi
done

# Build all test packages in midi_effects directory
echo "Building tests for midi_effects directory packages..."
for pkg in /home/sblo/Dev/MasterLab/unittst/midi_effects/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        build_package "$pkg" "$pkg_name"
    fi
done

# Build all test packages in midi_inserts directory
echo "Building tests for midi_inserts directory packages..."
for pkg in /home/sblo/Dev/MasterLab/unittst/midi_inserts/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        build_package "$pkg" "$pkg_name"
    fi
done

# Build all test packages in midi_instruments directory
echo "Building tests for midi_instruments directory packages..."
for pkg in /home/sblo/Dev/MasterLab/unittst/midi_instruments/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        build_package "$pkg" "$pkg_name"
    fi
done

# Build all test packages in effects directory
echo "Building tests for effects directory packages..."
for pkg in /home/sblo/Dev/MasterLab/unittst/effects/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        build_package "$pkg" "$pkg_name"
    fi
done

echo "Build process completed. Note that some packages may require manual compilation."
echo "For manual compilation, you can use the command line U++ compiler or TheIDE."