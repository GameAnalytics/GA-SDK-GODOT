#!/bin/bash

# ============================================================================
# iOS Build Script for GameAnalytics Godot SDK
# ============================================================================
# This script builds the GameAnalytics GDExtension for iOS devices only
# and packages them into xcframeworks.
#
# Usage:
#   ./build_ios.sh <target> [additional_scons_args]
#
# Arguments:
#   target: Build target - either "template_debug" or "template_release"
#   additional_scons_args: Optional additional SCons arguments
#
# Examples:
#   ./build_ios.sh template_debug
#   ./build_ios.sh template_release arch=arm64
#
# Output:
#   - bin/ios/libGodotGameAnalytics.ios.<target>.xcframework
#   - bin/ios/libgodot-cpp.ios.<target>.xcframework
#   - Copies frameworks to example/addons/GameAnalytics/ directories
# ============================================================================

set -e  # Exit on error

# Validate arguments
if [ -z "$1" ]; then
    echo "Error: Build target not specified"
    echo "Usage: $0 <template_debug|template_release> [additional_scons_args]"
    exit 1
fi

TARGET=$1
EXTRA_ARGS=$2

echo "============================================================================"
echo "Building GameAnalytics iOS SDK - Target: $TARGET"
echo "============================================================================"

# ============================================================================
# Step 1: Build godot-cpp for iOS
# ============================================================================
echo ""
echo "Step 1: Building godot-cpp for iOS device..."
cd godot-cpp
scons platform=ios target=$TARGET disable_exceptions=false $EXTRA_ARGS
cd ..

# ============================================================================
# Step 2: Build GameAnalytics SDK for iOS
# ============================================================================
echo ""
echo "Step 2: Building GameAnalytics SDK for iOS device..."
scons platform=ios target=$TARGET disable_exceptions=false $EXTRA_ARGS

# ============================================================================
# Step 3: Create xcframeworks
# ============================================================================
echo ""
echo "Step 3: Creating xcframeworks..."

# Create bin/ios directory if it doesn't exist
mkdir -p bin/ios

# Remove old xcframeworks if they exist
rm -rf bin/ios/libGodotGameAnalytics.ios.$TARGET.xcframework
rm -rf bin/ios/libgodot-cpp.ios.$TARGET.xcframework

# Create GameAnalytics xcframework from device build only
echo "Creating libGodotGameAnalytics.ios.$TARGET.xcframework..."
xcodebuild -create-xcframework \
    -library lib/libgameanalytics.ios.$TARGET.a \
    -output bin/ios/libGodotGameAnalytics.ios.$TARGET.xcframework

# Create godot-cpp xcframework from device build only
echo "Creating libgodot-cpp.ios.$TARGET.xcframework..."
xcodebuild -create-xcframework \
    -library godot-cpp/bin/libgodot-cpp.ios.$TARGET.arm64.a \
    -output bin/ios/libgodot-cpp.ios.$TARGET.xcframework

# ============================================================================
# Step 4: Copy frameworks to example project
# ============================================================================
echo ""
echo "Step 4: Copying frameworks to example project..."

# Create example directories if they don't exist
mkdir -p example/addons/GameAnalytics/bin/ios
mkdir -p example/addons/GameAnalytics/lib/ios

# Copy the built frameworks to example/addons/GameAnalytics/bin/ios/
echo "Copying to example/addons/GameAnalytics/bin/ios/..."
rm -rf example/addons/GameAnalytics/bin/ios/libGodotGameAnalytics.ios.$TARGET.xcframework
cp -r bin/ios/libGodotGameAnalytics.ios.$TARGET.xcframework example/addons/GameAnalytics/bin/ios/

# Copy godot-cpp framework to example/addons/GameAnalytics/lib/ios/ (dependency)
echo "Copying to example/addons/GameAnalytics/lib/ios/..."
rm -rf example/addons/GameAnalytics/lib/ios/libgodot-cpp.ios.$TARGET.xcframework
cp -r bin/ios/libgodot-cpp.ios.$TARGET.xcframework example/addons/GameAnalytics/lib/ios/

# Copy GameAnalytics iOS SDK framework (dependency) if not already present
if [ ! -d "example/addons/GameAnalytics/lib/ios/GameAnalytics.xcframework" ]; then
    echo "Copying GameAnalytics iOS SDK framework..."
    cp -r src/libs/iOS/GameAnalytics.xcframework example/addons/GameAnalytics/lib/ios/
fi

# ============================================================================
# Complete
# ============================================================================
echo ""
echo "============================================================================"
echo "iOS Build Complete!"
echo "============================================================================"
echo "Built frameworks:"
echo "  - bin/ios/libGodotGameAnalytics.ios.$TARGET.xcframework"
echo "  - bin/ios/libgodot-cpp.ios.$TARGET.xcframework"
echo ""
echo "Copied to example project:"
echo "  - example/addons/GameAnalytics/bin/ios/"
echo "  - example/addons/GameAnalytics/lib/ios/"
echo "============================================================================"
