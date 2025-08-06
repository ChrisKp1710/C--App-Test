@echo off
echo ===============================================
echo    Pulizia File di Build
echo ===============================================
echo.

if exist "obj" (
    echo Rimozione directory obj...
    rmdir /s /q "obj"
)

if exist "WindowsHelper.exe" (
    echo Rimozione eseguibile...
    del "WindowsHelper.exe"
)

echo.
echo Pulizia completata!
echo.
pause
