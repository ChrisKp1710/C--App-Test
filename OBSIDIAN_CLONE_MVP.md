# 🧠 ObsidianClone - DevNotes MVP Project

## 📋 Panoramica Progetto

**Obiettivo**: Creare un clone di Obsidian per Windows con funzionalità base e poi aggiungere features premium.

**Nome Progetto**: DevNotes  
**Target**: Developer e utenti avanzati  
**Tecnologie**: C++ Win32, Markdown, File System APIs  

---

## 🎯 FASE 1: FOUNDATION MVP (Settimane 1-2)

### Task 1.1: Layout Base Interfaccia
- [ ] **Sidebar sinistra**: File Explorer per note (200px width)
- [ ] **Area centrale**: Editor di testo multilinea
- [ ] **Sidebar destra**: Panel info/preview (250px width)
- [ ] **Menu bar**: File, Edit, View, Help
- [ ] **Status bar**: Informazioni file corrente

**File da modificare**: `main.cpp`
**Stima**: 2-3 giorni

### Task 1.2: File Management System
- [ ] **Creazione cartella** "notes" di default
- [ ] **Scan directory** per file .md esistenti
- [ ] **Creazione nuova nota** (Ctrl+N)
- [ ] **Salvataggio automatico** ogni 5 secondi
- [ ] **Apertura file** da sidebar

**Nuovi file**: `FileManager.h/cpp`
**Stima**: 3-4 giorni

### Task 1.3: Editor Base Markdown
- [ ] **Multi-line text editor** con scroll
- [ ] **Syntax highlighting** base (grassetto, corsivo)
- [ ] **Auto-indent** per liste
- [ ] **Undo/Redo** funzionalità
- [ ] **Find/Replace** (Ctrl+F)

**Nuovi file**: `MarkdownEditor.h/cpp`
**Stima**: 4-5 giorni

### Task 1.4: Preview System
- [ ] **Split view**: Editor + Preview
- [ ] **Markdown parser** base (headers, bold, italic, lists)
- [ ] **Live preview** che si aggiorna in tempo reale
- [ ] **Toggle preview** (Ctrl+E)

**Nuovi file**: `MarkdownParser.h/cpp`, `PreviewPane.h/cpp`
**Stima**: 3-4 giorni

---

## 🚀 FASE 2: CORE FEATURES (Settimane 3-4)

### Task 2.1: Link System
- [ ] **[[Link]] detection** nel testo
- [ ] **Auto-completion** nomi file esistenti
- [ ] **Click per aprire** note linkate
- [ ] **Creazione automatica** note non esistenti
- [ ] **Highlight link** esistenti vs non esistenti

**Nuovi file**: `LinkManager.h/cpp`
**Stima**: 4-5 giorni

### Task 2.2: Search Functionality
- [ ] **Global search** in tutte le note (Ctrl+Shift+F)
- [ ] **Search results** con preview snippet
- [ ] **Search in current file** enhanced
- [ ] **Case-sensitive** toggle option

**Nuovi file**: `SearchEngine.h/cpp`
**Stima**: 3-4 giorni

### Task 2.3: Backlinks Panel
- [ ] **Backlinks detection** per nota corrente
- [ ] **Sidebar panel** con lista backlinks
- [ ] **Click per navigare** a nota che fa riferimento
- [ ] **Context snippet** per ogni backlink

**Stima**: 3-4 giorni

### Task 2.4: Tags System
- [ ] **#tag recognition** nel testo
- [ ] **Tag panel** con lista tutti i tag usati
- [ ] **Filter by tag** funzionalità
- [ ] **Tag suggestions** durante digitazione

**Nuovi file**: `TagManager.h/cpp`
**Stima**: 3-4 giorni

---

## ⚡ FASE 3: ADVANCED FEATURES (Settimane 5-6)

### Task 3.1: Quick Switcher
- [ ] **Ctrl+O**: Quick file opener
- [ ] **Fuzzy search** nei nomi file
- [ ] **Recent files** priorità più alta
- [ ] **Keyboard navigation** con frecce

**Stima**: 2-3 giorni

### Task 3.2: Settings & Themes
- [ ] **Settings dialog** con opzioni base
- [ ] **Dark/Light theme** switch
- [ ] **Font size/family** customization
- [ ] **Auto-save interval** setting

**Nuovi file**: `Settings.h/cpp`, `ThemeManager.h/cpp`
**Stima**: 3-4 giorni

### Task 3.3: Graph View (MVP Version)
- [ ] **Simple graph visualization** delle connessioni
- [ ] **Nodes**: File names
- [ ] **Edges**: Collegamenti [[]]
- [ ] **Click node** per aprire file
- [ ] **Basic layout algorithm** (circle/grid)

**Nuovi file**: `GraphView.h/cpp`
**Stima**: 5-7 giorni

### Task 3.4: Export Functions
- [ ] **Export to HTML** singola nota
- [ ] **Export to PDF** (via print)
- [ ] **Export all notes** in zip
- [ ] **Export graph** come immagine

