@echo off
echo Building LeetCode Progress Tracker...

REM Create build directory
if not exist build mkdir build
cd build

REM Clear previous CMake cache
if exist CMakeCache.txt del CMakeCache.txt
if exist CMakeFiles rmdir /s /q CMakeFiles

REM Add MinGW to PATH
set PATH=C:\Qt\Tools\mingw1310_64\bin;%PATH%

REM Configure with CMake (adjust Qt path as needed)
echo Configuring with CMake...
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64"

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