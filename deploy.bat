@echo off
echo Deploying LeetCode Progress Tracker...

cd build

REM Deploy Qt libraries
C:\Qt\6.10.1\mingw_64\bin\windeployqt.exe LeetProgressTracker.exe

echo Deployment complete!
echo You can now run LeetProgressTracker.exe
pause