@echo off
IF EXIST ".\datasheet.db" del .\datasheet.db
mysql2sqlite -f datasheet.db -d datadb -u root -p