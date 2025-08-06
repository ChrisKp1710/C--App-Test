# Makefile per DevNotes - Obsidian Clone
# Compilatore
CXX = g++

# Nome dell'eseguibile
TARGET = DevNotes.exe

# Directory
SRCDIR = src
INCDIR = include
OBJDIR = obj

# File sorgenti
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Flag di compilazione per UI moderna
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCDIR) -DUNICODE -D_UNICODE
LDFLAGS = -lgdi32 -luser32 -lkernel32 -lcomctl32 -luxtheme

# Flag per release/debug
ifdef DEBUG
    CXXFLAGS += -g -DDEBUG
else
    CXXFLAGS += -O2 -DNDEBUG
endif

# Target principale
all: $(TARGET)

# Crea la directory obj se non esiste
$(OBJDIR):
	@if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

# Compila l'eseguibile
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo.
	@echo Compilazione completata! Eseguibile: $(TARGET)

# Compila i file oggetto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pulizia
clean:
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "$(TARGET)" del "$(TARGET)"
	@echo File di build rimossi.

# Esegue l'applicazione
run: $(TARGET)
	@echo Avvio dell'applicazione...
	@.\$(TARGET)

# Build per debug
debug:
	@$(MAKE) DEBUG=1

# Installa (copia in una directory di sistema - opzionale)
install: $(TARGET)
	@echo Per installare l'applicazione, copiare $(TARGET) nella directory desiderata.

# Help
help:
	@echo Comandi disponibili:
	@echo   make          - Compila l'applicazione
	@echo   make debug    - Compila in modalità debug
	@echo   make clean    - Rimuove i file di build
	@echo   make run      - Compila ed esegue l'applicazione
	@echo   make help     - Mostra questo messaggio

.PHONY: all clean run debug install help
