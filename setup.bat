@rem export to sqlite3 from MySQL
@rem mysql2sqlite -f Common/Database/datasheet.db -d datadb -u root -p
@rem @echo off

IF NOT EXIST ".\Common\Database\datasheet.db" del .\Common\Database\datasheet.db
mysql2sqlite -f .\Common\Database\datasheet.db -d datadb -u root -p

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