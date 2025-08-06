#pragma once

#include "Common.h"

// Classe ModernUI - Gestione del tema moderno
class ModernUI
{
public:
    // Colori del tema scuro moderno
    static const COLORREF BG_DARK;          // Background principale
    static const COLORREF BG_PANEL;         // Background pannelli
    static const COLORREF TEXT_PRIMARY;     // Testo principale
    static const COLORREF TEXT_SECONDARY;   // Testo secondario
    static const COLORREF ACCENT_BLUE;      // Colore accent
    static const COLORREF BORDER_COLOR;     // Bordi
    
    // Brush e Pen per disegno
    static HBRUSH hBrushDark;
    static HBRUSH hBrushPanel;
    static HBRUSH hBrushAccent;
    static HPEN hPenBorder;
    
    // Inizializzazione tema
    static void InitializeTheme();
    static void CleanupTheme();
    
    // Custom drawing functions
    static void DrawModernButton(HDC hdc, RECT rect, const char* text, bool pressed = false);
    static void DrawModernPanel(HDC hdc, RECT rect);
    static void DrawModernListBox(HDC hdc, RECT rect);
    static void DrawModernEdit(HDC hdc, RECT rect);
    
    // Window procedure personalizzati
    static LRESULT CALLBACK ModernListBoxProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK ModernEditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK ModernStaticProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    
    // Funzioni per subclassing
    static void ApplyModernStyle(HWND hwnd, const char* className);
    
    // Original window procedures (pubbliche per accesso)
    static WNDPROC OriginalListBoxProc;
    static WNDPROC OriginalEditProc;
    static WNDPROC OriginalStaticProc;
};
