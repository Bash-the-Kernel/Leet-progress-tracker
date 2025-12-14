@echo off
echo Building LeetCode Progress Tracker...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake (adjust Qt path as needed)
echo Configuring with CMake...
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.5.0\msvc2019_64"

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    echo Please check that Qt6 is installed and CMAKE_PREFIX_PATH is correct.
    pause
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build .

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo Executable location: build\LeetProgressTracker.exe
pause