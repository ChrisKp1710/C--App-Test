#pragma once

#include "Common.h"

// Classe Layout - Gestione layout a 3 pannelli
class Layout
{
public:
    static void CreateModernFonts();
    static void CreateDevNotesLayout(HWND hwnd);
    static void ResizeLayoutPanels(HWND hwnd);
    static void Cleanup();
};
