@echo off
echo Building DevNotes with hot reload...
mingw32-make
if %ERRORLEVEL% NEQ 0 (
    echo Building alternative version...
    g++ obj/main_new.o obj/Window.o obj/Layout.o obj/ModernUI.o -o DevNotes_new.exe -lgdi32 -luser32 -lkernel32 -lcomctl32 -luxtheme
    if %ERRORLEVEL% EQU 0 (
        echo New version ready! Press Ctrl+R in DevNotes to reload.
    )
) else (
    echo Build complete!
)
