@echo off
pushd "..\..\"
set currentdir=%cd%
popd
pushd "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\"
call devenv.exe "%currentdir%\LazyEngine.sln"
popd
