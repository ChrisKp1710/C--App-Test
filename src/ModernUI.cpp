#include "ModernUI.h"

// Definizione colori tema scuro moderno (simile a Obsidian)
const COLORREF ModernUI::BG_DARK = RGB(25, 26, 28);           // Nero scuro
const COLORREF ModernUI::BG_PANEL = RGB(35, 36, 39);         // Grigio scuro pannelli
const COLORREF ModernUI::TEXT_PRIMARY = RGB(230, 230, 230);   // Bianco per testo
const COLORREF ModernUI::TEXT_SECONDARY = RGB(160, 160, 160); // Grigio per testo secondario
const COLORREF ModernUI::ACCENT_BLUE = RGB(100, 149, 237);    // Blu moderno
const COLORREF ModernUI::BORDER_COLOR = RGB(60, 60, 60);      // Bordi sottili

// Risorse grafiche
HBRUSH ModernUI::hBrushDark = NULL;
HBRUSH ModernUI::hBrushPanel = NULL;
HBRUSH ModernUI::hBrushAccent = NULL;
HPEN ModernUI::hPenBorder = NULL;

// Original procedures
WNDPROC ModernUI::OriginalListBoxProc = NULL;
WNDPROC ModernUI::OriginalEditProc = NULL;
WNDPROC ModernUI::OriginalStaticProc = NULL;

void ModernUI::InitializeTheme()
{
    // Crea brush per i colori
    hBrushDark = CreateSolidBrush(BG_DARK);
    hBrushPanel = CreateSolidBrush(BG_PANEL);
    hBrushAccent = CreateSolidBrush(ACCENT_BLUE);
    hPenBorder = CreatePen(PS_SOLID, 1, BORDER_COLOR);
}

void ModernUI::CleanupTheme()
{
    // Pulisce le risorse
    if (hBrushDark) DeleteObject(hBrushDark);
    if (hBrushPanel) DeleteObject(hBrushPanel);
    if (hBrushAccent) DeleteObject(hBrushAccent);
    if (hPenBorder) DeleteObject(hPenBorder);
}

void ModernUI::DrawModernPanel(HDC hdc, RECT rect)
{
    // Riempie con colore panel moderno
    FillRect(hdc, &rect, hBrushPanel);
    
    // Bordo sottile
    HPEN oldPen = (HPEN)SelectObject(hdc, hPenBorder);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
}

void ModernUI::DrawModernListBox(HDC hdc, RECT rect)
{
    // Background scuro
    FillRect(hdc, &rect, hBrushDark);
    
    // Bordo accent sottile
    HPEN accentPen = CreatePen(PS_SOLID, 1, ACCENT_BLUE);
    HPEN oldPen = (HPEN)SelectObject(hdc, accentPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(accentPen);
}

void ModernUI::DrawModernEdit(HDC hdc, RECT rect)
{
    // Background editor scuro
    FillRect(hdc, &rect, hBrushDark);
    
    // Bordo accent
    HPEN accentPen = CreatePen(PS_SOLID, 2, ACCENT_BLUE);
    HPEN oldPen = (HPEN)SelectObject(hdc, accentPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(accentPen);
}

// Custom ListBox procedure
LRESULT CALLBACK ModernUI::ModernListBoxProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        RECT rect;
        GetClientRect(hwnd, &rect);
        
        // Disegna background moderno
        DrawModernListBox(hdc, rect);
        
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1; // Previene flicker
    }
    
    return CallWindowProc(OriginalListBoxProc, hwnd, uMsg, wParam, lParam);
}

// Custom Edit procedure  
LRESULT CALLBACK ModernUI::ModernEditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        RECT rect;
        GetClientRect(hwnd, &rect);
        
        // Disegna background moderno
        DrawModernEdit(hdc, rect);
        
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1; // Previene flicker
    }
    
    return CallWindowProc(OriginalEditProc, hwnd, uMsg, wParam, lParam);
}

// Custom Static procedure
LRESULT CALLBACK ModernUI::ModernStaticProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        RECT rect;
        GetClientRect(hwnd, &rect);
        
        // Disegna background moderno
        DrawModernPanel(hdc, rect);
        
        // Testo con colore moderno
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, TEXT_PRIMARY);
        
        char text[1024];
        GetWindowText(hwnd, text, sizeof(text));
        DrawText(hdc, text, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
        
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1; // Previene flicker
    }
    
    return CallWindowProc(OriginalStaticProc, hwnd, uMsg, wParam, lParam);
}
