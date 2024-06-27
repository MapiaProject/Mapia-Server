@echo off

@rem build libraries
IF NOT EXIST "..\lib\bin\Debug\SQLiteCpp.lib" (
    call :build Debug
    call :build Release
)
EXIT /B %ERRORLEVEL%

:build
cd Common\Library\SQLiteCpp
cmake .
cmake --build . --target sqlite3 --config %~1
cmake --build . --target SQLiteCpp --config %~1

cd ..\..\..\
for /r .\Common\Library\SQLiteCpp %%i in (*.lib) do (
    copy "%%i" "..\lib\bin\%~1\"
    del "%%i"
)
EXIT /B 0