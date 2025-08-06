#pragma once

#include "Common.h"

// Classe HotReload - Sistema di ricaricamento live
class HotReload
{
public:
    static void Initialize();
    static void CheckForChanges();
    static void ReloadUI();
    static void ReloadContent();
    
    // File monitoring
    static void WatchFiles();
    static void OnFileChanged(const char* filename);
    
    // Live updates
    static void UpdateSidebarContent();
    static void UpdateEditorContent(); 
    static void UpdatePanelContent();
    static void UpdateColors();
    
    // Config file support
    static void LoadConfigFile();
    static void SaveConfigFile();
    
private:
    static HANDLE hFileWatcher;
    static bool isWatching;
};
