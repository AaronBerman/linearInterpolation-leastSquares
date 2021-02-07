
@echo off
SETLOCAL

CALL "%~dp0lib\CPUTemps.exe" %*
EXIT /B %ERRORLEVEL%
ENDLOCAL
