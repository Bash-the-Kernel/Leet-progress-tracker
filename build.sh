#!/bin/bash

echo "Building LeetCode Progress Tracker..."

# Create build directory
mkdir -p build
cd build

# Detect OS and set Qt path
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    QT_PATH="/usr/local/opt/qt6"
    if [ ! -d "$QT_PATH" ]; then
        QT_PATH="/opt/homebrew/opt/qt6"  # Apple Silicon
    fi
else
    # Linux
    QT_PATH="/usr/lib/x86_64-linux-gnu/qt6"
    if [ ! -d "$QT_PATH" ]; then
        QT_PATH="/usr/lib/qt6"  # Alternative path
    fi
fi

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_PREFIX_PATH="$QT_PATH" -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    echo "Please check that Qt6 is installed."
    echo "On macOS: brew install qt6"
    echo "On Ubuntu/Debian: sudo apt install qt6-base-dev qt6-tools-dev libqt6sql6-sqlite"
    exit 1
fi

# Build the project
echo "Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build completed successfully!"
echo "Executable location: build/LeetProgressTracker"

# Make executable
chmod +x LeetProgressTracker