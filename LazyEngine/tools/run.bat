@echo off
mkdir "..\build"
pushd "..\build\"
cl -Zi "..\MainFunctions\Win32Main.cpp" user32.lib gdi32.lib
popd
