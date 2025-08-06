# Guida all'Installazione di MinGW-w64

## Metodo 1: MSYS2 (Raccomandato)

### Passo 1: Scarica MSYS2
1. Vai su [https://www.msys2.org/](https://www.msys2.org/)
2. Scarica l'installer per il tuo sistema (x86_64 per Windows 64-bit)
3. Esegui l'installer e segui la procedura guidata

### Passo 2: Installa il Compilatore
Apri il terminale MSYS2 e esegui:

```bash
# Aggiorna il sistema
pacman -Syu

# Installa il toolchain di sviluppo
pacman -S mingw-w64-x86_64-toolchain

# Installa make
pacman -S mingw-w64-x86_64-make
```

### Passo 3: Aggiungi al PATH
1. Apri "Variabili d'ambiente" in Windows
2. Aggiungi questi percorsi alla variabile PATH:
   - `C:\msys64\mingw64\bin`
   - `C:\msys64\usr\bin`

### Passo 4: Verifica l'Installazione
Apri il Prompt dei Comandi di Windows e verifica:

```cmd
gcc --version
g++ --version
mingw32-make --version
```

## Metodo 2: MinGW-w64 Standalone

### Passo 1: Scarica MinGW-w64
1. Vai su [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/)
2. Scegli un distributore (es. Niels Kristian Bech Jensen)
3. Scarica la versione più recente

### Passo 2: Estrai e Configura
1. Estrai l'archivio in `C:\mingw64`
2. Aggiungi `C:\mingw64\bin` al PATH di sistema

## Metodo 3: Visual Studio (Alternativo)

Se preferisci non usare MinGW, puoi usare Visual Studio:

### Passo 1: Installa Visual Studio
1. Scarica Visual Studio Community (gratuito)
2. Durante l'installazione, seleziona "Desktop development with C++"
3. Assicurati che sia incluso MSVC v143

### Passo 2: Compila dal Developer Command Prompt
```cmd
# Apri "Developer Command Prompt for VS 2022"
cl /EHsc /std:c++17 src\main.cpp /Fe:WindowsHelper.exe user32.lib gdi32.lib comctl32.lib
```

## Test della Configurazione

Dopo aver installato il compilatore, testa la configurazione:

### 1. Apri il Prompt dei Comandi
### 2. Naviga alla directory del progetto:
```cmd
cd "C:\Users\chris\Documents\prova"
```

### 3. Esegui la compilazione:
```cmd
# Con MinGW
mingw32-make

# Oppure usa il file batch
build.bat
```

### 4. Se tutto funziona, vedrai:
```
Compilazione completata! Eseguibile: WindowsHelper.exe
```

## Problemi Comuni e Soluzioni

### Errore: "mingw32-make non riconosciuto"
**Soluzione**: Il PATH non è configurato correttamente. Verifica che `C:\msys64\mingw64\bin` sia nel PATH.

### Errore: "gcc non trovato"
**Soluzione**: Installa il toolchain completo con `pacman -S mingw-w64-x86_64-toolchain`

### Errore di linking con le librerie Windows
**Soluzione**: Assicurati di usare MinGW-w64 (non MinGW-32) per la compatibilità con le API moderne.

### L'applicazione non si avvia
**Soluzione**: Potrebbe mancare una DLL. Copia le DLL necessarie dalla cartella MinGW o compila staticamente.

## Configurazione Visual Studio Code

Dopo l'installazione di MinGW, riavvia VS Code per rilevare automaticamente il compilatore. Se non viene rilevato:

1. Apri Command Palette (Ctrl+Shift+P)
2. Cerca "C/C++: Edit Configurations (UI)"
3. Imposta il Compiler path su: `C:\msys64\mingw64\bin\g++.exe`

## Supporto

Se incontri problemi:
1. Verifica che il PATH sia configurato correttamente
2. Riavvia il terminale/VS Code dopo aver modificato il PATH
3. Controlla che la versione di MinGW sia compatibile con il tuo sistema

---

Una volta installato MinGW, potrai compilare ed eseguire l'applicazione Windows Helper!
