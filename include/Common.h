#pragma once

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
extern HINSTANCE hInst;
extern HWND hMainWindow;
extern HWND hSidebarLeft;      // File explorer
extern HWND hEditorMain;       // Editor markdown principale
extern HWND hPanelRight;       // Backlinks/Graph panel
extern HWND hStatusBar;        // Status bar bottom

// Font per design moderno
extern HFONT hFontUI;          // Font UI (Segoe UI)
extern HFONT hFontEditor;      // Font editor (monospace)
