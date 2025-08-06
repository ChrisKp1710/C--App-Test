#include <windows.h>
#include <string>
#include <commctrl.h>

// Costanti per i controlli - DevNotes Layout
#define ID_SIDEBAR_LEFT 2001
#define ID_EDITOR_MAIN 2002
#define ID_PANEL_RIGHT 2003
#define ID_MENU_NEW_NOTE 2004
#define ID_MENU_OPEN_NOTE 2005
#define ID_STATUSBAR 2006

// Layout costanti per il design pulito
#define SIDEBAR_WIDTH 250
#define PANEL_RIGHT_WIDTH 300
#define STATUSBAR_HEIGHT 25

// Variabili globali - DevNotes UI
HINSTANCE hInst;
HWND hMainWindow;
HWND hSidebarLeft;      // File explorer
HWND hEditorMain;       // Editor markdown principale
HWND hPanelRight;       // Backlinks/Graph panel
HWND hStatusBar;        // Status bar bottom

// Font per design moderno
HFONT hFontUI;          // Font UI (Segoe UI)
HFONT hFontEditor;      // Font editor (monospace)

// Dichiarazioni delle funzioni - DevNotes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateDevNotesLayout(HWND hwnd);
void CreateModernFonts();
void ResizeLayoutPanels(HWND hwnd);
void InitializeDevNotes();

// Punto di ingresso dell'applicazione
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Evita warning per parametri non usati
    (void)hPrevInstance;
    (void)lpCmdLine;
    
    hInst = hInstance;

    // Registra la classe della finestra
    const char* CLASS_NAME = "DevNotesApp";
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(248, 249, 250)); // Colore background moderno
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpszMenuName = NULL;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Errore nella registrazione della classe finestra!", "Errore", MB_OK | MB_ICONERROR);
        return 0;
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

    if (hMainWindow == NULL)
    {
        MessageBox(NULL, "Errore nella creazione della finestra!", "Errore", MB_OK | MB_ICONERROR);
        return 0;
    }

    // Mostra la finestra
    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);

    // Inizializza DevNotes
    InitializeDevNotes();

    // Loop dei messaggi
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Procedura per gestire i messaggi della finestra - DevNotes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        CreateModernFonts();
        CreateDevNotesLayout(hwnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_MENU_NEW_NOTE:
            // TODO: Implementare creazione nuova nota
            MessageBox(hwnd, "Nuova nota - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_MENU_OPEN_NOTE:
            // TODO: Implementare apertura nota
            MessageBox(hwnd, "Apri nota - Coming soon!", "DevNotes", MB_OK | MB_ICONINFORMATION);
            break;
        }
        break;

    case WM_SIZE:
        ResizeLayoutPanels(hwnd);
        break;

    case WM_DESTROY:
        // Cleanup fonts
        if (hFontUI) DeleteObject(hFontUI);
        if (hFontEditor) DeleteObject(hFontEditor);
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Crea i font moderni per DevNotes
void CreateModernFonts()
{
    // Font per UI - Segoe UI (standard Windows)
    hFontUI = CreateFont(
        -14,                        // Altezza
        0,                          // Larghezza
        0,                          // Escapement
        0,                          // Orientation
        FW_NORMAL,                  // Weight
        FALSE,                      // Italic
        FALSE,                      // Underline
        FALSE,                      // StrikeOut
        DEFAULT_CHARSET,            // CharSet
        OUT_DEFAULT_PRECIS,         // OutPrecision
        CLIP_DEFAULT_PRECIS,        // ClipPrecision
        CLEARTYPE_QUALITY,          // Quality
        DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
        "Segoe UI"                  // Font name
    );

    // Font per editor - Consolas (monospace)
    hFontEditor = CreateFont(
        -16,                        // Altezza
        0,                          // Larghezza
        0,                          // Escapement
        0,                          // Orientation
        FW_NORMAL,                  // Weight
        FALSE,                      // Italic
        FALSE,                      // Underline
        FALSE,                      // StrikeOut
        DEFAULT_CHARSET,            // CharSet
        OUT_DEFAULT_PRECIS,         // OutPrecision
        CLIP_DEFAULT_PRECIS,        // ClipPrecision
        CLEARTYPE_QUALITY,          // Quality
        FIXED_PITCH | FF_MODERN,    // PitchAndFamily
        "Consolas"                  // Font name
    );
}

// Crea il layout a 3 pannelli stile Obsidian
void CreateDevNotesLayout(HWND hwnd)
{
    // Sidebar sinistra - File Explorer
    hSidebarLeft = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "LISTBOX",
        "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOTIFY,
        0, 0, SIDEBAR_WIDTH, 400,
        hwnd,
        (HMENU)ID_SIDEBAR_LEFT,
        hInst,
        NULL
    );

    // Editor principale - Area centrale
    hEditorMain = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "# Benvenuto in DevNotes\n\nInizia a scrivere la tua prima nota...\n\n## Features\n- [[Link]] tra note\n- #tags organizzazione\n- **Markdown** formatting\n",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | 
        ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN,
        SIDEBAR_WIDTH, 0, 400, 400,
        hwnd,
        (HMENU)ID_EDITOR_MAIN,
        hInst,
        NULL
    );

    // Panel destro - Backlinks/Graph
    hPanelRight = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "STATIC",
        "Backlinks & Graph\n\nQui apparirà:\n• Collegamenti inversi\n• Grafo delle connessioni\n• Tag utilizzati\n• Metadati nota",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        600, 0, PANEL_RIGHT_WIDTH, 400,
        hwnd,
        (HMENU)ID_PANEL_RIGHT,
        hInst,
        NULL
    );

    // Status bar
    hStatusBar = CreateWindow(
        STATUSCLASSNAME,
        "",
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
        0, 0, 0, 0,
        hwnd,
        (HMENU)ID_STATUSBAR,
        hInst,
        NULL
    );

    // Applica i font moderni
    if (hFontUI)
    {
        SendMessage(hSidebarLeft, WM_SETFONT, (WPARAM)hFontUI, TRUE);
        SendMessage(hPanelRight, WM_SETFONT, (WPARAM)hFontUI, TRUE);
        SendMessage(hStatusBar, WM_SETFONT, (WPARAM)hFontUI, TRUE);
    }
    
    if (hFontEditor)
    {
        SendMessage(hEditorMain, WM_SETFONT, (WPARAM)hFontEditor, TRUE);
    }

    // Popola la sidebar con file di esempio
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📁 Notes");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Welcome.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Ideas.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Projects.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📁 Archive");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📁 Templates");

    // Imposta status bar
    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)"Ready | DevNotes v1.0 | 0 words");

    // Focus sull'editor
    SetFocus(hEditorMain);
}

