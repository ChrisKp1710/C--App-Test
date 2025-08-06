#include "Window.h"
#include "Layout.h"
#include "ModernUI.h"

const char* Window::CLASS_NAME = "DevNotesApp";

bool Window::Initialize(HINSTANCE hInstance)
{
    // Registra la classe della finestra
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(25, 26, 28)); // Dark theme moderno come ModernUI
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpszMenuName = NULL;

    if (!RegisterClass(&wc))
    {
        return false;
    }

    // Crea la finestra principale - DevNotes
    hMainWindow = CreateWindowEx(
        0,                              // Stili estesi
        CLASS_NAME,                     // Nome classe
        "DevNotes - Knowledge Management",  // Titolo finestra
        WS_OVERLAPPEDWINDOW,            // Stile finestra
        CW_USEDEFAULT, CW_USEDEFAULT,   // Posizione
        1200, 800,                      // Dimensioni per layout moderno
        NULL,                           // Finestra padre
        NULL,                           // Menu
        hInstance,                      // Istanza
        NULL                            // Parametri aggiuntivi
    );

    return (hMainWindow != NULL);
}

void Window::Show(int nCmdShow)
{
    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);
}

int Window::MessageLoop()
{
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        Layout::CreateModernFonts();
        Layout::CreateDevNotesLayout(hwnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_MENU_NEW_NOTE:
            MessageBox(hwnd, "Nuova nota - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_MENU_OPEN_NOTE:
            MessageBox(hwnd, "Apri nota - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
            break;
        }
        break;

    case WM_KEYDOWN:
        // Controlla se Ctrl è premuto
        if (GetKeyState(VK_CONTROL) & 0x8000)
        {
            switch (wParam)
            {
            case 'R':
                // Ctrl+R = Hot Reload (riavvia con nuova versione)
                {
                    // Controlla se esiste una nuova versione
                    if (GetFileAttributes("DevNotes_new.exe") != INVALID_FILE_ATTRIBUTES)
                    {
                        // Avvia la nuova versione
                        ShellExecute(NULL, "open", "DevNotes_new.exe", NULL, NULL, SW_SHOW);
                        
                        // Chiudi questa versione
                        PostQuitMessage(0);
                    }
                    else
                    {
                        // Fallback: reload UI normale
                        Layout::Cleanup();
                        Layout::CreateModernFonts();
                        Layout::CreateDevNotesLayout(hwnd);
                        InvalidateRect(hwnd, NULL, TRUE);
                        MessageBox(hwnd, "UI Reloaded! (No new version found)", "DevNotes", MB_OK | MB_ICONINFORMATION);
                    }
                }
                break;
            case 'N':
                // Ctrl+N = New note
                MessageBox(hwnd, "Nuova nota - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
                break;
            case 'F':
                // Ctrl+F = Search
                MessageBox(hwnd, "Ricerca globale - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        else
        {
            switch (wParam)
            {
            case VK_F6:
                // F6 = Toggle theme
                MessageBox(hwnd, "Theme toggle - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;

    case WM_SIZE:
        Layout::ResizeLayoutPanels(hwnd);
        break;

    case WM_DESTROY:
        Layout::Cleanup();
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
