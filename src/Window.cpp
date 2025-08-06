#include "Window.h"
#include "Layout.h"

const char* Window::CLASS_NAME = "DevNotesApp";

bool Window::Initialize(HINSTANCE hInstance)
{
    // Registra la classe della finestra
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(37, 39, 42)); // Dark theme moderno
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
