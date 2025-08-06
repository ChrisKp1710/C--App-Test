#pragma once

#include "Common.h"

// Classe Window - Gestione finestra principale
class Window
{
public:
    static bool Initialize(HINSTANCE hInstance);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void Show(int nCmdShow);
    static int MessageLoop();
    
private:
    static const char* CLASS_NAME;
};
