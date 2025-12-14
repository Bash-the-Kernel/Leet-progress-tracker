# VS Code Setup Guide

## Required Extensions

Install these VS Code extensions:

1. **C/C++** (Microsoft) - IntelliSense and debugging
2. **CMake Tools** (Microsoft) - CMake integration
3. **Qt tools** (tonka3000) - Qt syntax highlighting

## Setup Steps

### 1. Install Qt6
Download and install Qt6 from https://www.qt.io/download
- Choose Qt 6.5.0 or later
- Select MSVC 2019 64-bit component
- Note the installation path (e.g., `C:\Qt\6.5.0\msvc2019_64`)

### 2. Update Qt Path
Edit `.vscode/settings.json` and update the Qt path:
```json
{
    "cmake.configureArgs": [
        "-DCMAKE_PREFIX_PATH=YOUR_QT_PATH_HERE"
    ]
}
```

### 3. Build in VS Code

#### Option A: Use CMake Tools Extension
1. Open Command Palette (`Ctrl+Shift+P`)
2. Run "CMake: Configure"
3. Run "CMake: Build"

#### Option B: Use Tasks
1. Press `Ctrl+Shift+P`
2. Run "Tasks: Run Task"
3. Select "CMake Build"

#### Option C: Use Terminal
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64"
cmake --build .
```

### 4. Run/Debug
- Press `F5` to debug
- Or run `./build/LeetProgressTracker.exe` from terminal

## Troubleshooting

### Qt Not Found
- Verify Qt installation path in settings.json
- Ensure Qt6 (not Qt5) is installed
- Check that MSVC 2019 64-bit component is selected

### Build Errors
- Install Visual Studio Build Tools or Visual Studio Community
- Ensure C++ development tools are installed
- Try using Developer Command Prompt

### CMake Issues
- Update CMake to 3.20+
- Clear build directory and reconfigure
- Check that all required Qt modules are installed

## Alternative: MinGW Build

If you prefer MinGW over MSVC:

1. Install Qt6 with MinGW component
2. Update settings.json:
```json
{
    "cmake.configureArgs": [
        "-DCMAKE_PREFIX_PATH=C:/Qt/6.5.0/mingw_64",
        "-G", "MinGW Makefiles"
    ]
}
```
3. Ensure MinGW is in your PATH