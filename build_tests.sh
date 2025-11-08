#!/bin/bash

echo "Building all test packages in upptst directory..."

# Define source paths
UPPSRC_PATH="$HOME/ai-upp/uppsrc"
BUILD_CONFIG="$HOME/.config/u++/theide/CLANG.bm"

# Create bin directory if it doesn't exist
mkdir -p /home/sblo/Dev/MasterLab/bin

# Build all test packages in src directory
echo "Building tests for src directory..."
for pkg in /home/sblo/Dev/MasterLab/upptst/src/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        echo "Building $pkg_name..."
        umk "src,$UPPSRC_PATH" "$pkg" "$BUILD_CONFIG" -bds +GUI,DEBUG_FULL "bin/$pkg_name"
        if [ $? -eq 0 ]; then
            echo "Successfully built $pkg_name"
        else
            echo "Failed to build $pkg_name"
        fi
    fi
done

# Build all test packages in instruments directory
echo "Building tests for instruments directory..."
for pkg in /home/sblo/Dev/MasterLab/upptst/instruments/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        echo "Building $pkg_name..."
        umk "src,$UPPSRC_PATH" "$pkg" "$BUILD_CONFIG" -bds +GUI,DEBUG_FULL "bin/$pkg_name"
        if [ $? -eq 0 ]; then
            echo "Successfully built $pkg_name"
        else
            echo "Failed to build $pkg_name"
        fi
    fi
done

# Build all test packages in midi_effects directory
echo "Building tests for midi_effects directory..."
for pkg in /home/sblo/Dev/MasterLab/upptst/midi_effects/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        echo "Building $pkg_name..."
        umk "src,$UPPSRC_PATH" "$pkg" "$BUILD_CONFIG" -bds +GUI,DEBUG_FULL "bin/$pkg_name"
        if [ $? -eq 0 ]; then
            echo "Successfully built $pkg_name"
        else
            echo "Failed to build $pkg_name"
        fi
    fi
done

# Build all test packages in midi_inserts directory
echo "Building tests for midi_inserts directory..."
for pkg in /home/sblo/Dev/MasterLab/upptst/midi_inserts/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        echo "Building $pkg_name..."
        umk "src,$UPPSRC_PATH" "$pkg" "$BUILD_CONFIG" -bds +GUI,DEBUG_FULL "bin/$pkg_name"
        if [ $? -eq 0 ]; then
            echo "Successfully built $pkg_name"
        else
            echo "Failed to build $pkg_name"
        fi
    fi
done

# Build all test packages in midi_instruments directory
echo "Building tests for midi_instruments directory..."
for pkg in /home/sblo/Dev/MasterLab/upptst/midi_instruments/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        echo "Building $pkg_name..."
        umk "src,$UPPSRC_PATH" "$pkg" "$BUILD_CONFIG" -bds +GUI,DEBUG_FULL "bin/$pkg_name"
        if [ $? -eq 0 ]; then
            echo "Successfully built $pkg_name"
        else
            echo "Failed to build $pkg_name"
        fi
    fi
done

# Build all test packages in effects directory
echo "Building tests for effects directory..."
for pkg in /home/sblo/Dev/MasterLab/upptst/effects/*.upp; do
    if [ -f "$pkg" ]; then
        pkg_name=$(basename "$pkg" .upp)
        echo "Building $pkg_name..."
        umk "src,$UPPSRC_PATH" "$pkg" "$BUILD_CONFIG" -bds +GUI,DEBUG_FULL "bin/$pkg_name"
        if [ $? -eq 0 ]; then
            echo "Successfully built $pkg_name"
        else
            echo "Failed to build $pkg_name"
        fi
    fi
done

echo "Build process completed for all test packages."