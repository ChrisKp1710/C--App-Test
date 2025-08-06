<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

# Istruzioni per GitHub Copilot - Windows Helper App

## Contesto del Progetto

Questo è un progetto di applicazione desktop Windows scritta in C++ utilizzando le API Win32 native. L'obiettivo è creare un software di utilità per aiutare gli utenti di Windows con varie attività.

## Linee Guida per il Codice

### Stile di Programmazione
- Utilizza C++17 come standard
- Segui le convenzioni di naming di Windows API (PascalCase per funzioni, camelCase per variabili)
- Commenta il codice in italiano
- Usa nomi di variabili e funzioni descrittivi

### API e Librerie
- Utilizza principalmente le API Win32 native per la GUI
- Includi `windows.h` e `commctrl.h` per i controlli comuni
- Evita dipendenze esterne non necessarie per mantenere la semplicità

### Gestione della Memoria
- Gestisci correttamente le risorse Windows (handle, memory, etc.)
- Usa RAII quando possibile
- Assicurati di chiamare le funzioni di cleanup appropriate

### Interfaccia Utente
- Mantieni l'interfaccia semplice e intuitiva
- Usa controlli Windows standard (button, edit, listbox, etc.)
- Implementa il ridimensionamento responsive dei controlli
- Gestisci correttamente i messaggi Windows

### Struttura del Codice
- Mantieni il codice modulare e ben organizzato
- Usa file header (.h) per dichiarazioni in `/include`
- Implementazioni in file sorgente (.cpp) in `/src`
- Separa la logica UI dalla logica business

### Funzionalità Suggerite
Quando suggerisci nuove funzionalità, considera:
- Utilità di sistema (monitor risorse, pulizia file)
- Gestione file avanzata
- Automazione attività
- Strumenti di rete
- Personalizzazione interfaccia

### Build e Debug
- Il progetto usa Makefile con MinGW-w64
- Supporta build in modalità debug e release
- Configurazione VS Code per IntelliSense e debugging

## Note Tecniche

- Target: Windows 7 e superiori
- Architettura: x64 preferita, compatibile x86
- Compilatore: GCC tramite MinGW-w64
- Editor: Visual Studio Code con estensione C/C++

## Esempi di Pattern da Seguire

### Creazione Controlli
```cpp
HWND hControl = CreateWindow(
    "BUTTON",                    // Tipo controllo
    "Testo Bottone",            // Testo
    WS_VISIBLE | WS_CHILD,      // Stili
    x, y, width, height,        // Posizione e dimensioni
    hParent,                    // Finestra padre
    (HMENU)ID_CONTROL,          // ID controllo
    hInstance,                  // Istanza app
    NULL                        // Parametri extra
);
```

### Gestione Messaggi
```cpp
case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case ID_BUTTON:
        // Logica del bottone
        break;
    }
    break;
```

Quando generi codice, mantieni sempre questi principi e assicurati che il codice sia compatibile con la struttura esistente del progetto.
