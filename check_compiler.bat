@echo off
echo ===============================================
echo    VERIFICA INSTALLAZIONE COMPILATORE
echo ===============================================
echo.

echo Verifico se MinGW-w64 è installato...
echo.

where gcc >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] GCC trovato!
    gcc --version
    echo.
) else (
    echo [ERRORE] GCC non trovato nel PATH
)

where g++ >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] G++ trovato!
    g++ --version
    echo.
) else (
    echo [ERRORE] G++ non trovato nel PATH
)

where mingw32-make >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] MinGW Make trovato!
    mingw32-make --version
    echo.
) else (
    echo [ERRORE] MinGW Make non trovato nel PATH
)

echo ===============================================
echo    INSTALLAZIONE RAPIDA MINGW-w64
echo ===============================================
echo.
echo Per installare MinGW-w64 rapidamente:
echo.
echo 1. Scarica MSYS2 da: https://www.msys2.org/
echo 2. Installa ed esegui questi comandi nel terminale MSYS2:
echo.
echo    pacman -Syu
echo    pacman -S mingw-w64-x86_64-toolchain
echo    pacman -S mingw-w64-x86_64-make
echo.
echo 3. Aggiungi al PATH di Windows:
echo    C:\msys64\mingw64\bin
echo    C:\msys64\usr\bin
echo.
echo 4. Riavvia VS Code
echo.
echo ===============================================
echo.
pause
