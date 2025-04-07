@echo off
echo Cleaning build directory...
if exist build (
    rmdir /s /q build
)

echo Creating build directory...
mkdir build

echo Entering build directory...
cd /d build

echo Configuring project...
cmake .. -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=d:\program\Qt\Qt5.12.9\Tools\mingw730_64\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=d:\program\Qt\Qt5.12.9\Tools\mingw730_64\bin\g++.exe --no-warn-unused-cli -SF:/code/projects/29_QT_projects/custom_widget -Bf:/code/projects/29_QT_projects/custom_widget/build -G Ninja

echo Building project...
ninja -j4

if %ERRORLEVEL% neq 0 (
    echo Build failed.
    pause
    exit /b %ERRORLEVEL%
)

echo Build complete.
cd ..

echo Running custom_widget.exe...
start "" "F:\code\projects\29_QT_projects\custom_widget\build\custom_widget.exe"

pause