**Nuovi file**: `ExportManager.h/cpp`
**Stima**: 3-4 giorni

---

## 💎 FASE 4: PREMIUM FEATURES (Settimane 7-8)

### Task 4.1: Advanced Graph
- [ ] **Force-directed layout** più sofisticato
- [ ] **Zoom/Pan** nel graph
- [ ] **Node clustering** per argomenti
- [ ] **Graph filters** (by tag, date, etc.)

**Stima**: 4-5 giorni

### Task 4.2: Plugin System Base
- [ ] **Plugin interface** definition
- [ ] **Plugin loader** architecture
- [ ] **Sample plugin**: Word count
- [ ] **Plugin manager** UI

**Nuovi file**: `PluginSystem.h/cpp`
**Stima**: 5-6 giorni

### Task 4.3: Cloud Sync Preparation
- [ ] **File versioning** system locale
- [ ] **Sync conflict** detection
- [ ] **API preparation** per cloud service
- [ ] **User authentication** system base

**Nuovi file**: `SyncManager.h/cpp`, `Auth.h/cpp`
**Stima**: 4-5 giorni

### Task 4.4: Advanced Search
- [ ] **Boolean operators** (AND, OR, NOT)
- [ ] **Date range** filtering
- [ ] **File type** filtering
- [ ] **Regular expressions** support

**Stima**: 3-4 giorni

---

## 📁 Struttura File Finale

```
src/
├── main.cpp                 // Entry point
├── core/
│   ├── Application.h/cpp    // Main app logic
│   ├── Window.h/cpp         // Window management
│   └── Settings.h/cpp       // User preferences
├── ui/
│   ├── MarkdownEditor.h/cpp // Editor principale
│   ├── PreviewPane.h/cpp    // Markdown preview
│   ├── Sidebar.h/cpp        // File explorer
│   ├── GraphView.h/cpp      // Graph visualization
│   └── ThemeManager.h/cpp   // Theming system
├── engine/
│   ├── FileManager.h/cpp    // File operations
│   ├── MarkdownParser.h/cpp // MD to HTML
│   ├── LinkManager.h/cpp    // [[Link]] handling
│   ├── SearchEngine.h/cpp   // Search functionality
│   └── TagManager.h/cpp     // Tag system
├── sync/
│   ├── SyncManager.h/cpp    // Cloud sync
│   └── Auth.h/cpp           // Authentication
└── plugins/
    ├── PluginSystem.h/cpp   // Plugin architecture
    └── samples/             // Example plugins
```

---

## 🎯 Milestone e Deliverable

### MVP Release 1.0 (Fine Fase 2)
- ✅ Editor Markdown funzionale
- ✅ File management completo
- ✅ Link system [[]] funzionante
- ✅ Search in files
- ✅ Backlinks detection

### Beta Release 1.5 (Fine Fase 3)
- ✅ Graph view base
- ✅ Quick switcher
- ✅ Theme support
- ✅ Export functions

### Production Release 2.0 (Fine Fase 4)
- ✅ Advanced graph visualization
- ✅ Plugin system
- ✅ Cloud sync ready
- ✅ Advanced search

---

## 🛠️ Setup Tecnico Necessario

### Dependencies
- **Windows SDK** (già presente)
- **GDI+** per rendering graph
- **WinHTTP** per cloud sync
- **Regex library** per pattern matching

### Build Configuration
```makefile
# Aggiungi al Makefile
LIBS += -lgdiplus -lwinhttp -lcomctl32 -luxtheme
CPPFLAGS += -DUNICODE -D_UNICODE
```

### VS Code Extensions Utili
- **Markdown Preview Enhanced**
- **C++ Intellisense**
- **Git Graph** (per vedere progress)

---

## 📊 Stima Tempi Totali

| Fase | Settimane | Giorni Lavorativi | Complessità |
|------|-----------|-------------------|-------------|
| Fase 1 | 2 | 10-14 giorni | Media |
| Fase 2 | 2 | 10-14 giorni | Alta |
| Fase 3 | 2 | 10-14 giorni | Alta |
| Fase 4 | 2 | 10-14 giorni | Molto Alta |
| **TOTALE** | **8** | **40-56 giorni** | - |

---

## 🎮 Features Competitive vs Obsidian

### Nostri Vantaggi
- 🚀 **Performance nativa** C++ vs Electron
- 🎯 **Focalizzato su developer** workflow
- 💰 **Cloud sync più economico**
- 🛠️ **Plugin system** più semplice

### Differenziatori Premium
- 📊 **Advanced analytics** usage patterns
- 🤖 **AI-powered** link suggestions
- 🌐 **Multi-workspace** management
- 📱 **Mobile companion** app

---

## 🚀 Next Steps

1. **Iniziare con Task 1.1** - Layout base interfaccia
2. **Setup branch** development su Git
3. **Daily commits** per trackare progress
4. **Weekly review** milestone raggiunti

**Pronto per iniziare Task 1.1? Modifichiamo il main.cpp per creare il layout a 3 pannelli! 🎯**