// Ridimensiona i pannelli quando la finestra cambia dimensione
void ResizeLayoutPanels(HWND hwnd)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int contentHeight = height - STATUSBAR_HEIGHT;
    int editorWidth = width - SIDEBAR_WIDTH - PANEL_RIGHT_WIDTH;

    // Ridimensiona sidebar sinistra
    SetWindowPos(hSidebarLeft, NULL, 
        0, 0, 
        SIDEBAR_WIDTH, contentHeight, 
        SWP_NOZORDER);

    // Ridimensiona editor centrale
    SetWindowPos(hEditorMain, NULL, 
        SIDEBAR_WIDTH, 0, 
        editorWidth, contentHeight, 
        SWP_NOZORDER);

    // Ridimensiona panel destro
    SetWindowPos(hPanelRight, NULL, 
        SIDEBAR_WIDTH + editorWidth, 0, 
        PANEL_RIGHT_WIDTH, contentHeight, 
        SWP_NOZORDER);

    // Ridimensiona status bar
    SetWindowPos(hStatusBar, NULL, 
        0, contentHeight, 
        width, STATUSBAR_HEIGHT, 
        SWP_NOZORDER);
}

// Inizializzazione DevNotes
void InitializeDevNotes()
{
    // TODO: Carica configurazione
    // TODO: Scan directory notes
    // TODO: Carica ultima nota aperta
    
    // Per ora mostra messaggio di benvenuto
    SetWindowText(hStatusBar, "DevNotes avviato con successo!");
}
