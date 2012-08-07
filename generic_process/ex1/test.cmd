@echo off
setlocal

set CXX=cl.exe /EHsc /nologo /Fea.exe
set CONTAINERS=Array Deque List
set ALGORITHMS=Find GetAt Transform

for %%i in (%CONTAINERS%) do for %%j in (%ALGORITHMS%) do call :TEST %%i %%j

endlocal
goto :eof 

:TEST
%CXX% %1\%2\*.cpp 2>&1 >nul
echo Testing %1 %2 ...
.\a.exe
if %ERRORLEVEL% EQU 0 goto :eof
echo ***FAILED!
goto :eof
