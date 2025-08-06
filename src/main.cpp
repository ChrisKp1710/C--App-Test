#include <windows.h>
#include <string>

// Costanti per i controlli
#define ID_BUTTON_HELLO 1001
#define ID_BUTTON_CLEAR 1002
#define ID_TEXTBOX 1003
#define ID_LISTBOX 1004

// Variabili globali
HINSTANCE hInst;
HWND hMainWindow;
HWND hTextBox;
HWND hListBox;

// Dichiarazioni delle funzioni
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateControls(HWND hwnd);
void AddMessageToList(const std::string& message);

// Punto di ingresso dell'applicazione
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Evita warning per parametri non usati
    (void)hPrevInstance;
    (void)lpCmdLine;
    
    hInst = hInstance;

    // Registra la classe della finestra
    const char* CLASS_NAME = "WindowsHelperApp";
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Errore nella registrazione della classe finestra!", "Errore", MB_OK | MB_ICONERROR);
        return 0;
    }

    // Crea la finestra principale
    hMainWindow = CreateWindowEx(
        0,                              // Stili estesi
        CLASS_NAME,                     // Nome classe
        "Windows Helper - Assistente per Windows",  // Titolo finestra
        WS_OVERLAPPEDWINDOW,            // Stile finestra
        CW_USEDEFAULT, CW_USEDEFAULT,   // Posizione
        800, 600,                       // Dimensioni
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

    // Messaggio di benvenuto
    AddMessageToList("Benvenuto in Windows Helper!");
    AddMessageToList("Questa applicazione ti aiutera' con varie attivita' su Windows.");

    // Loop dei messaggi
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Procedura per gestire i messaggi della finestra
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        CreateControls(hwnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BUTTON_HELLO:
        {
            char buffer[256];
            GetWindowText(hTextBox, buffer, sizeof(buffer));
            
            if (strlen(buffer) > 0)
            {
                std::string message = "Hai scritto: " + std::string(buffer);
                AddMessageToList(message);
                SetWindowText(hTextBox, ""); // Pulisce il textbox
            }
            else
            {
                AddMessageToList("Scrivi qualcosa nella casella di testo!");
            }
            break;
        }
        case ID_BUTTON_CLEAR:
            SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
            AddMessageToList("Lista pulita!");
            break;
        }
        break;

    case WM_SIZE:
    {
        // Ridimensiona i controlli quando la finestra viene ridimensionata
        RECT rect;
        GetClientRect(hwnd, &rect);
        
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        
        // Ridimensiona i controlli
        SetWindowPos(hTextBox, NULL, 20, 20, width - 40, 25, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_HELLO), NULL, 20, 55, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_CLEAR), NULL, 130, 55, 100, 30, SWP_NOZORDER);
        SetWindowPos(hListBox, NULL, 20, 95, width - 40, height - 125, SWP_NOZORDER);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Crea tutti i controlli dell'interfaccia
void CreateControls(HWND hwnd)
{
    // Casella di testo per input
    hTextBox = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        20, 20, 400, 25,
        hwnd,
        (HMENU)ID_TEXTBOX,
        hInst,
        NULL
    );

    // Bottone "Invia messaggio"
    CreateWindow(
        "BUTTON",
        "Invia Messaggio",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 55, 100, 30,
        hwnd,
        (HMENU)ID_BUTTON_HELLO,
        hInst,
        NULL
    );

    // Bottone "Pulisci"
    CreateWindow(
        "BUTTON",
        "Pulisci Lista",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        130, 55, 100, 30,
        hwnd,
        (HMENU)ID_BUTTON_CLEAR,
        hInst,
        NULL
    );

    // Lista per mostrare i messaggi
    hListBox = CreateWindow(
        "LISTBOX",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_HASSTRINGS,
        20, 95, 400, 200,
        hwnd,
        (HMENU)ID_LISTBOX,
        hInst,
        NULL
    );

    // Imposta il focus sulla casella di testo
    SetFocus(hTextBox);
}

// Aggiunge un messaggio alla lista
void AddMessageToList(const std::string& message)
{
    if (hListBox != NULL)
    {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)message.c_str());
        // Scorre automaticamente all'ultimo elemento
        int count = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
        SendMessage(hListBox, LB_SETTOPINDEX, count - 1, 0);
    }
}
