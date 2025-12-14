# Build Instructions

## Prerequisites

### Windows
- Visual Studio 2019 or later (with C++ support)
- Qt6 (6.2 or later) - Download from https://www.qt.io/download
- CMake 3.20 or later

### macOS
- Xcode Command Line Tools
- Qt6 (6.2 or later) - Install via Homebrew: `brew install qt6`
- CMake 3.20 or later - Install via Homebrew: `cmake install cmake`

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev libqt6sql6-sqlite
```

## Building the Application

### 1. Clone the Repository
```bash
git clone <repository-url>
cd Leet-progress-tracker
```

### 2. Create Build Directory
```bash
mkdir build
cd build
```

### 3. Configure with CMake

#### Windows (Visual Studio)
```cmd
cmake .. -G "Visual Studio 16 2019" -DCMAKE_PREFIX_PATH="C:\Qt\6.5.0\msvc2019_64"
```

#### macOS
```bash
cmake .. -DCMAKE_PREFIX_PATH="/usr/local/opt/qt6"
```

#### Linux
```bash
cmake .. -DCMAKE_PREFIX_PATH="/usr/lib/x86_64-linux-gnu/qt6"
```

### 4. Build the Application

#### Windows
```cmd
cmake --build . --config Release
```

#### macOS/Linux
```bash
make -j$(nproc)
```

## Running the Application

### Windows
```cmd
.\Release\LeetProgressTracker.exe
```

### macOS/Linux
```bash
./LeetProgressTracker
```

## Troubleshooting

### Qt6 Not Found
- Ensure Qt6 is properly installed
- Set CMAKE_PREFIX_PATH to your Qt6 installation directory
- On Windows, make sure to use the correct MSVC version

### SQLite Issues
- The application uses Qt6's built-in SQLite support
- No additional SQLite installation required

### Missing Dependencies
- Ensure all Qt6 modules are installed (Core, Widgets, Sql)
- On Linux, install qt6-base-dev and related packages

## Development Setup

### IDE Configuration
- **Visual Studio Code**: Install C++ and CMake extensions
- **Qt Creator**: Open CMakeLists.txt directly
- **Visual Studio**: Use "Open Folder" with the project root

### Debug Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

## Packaging

### Windows
Use Qt's windeployqt tool:
```cmd
windeployqt.exe --qmldir . LeetProgressTracker.exe
```

### macOS
Use Qt's macdeployqt tool:
```bash
macdeployqt LeetProgressTracker.app
```

### Linux
Create an AppImage or use system package managers.