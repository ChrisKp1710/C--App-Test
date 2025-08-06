#include "Layout.h"

void Layout::CreateModernFonts()
{
    // Font per UI - Segoe UI più grande
    hFontUI = CreateFont(
        -16,                        // Altezza maggiore
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

    // Font per editor - Consolas più grande
    hFontEditor = CreateFont(
        -18,                        // Altezza maggiore
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

void Layout::CreateDevNotesLayout(HWND hwnd)
{
    // Sidebar sinistra - File Explorer con stile moderno
    hSidebarLeft = CreateWindowEx(
        0, // Rimuovi bordo 3D
        "LISTBOX",
        "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOTIFY,
        5, 5, SIDEBAR_WIDTH-5, 400, // Padding moderno
        hwnd,
        (HMENU)ID_SIDEBAR_LEFT,
        hInst,
        NULL
    );

    // Editor principale - Area centrale con bordi sottili
    hEditorMain = CreateWindowEx(
        0, // Rimuovi bordo 3D 
        "EDIT",
        "# Benvenuto in DevNotes\n\nInizia a scrivere la tua prima nota...\n\n## Features\n- [[Link]] tra note\n- #tags organizzazione\n- **Markdown** formatting\n\n> Quote di esempio\n\n```cpp\n// Code block esempio\nint main() {\n    return 0;\n}\n```",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | 
        ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN,
        SIDEBAR_WIDTH+5, 5, 400, 400, // Padding moderno
        hwnd,
        (HMENU)ID_EDITOR_MAIN,
        hInst,
        NULL
    );

    // Panel destro - Backlinks/Graph con stile moderno
    hPanelRight = CreateWindowEx(
        0, // Rimuovi bordo 3D
        "STATIC",
        "Backlinks & Graph\n\n🔗 Collegamenti:\n• [[Welcome]]\n• [[Ideas]]\n\n🏷️ Tags utilizzati:\n• #devnotes\n• #markdown\n\n📊 Statistiche:\n• 1 nota attiva\n• 247 parole\n• Ultima modifica: ora",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        600, 5, PANEL_RIGHT_WIDTH-5, 400, // Padding moderno
        hwnd,
        (HMENU)ID_PANEL_RIGHT,
        hInst,
        NULL
    );

    // Status bar moderno
    hStatusBar = CreateWindow(
        STATUSCLASSNAME,
        "",
        WS_CHILD | WS_VISIBLE,
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

    // Popola la sidebar con file di esempio più moderni
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📁 My Notes");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Welcome.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Daily Notes.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Project Ideas.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Code Snippets.md");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📁 Archive");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📁 Templates");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"🔗 Quick Links");

    // Imposta status bar moderno
    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)"🚀 DevNotes v1.0 | Ready | 247 words | Obsidian-style knowledge management");

    // Focus sull'editor
    SetFocus(hEditorMain);
}

void Layout::ResizeLayoutPanels(HWND hwnd)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int contentHeight = height - STATUSBAR_HEIGHT;
    int editorWidth = width - SIDEBAR_WIDTH - PANEL_RIGHT_WIDTH;

    // Ridimensiona sidebar sinistra con padding
    SetWindowPos(hSidebarLeft, NULL, 
        5, 5, 
        SIDEBAR_WIDTH - 10, contentHeight - 10, 
        SWP_NOZORDER);

    // Ridimensiona editor centrale con padding
    SetWindowPos(hEditorMain, NULL, 
        SIDEBAR_WIDTH + 5, 5, 
        editorWidth - 10, contentHeight - 10, 
        SWP_NOZORDER);

    // Ridimensiona panel destro con padding
    SetWindowPos(hPanelRight, NULL, 
        SIDEBAR_WIDTH + editorWidth + 5, 5, 
        PANEL_RIGHT_WIDTH - 10, contentHeight - 10, 
        SWP_NOZORDER);

    // Ridimensiona status bar
    SetWindowPos(hStatusBar, NULL, 
        0, contentHeight, 
        width, STATUSBAR_HEIGHT, 
        SWP_NOZORDER);
}

void Layout::Cleanup()
{
    // Cleanup fonts
    if (hFontUI) DeleteObject(hFontUI);
    if (hFontEditor) DeleteObject(hFontEditor);
}
