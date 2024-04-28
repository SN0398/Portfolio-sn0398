@echo off
mkdir Build
xcopy /E /I /Y /Q Assets Build\Assets
copy /Y x64\Release\DxLib_SolutionTemplate.exe Build\Build.exe