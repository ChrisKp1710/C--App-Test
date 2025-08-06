# Windows Helper - Assistente per Windows

Un'applicazione desktop C++ con interfaccia grafica nativa per Windows.

## 🚀 **Stato del Progetto: COMPLETATO E FUNZIONANTE!**

### Caratteristiche Attuali:
- ✅ **Interfaccia grafica Windows nativa** con API Win32
- ✅ **Compilazione ottimizzata** con MinGW-w64  
- ✅ **Nessun errore di compilazione** o linting
- ✅ **Ridimensionamento automatico** dei controlli
- ✅ **Gestione eventi completa**

### Come Usare:

#### Esegui l'applicazione:
```cmd
.\WindowsHelper.exe
```

#### Compila l'applicazione:
```cmd
.\build.bat
```

#### Pulisci i file di build:
```cmd
.\clean.bat
```

### Funzionalità Implementate:
- **Casella di testo** per inserire messaggi
- **Bottone "Invia Messaggio"** per aggiungere testo alla lista
- **Bottone "Pulisci Lista"** per svuotare la lista messaggi
- **Lista scorrevole** che mostra tutti i messaggi inseriti
- **Ridimensionamento responsive** dell'interfaccia

## 🛠️ **Tecnologie Utilizzate:**
- **Linguaggio**: C++17
- **GUI**: Win32 API native
- **Compilatore**: MinGW-w64 (GCC 15.1.0)
- **Build System**: Makefile + Script Batch  
- **IDE**: Visual Studio Code

## 📁 **Struttura Progetto:**
```
prova/
├── src/
│   └── main.cpp           # Codice sorgente principale
├── .vscode/               # Configurazione VS Code
├── build.bat              # Script di compilazione
├── clean.bat              # Script per pulizia
├── Makefile               # Build system alternativo
└── WindowsHelper.exe      # Eseguibile (dopo compilazione)
```

## 🎯 **Pronto per Nuove Funzionalità!**

La base è solida e pronta per essere estesa con:
- Monitor delle risorse di sistema
- Utilità per la gestione file
- Strumenti di rete
- Automazione attività
- E molto altro...

---

**Progetto creato con successo!** 🎉

## Funzionalità Attuali

- 🖼️ **Interfaccia Grafica Nativa**: Utilizzando le API Win32 per massima compatibilità
- 📝 **Input di Testo**: Casella di testo per inserire messaggi
- 📋 **Lista Messaggi**: Visualizzazione dei messaggi in una lista scorrevole
- 🔘 **Controlli Interattivi**: Bottoni per inviare messaggi e pulire la lista
- 📱 **Responsive**: L'interfaccia si adatta al ridimensionamento della finestra

## Requisiti di Sistema

- **Sistema Operativo**: Windows 7 o superiore
- **Compilatore**: MinGW-w64 (GCC per Windows)
- **Editor**: Visual Studio Code (raccomandato)

## Installazione e Setup

### 1. Installare MinGW-w64

Scarica e installa MinGW-w64 da [https://www.mingw-w64.org/](https://www.mingw-w64.org/)

Assicurati che `gcc`, `g++` e `mingw32-make` siano nel PATH di sistema.

### 2. Verificare l'Installazione

Apri il prompt dei comandi e verifica:

```cmd
gcc --version
g++ --version
mingw32-make --version
```

## Compilazione

### Compilazione Standard
```cmd
mingw32-make
```

### Compilazione in Modalità Debug
```cmd
mingw32-make debug
```

### Pulizia dei File di Build
```cmd
mingw32-make clean
```

### Compilazione ed Esecuzione
```cmd
mingw32-make run
```

## Utilizzo in Visual Studio Code

### Comandi Disponibili (Ctrl+Shift+P):

- **Tasks: Run Task** → "Build Application" - Compila l'applicazione
- **Tasks: Run Task** → "Build Debug" - Compila in modalità debug
- **Tasks: Run Task** → "Run Application" - Compila ed esegue
- **Tasks: Run Task** → "Clean Build" - Pulisce i file di build

### Debug

1. Apri il file `src/main.cpp`
2. Imposta dei breakpoint cliccando sulla riga desiderata
3. Premi **F5** per avviare il debug

## Struttura del Progetto

```
prova/
├── src/                    # File sorgenti C++
│   └── main.cpp           # File principale dell'applicazione
├── include/               # File header (per future espansioni)
├── obj/                   # File oggetto compilati (generati)
├── .vscode/               # Configurazione Visual Studio Code
│   ├── tasks.json         # Task di build
│   ├── launch.json        # Configurazione debug
│   └── c_cpp_properties.json # Configurazione IntelliSense
├── .github/               # Configurazione GitHub
│   └── copilot-instructions.md # Istruzioni per GitHub Copilot
├── Makefile              # Script di compilazione
├── README.md             # Questo file
└── WindowsHelper.exe     # Eseguibile (generato dopo la compilazione)
```

## Idee per Espansioni Future

### 🛠️ Utilità di Sistema
- Monitor delle risorse (CPU, RAM, disco)
- Pulizia file temporanei
- Gestione processi in esecuzione
- Informazioni di sistema

### 📁 Gestione File
- Esploratore file migliorato
- Ricerca avanzata file
- Operazioni batch sui file
- Sincronizzazione cartelle

### 🔧 Automazione
- Task scheduler personalizzato
- Script automatici
- Backup automatico
- Monitoraggio cartelle

### 🌐 Connettività
- Test connessione di rete
- Monitor traffico rete
- Ping e traceroute GUI
- Gestione connessioni WiFi

### 🎨 Personalizzazione
- Tema scuro/chiaro
- Configurazioni salvabili
- Scorciatoie personalizzabili
- Plugin system

## Contributi

Questo è un progetto in fase di sviluppo. Sentiti libero di:

- Suggerire nuove funzionalità
- Segnalare bug
- Contribuire con codice
- Migliorare la documentazione

## Licenza

Progetto open source - sentiti libero di usarlo e modificarlo secondo le tue esigenze.

---

**Nota**: Questo è un progetto base che può essere esteso con molte funzionalità utili per gli utenti Windows. La struttura è progettata per essere facilmente espandibile.
