@echo off
echo ===============================================
echo    Windows Helper - Build Script
echo ===============================================
echo.

REM Controlla se MinGW è installato
where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERRORE: MinGW-w64 non trovato!
    echo.
    echo Per installare MinGW-w64:
    echo 1. Vai su https://www.mingw-w64.org/downloads/
    echo 2. Scarica e installa MSYS2 o MinGW-w64
    echo 3. Aggiungi la cartella bin al PATH di sistema
    echo.
    echo Alternativamente, puoi usare Visual Studio con MSVC:
    echo 1. Installa Visual Studio Community (gratuito)
    echo 2. Includi "Desktop development with C++"
    echo 3. Usa il Developer Command Prompt per compilare
    echo.
    pause
    exit /b 1
)

echo MinGW-w64 trovato! Procedo con la compilazione...
echo.

REM Crea la directory obj se non esiste
if not exist "obj" mkdir "obj"

echo Compilazione di main.cpp...
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/main.cpp -o obj/main.o

if %ERRORLEVEL% NEQ 0 (
    echo ERRORE durante la compilazione!
    pause
    exit /b 1
)

echo Linking dell'eseguibile...
g++ obj/main.o -o WindowsHelper.exe -lgdi32 -luser32 -lkernel32

if %ERRORLEVEL% NEQ 0 (
    echo ERRORE durante il linking!
    pause
    exit /b 1
)

echo.
echo ===============================================
echo    COMPILAZIONE COMPLETATA CON SUCCESSO!
echo ===============================================
echo.
echo Eseguibile creato: WindowsHelper.exe
echo.
echo Per eseguire l'applicazione:
echo    .\WindowsHelper.exe
echo.
pause
