@echo off
set "ROOT=%~dp0"

cd /d "%ROOT%"

rmdir /s /q ..\bin
del ..\src\frontend\lexical-analysis\flex-scanner.c
del ..\src\frontend\syntactic-analysis\bison-parser.c
del ..\src\frontend\syntactic-analysis\bison-parser.h

echo All clean.
