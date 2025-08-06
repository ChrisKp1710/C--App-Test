#include "Common.h"
#include "Window.h"
#include "Layout.h"

// Definizione delle variabili globali
HINSTANCE hInst;
HWND hMainWindow;
HWND hSidebarLeft;
HWND hEditorMain;
HWND hPanelRight;
HWND hStatusBar;
HFONT hFontUI;
HFONT hFontEditor;

// Punto di ingresso dell'applicazione
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Evita warning per parametri non usati
    (void)hPrevInstance;
    (void)lpCmdLine;
    
    hInst = hInstance;

    // Inizializza la finestra principale
    if (!Window::Initialize(hInstance))
    {
        MessageBox(NULL, "Errore nell'inizializzazione di DevNotes!", "Errore", MB_OK | MB_ICONERROR);
        return -1;
    }

    // Mostra la finestra
    Window::Show(nCmdShow);

    // Loop dei messaggi
    return Window::MessageLoop();
}
