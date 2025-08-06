@echo off
REM DevNotes Quick Build per MSYS2 Qt6
echo 🏗️  DevNotes Quick Build (MSYS2)
echo ===============================

REM Verifica MSYS2 Qt6
if not exist "C:\msys64\mingw64\bin\qmake6.exe" (
    echo ❌ MSYS2 Qt6 non trovato
    echo Installa con: pacman -S mingw-w64-x86_64-qt6-base mingw-w64-x86_64-qt6-declarative mingw-w64-x86_64-qt6-tools
    pause
    exit /b 1
)

echo 📍 MSYS2 Qt6 Path: C:\msys64\mingw64

REM Aggiorna PATH
set PATH=C:\msys64\mingw64\bin;%PATH%

REM Pulizia rapida
echo 🧹 Pulizia...
if exist obj rmdir /s /q obj
if exist DevNotes.exe del DevNotes.exe
if exist Makefile del Makefile

REM Build
echo ⚙️  qmake6...
qmake6 DevNotes.pro CONFIG+=release
if errorlevel 1 goto error

echo 🔨 Compilazione...
mingw32-make -j4
if errorlevel 1 goto error

echo ✅ Build completata!
if exist DevNotes.exe (
    echo 🚀 Avvio DevNotes...
    start DevNotes.exe
) else (
    echo ❌ Eseguibile non trovato
)
goto end

:error
echo ❌ Errore durante il build
pause

:end
