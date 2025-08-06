#include "Layout.h"
#include "ModernUI.h"

void Layout::Cleanup()
{
    // Distruggi i controlli esistenti se presenti
    if (hSidebarLeft) DestroyWindow(hSidebarLeft);
    if (hEditorMain) DestroyWindow(hEditorMain);
    if (hPanelRight) DestroyWindow(hPanelRight);
    if (hStatusBar) DestroyWindow(hStatusBar);
    
    // Reset handles
    hSidebarLeft = hEditorMain = hPanelRight = hStatusBar = NULL;
    
    // Distruggi i font
    if (hFontUI) DeleteObject(hFontUI);
    if (hFontEditor) DeleteObject(hFontEditor);
    hFontUI = hFontEditor = NULL;
}

void Layout::CreateModernFonts()
{
    // Inizializza tema moderno
    ModernUI::InitializeTheme();
    
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
    // Sidebar sinistra - File Explorer con stile migliorato
    hSidebarLeft = CreateWindowEx(
        WS_EX_CLIENTEDGE, // Bordo moderno
        "LISTBOX",
        "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOTIFY,
        8, 8, SIDEBAR_WIDTH-16, 400, // Più padding
        hwnd,
        (HMENU)ID_SIDEBAR_LEFT,
        hInst,
        NULL
    );

    // Editor principale - Area centrale 
    hEditorMain = CreateWindowEx(
        WS_EX_CLIENTEDGE, // Bordo sottile elegante
        "EDIT",
        "# Benvenuto in DevNotes\n\nInizia a scrivere la tua prima nota...\n\n## Features\n- [[Link]] tra note\n- #tags organizzazione\n- **Markdown** formatting\n\n> Quote di esempio\n\n```cpp\n// Code block esempio\nint main() {\n    return 0;\n}\n```\n\n## Links\n- [[Welcome]] - Pagina di benvenuto\n- [[Ideas]] - Le tue idee\n\n## Tags\n#devnotes #markdown #knowledge",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | 
        ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN,
        SIDEBAR_WIDTH + 8, 8, 400, 400, 
        hwnd,
        (HMENU)ID_EDITOR_MAIN,
        hInst,
        NULL
    );

    // Panel destro - Backlinks/Graph
    hPanelRight = CreateWindowEx(
        WS_EX_CLIENTEDGE, // Bordo elegante
        "STATIC",
        "🌟 DevNotes Dashboard 🌟\n\n🔗 Collegamenti in entrata:\n→ [[Welcome]] (2 references)\n→ [[Ideas]] (1 reference)\n\n🏷️ Tags utilizzati:\n→ #devnotes (3 notes)\n→ #markdown (2 notes)\n→ #knowledge (1 note)\n\n📊 Statistiche:\n→ 1 nota attiva ✅\n→ 247 parole totali 📝\n→ Ultima modifica: ora ⏰\n→ 3 collegamenti 🔗\n\n🚀 Quick Actions:\n→ Nuova nota [Ctrl+N] 📄\n→ Ricerca globale [Ctrl+F] 🔍\n→ Reload UI [Ctrl+R] 🔄\n→ Graph view [F6] 🎨",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        600, 8, PANEL_RIGHT_WIDTH-16, 400,
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

    // Applica i font moderni (SENZA subclassing per ora)
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

    // TODO: Rimettere custom styling quando sarà corretto
    // ModernUI::OriginalListBoxProc = (WNDPROC)SetWindowLongPtr(hSidebarLeft, GWLP_WNDPROC, (LONG_PTR)ModernUI::ModernListBoxProc);
    // ModernUI::OriginalEditProc = (WNDPROC)SetWindowLongPtr(hEditorMain, GWLP_WNDPROC, (LONG_PTR)ModernUI::ModernEditProc);
    // ModernUI::OriginalStaticProc = (WNDPROC)SetWindowLongPtr(hPanelRight, GWLP_WNDPROC, (LONG_PTR)ModernUI::ModernStaticProc);

    // Popola la sidebar con contenuto più ricco
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"🌟 My Notes (4) ⭐");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Welcome.md 🎉");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Daily Notes.md 📅");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Project Ideas.md 💡");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Code Snippets.md 💻");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"🗃️ Archive (2) 📦");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Old Notes.md 🗂️");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📝 Experiments.md 🧪");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"📋 Templates (3) ✨");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📄 Meeting Template 🤝");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"  📄 Project Template 🚀");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"🔗 Quick Links 🌐");
    SendMessage(hSidebarLeft, LB_ADDSTRING, 0, (LPARAM)"🔍 Recent Searches 🕵️");

    // Status bar più informativo
    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)"🚀 DevNotes v1.0 | ✅ Ready | 📝 247 words | 🔗 3 links | 💾 Last saved: now | 🧠 Obsidian-style | 🔄 Ctrl+R to reload");

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

    // Ridimensiona sidebar sinistra con padding elegante
    SetWindowPos(hSidebarLeft, NULL, 
        8, 8, 
        SIDEBAR_WIDTH - 16, contentHeight - 16, 
        SWP_NOZORDER);

    // Ridimensiona editor centrale con padding
    SetWindowPos(hEditorMain, NULL, 
        SIDEBAR_WIDTH + 8, 8, 
        editorWidth - 16, contentHeight - 16, 
        SWP_NOZORDER);

    // Ridimensiona panel destro con padding  
    SetWindowPos(hPanelRight, NULL, 
        SIDEBAR_WIDTH + editorWidth + 8, 8, 
        PANEL_RIGHT_WIDTH - 16, contentHeight - 16, 
        SWP_NOZORDER);

    // Ridimensiona status bar
    SetWindowPos(hStatusBar, NULL, 
        0, contentHeight, 
        width, STATUSBAR_HEIGHT, 
        SWP_NOZORDER);
}
